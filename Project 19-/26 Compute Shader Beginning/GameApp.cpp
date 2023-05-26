#include "GameApp.h"

using namespace DirectX;

GameApp::GameApp(HINSTANCE hInstance) : D3DApp(hInstance) {}

GameApp::~GameApp() {}

bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	if (!InitResource())
		return false;

	return true;
}

bool SaveBitmapFile(const wchar_t *path, const uint8_t *data, int linesize, int width, int height,
		    int pixelSize, bool flip);

void GameApp::Compute()
{
	assert(m_pd3dImmediateContext);
	// 注意：以下DX函数 都是CS_XXXX， 以CS开头

	m_pd3dImmediateContext->CSSetShaderResources(0, 1, m_pTextureInputA.GetAddressOf());
	m_pd3dImmediateContext->CSSetShaderResources(1, 1, m_pTextureInputB.GetAddressOf());

	m_pd3dImmediateContext->CSSetShader(m_pTextureMul_CS.Get(), nullptr, 0);
	m_pd3dImmediateContext->CSSetUnorderedAccessViews(0, 1, m_pTextureOutputUAV.GetAddressOf(),
							  nullptr);

	ID3D11Buffer *buffer[] = {m_pCSConstBuffer.Get()};
	m_pd3dImmediateContext->CSSetConstantBuffers(0, 1, buffer);

	// 此处的x/y/z和shader中的numthreads配合，最终扫描区域可能会超出纹理尺寸，超出的部分也会调用到computeshader
	// 可以向shader同时传递纹理分辨率的const buffer
	m_pd3dImmediateContext->Dispatch(32, 32, 1);

	// 注意：
	// 微软的demo中，调用完了Dispatch， 又会把前面设置的参数都set为null
	// https://github.com/walbourn/directx-sdk-samples/tree/main/BasicCompute11

	//---------------------------------------------------------------------------------------------------------------
	DWORD clr = 0;
	SaveDDSTextureToFile(m_pd3dImmediateContext.Get(), m_pTextureOutput.Get(),
			     L"..\\Texture\\flareoutput.dds", clr);

	int width = 200;
	int height = 200;
	int linesize = width * 4;

	uint8_t *data = new uint8_t[(size_t)linesize * (size_t)height];
	DWORD *temp = (DWORD *)data;
	for (int i = 0; i < width * height; ++i) {
		temp[i] = clr;
	}

	SaveBitmapFile(L"..\\Texture\\flareoutput.bmp", data, linesize, width, height, 4, false);
	delete[] data;
}

bool GameApp::InitResource()
{
	CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"..\\Texture\\flare.dds", nullptr,
				 m_pTextureInputA.GetAddressOf());
	CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"..\\Texture\\flarealpha.dds", nullptr,
				 m_pTextureInputB.GetAddressOf());

	// DXGI_FORMAT                     |  RWTexture2D<T>
	// --------------------------------+------------------
	// DXGI_FORMAT_R8G8B8A8_UNORM      |  unorm float4
	// DXGI_FORMAT_R16G16B16A16_UNORM  |  unorm float4
	// DXGI_FORMAT_R8G8B8A8_SNORM      |  snorm float4
	// DXGI_FORMAT_R16G16B16A16_SNORM  |  snorm float4
	// DXGI_FORMAT_R16G16B16A16_FLOAT  |  float4 或 half4?
	// DXGI_FORMAT_R32G32B32A32_FLOAT  |  float4
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
	CD3D11_TEXTURE2D_DESC texDesc(format, 512, 512, 1, 1,
				      D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
	m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, m_pTextureOutput.GetAddressOf());

	// 创建无序访问视图
	CD3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc(D3D11_UAV_DIMENSION_TEXTURE2D, format);
	m_pd3dDevice->CreateUnorderedAccessView(m_pTextureOutput.Get(), &uavDesc,
						m_pTextureOutputUAV.GetAddressOf());

	// 创建计算着色器
	ComPtr<ID3DBlob> blob;
	D3DReadFileToBlob(L"Shaders\\TextureMul_CS.cso", blob.GetAddressOf());
	m_pd3dDevice->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr,
					  m_pTextureMul_CS.GetAddressOf());

	{ // const buffer for compute shader

		float clr[4];
		clr[0] = 0.0;
		clr[1] = 1.0;
		clr[2] = 0.0;
		clr[3] = 1.0;

		D3D11_BUFFER_DESC CBufferDesc = {};
		CBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		CBufferDesc.ByteWidth = sizeof(clr);
		CBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		auto hr = m_pd3dDevice->CreateBuffer(&CBufferDesc, NULL,
						     m_pCSConstBuffer.GetAddressOf());
		if (FAILED(hr)) {
			assert(false);
		}

		UpdateShaderBuffer(m_pCSConstBuffer, clr, sizeof(clr));
	}

	return true;
}

void GameApp::UpdateShaderBuffer(ComPtr<ID3D11Buffer> buffer, const void *data, size_t size)
{
	D3D11_BUFFER_DESC desc;
	buffer->GetDesc(&desc);

	if (desc.ByteWidth == size)
		m_pd3dImmediateContext->UpdateSubresource(buffer.Get(), 0, nullptr, data, 0, 0);
	else {
		assert(false);
	}
}

bool SaveBitmapFile(const wchar_t *path, const uint8_t *data, int linesize, int width, int height,
		    int pixelSize, bool flip)
{
	if (!path || !data)
		return false;

	HANDLE hWrite = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
				   FILE_ATTRIBUTE_NORMAL, NULL);
	if (!hWrite || hWrite == INVALID_HANDLE_VALUE)
		return false;

	DWORD dwStride = width * pixelSize;
	DWORD dwNumOfWrite = 0;

	BITMAPFILEHEADER fileHead;
	memset(&fileHead, 0, sizeof(fileHead));
	fileHead.bfType = 'MB';
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	fileHead.bfSize = fileHead.bfOffBits + height * dwStride;

	BITMAPINFOHEADER infoHead;
	memset(&infoHead, 0, sizeof(infoHead));
	infoHead.biSize = sizeof(BITMAPINFOHEADER);
	infoHead.biWidth = width;
	infoHead.biHeight = height;
	infoHead.biPlanes = 1;
	infoHead.biBitCount = pixelSize * 8;
	infoHead.biCompression = 0;
	infoHead.biSizeImage = height * dwStride;

	WriteFile(hWrite, &fileHead, sizeof(BITMAPFILEHEADER), &dwNumOfWrite, NULL);
	WriteFile(hWrite, &infoHead, sizeof(BITMAPINFOHEADER), &dwNumOfWrite, NULL);

	for (int i = 0; i < height; ++i) {
		if (flip)
			WriteFile(hWrite, data + (height - 1 - i) * linesize, dwStride,
				  &dwNumOfWrite, NULL);
		else
			WriteFile(hWrite, data + i * linesize, dwStride, &dwNumOfWrite, NULL);
	}

	CloseHandle(hWrite);
	return true;
}
