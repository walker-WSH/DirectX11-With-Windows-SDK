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

void GameApp::Compute()
{
	assert(m_pd3dImmediateContext);
	// 注意：以下DX函数 都是CS_XXXX， 以CS开头

	while (1) {
		m_pd3dImmediateContext->CSSetShaderResources(0, 1, m_pTextureInputA.GetAddressOf());
		m_pd3dImmediateContext->CSSetShaderResources(1, 1, m_pTextureInputB.GetAddressOf());

		m_pd3dImmediateContext->CSSetShader(m_pTextureMul_CS.Get(), nullptr, 0);
		m_pd3dImmediateContext->CSSetUnorderedAccessViews(
			0, 1, g_pBufResultUAV.GetAddressOf(), nullptr);

		ID3D11Buffer *buffer[] = {m_pCSConstBuffer.Get()};
		m_pd3dImmediateContext->CSSetConstantBuffers(0, 1, buffer);

		// 此处的x/y/z和shader中的numthreads配合，最终扫描区域可能会超出纹理尺寸，超出的部分也会调用到computeshader
		// 可以向shader同时传递纹理分辨率的const buffer
		m_pd3dImmediateContext->Dispatch(32, 32, 1);

		// 注意：
		// 微软的demo中，调用完了Dispatch， 又会把前面设置的参数都set为null
		// https://github.com/walbourn/directx-sdk-samples/tree/main/BasicCompute11

		//---------------------------------------------------------------------------------------------------------------
		CopyAndReadOutputBuffer();
		Sleep(5);
	}
}

bool GameApp::InitResource()
{
	CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"..\\Texture\\flare.dds", nullptr,
				 m_pTextureInputA.GetAddressOf());
	CreateDDSTextureFromFile(m_pd3dDevice.Get(), L"..\\Texture\\flarealpha.dds", nullptr,
				 m_pTextureInputB.GetAddressOf());

	InitOutputBuffer();
	InitInputBuffer();

	// 创建计算着色器
	ComPtr<ID3DBlob> blob;
	D3DReadFileToBlob(L"Shaders\\TextureMul_CS.cso", blob.GetAddressOf());
	m_pd3dDevice->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr,
					  m_pTextureMul_CS.GetAddressOf());

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

void GameApp::InitOutputBuffer()
{
	OutputBuffer initData;
	ZeroMemory(&initData, sizeof(OutputBuffer));
	initData.x = 1122331;
	initData.y = -112233;

	UINT uElementSize = sizeof(OutputBuffer);
	UINT uCount = 1;

	{
		D3D11_BUFFER_DESC desc = {};
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		desc.ByteWidth = uElementSize * uCount;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = uElementSize;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = &initData;

		auto hr = m_pd3dDevice->CreateBuffer(&desc, &InitData, g_pBufResult.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	//-------------------------------------------------------------------------------------
	{
		D3D11_BUFFER_DESC descBuf = {};
		g_pBufResult->GetDesc(&descBuf);

		D3D11_UNORDERED_ACCESS_VIEW_DESC desc = {};
		desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		desc.Buffer.FirstElement = 0;
		// This is a Structured Buffer,
		// Format must be must be DXGI_FORMAT_UNKNOWN, when creating a View of a Structured Buffer
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.Buffer.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

		auto hr = m_pd3dDevice->CreateUnorderedAccessView(g_pBufResult.Get(), &desc,
								  g_pBufResultUAV.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
}

void GameApp::InitInputBuffer()
{
	float clr[4];
	clr[0] = 0.0;
	clr[1] = 1.0;
	clr[2] = 0.0;
	clr[3] = 1.0;

	D3D11_BUFFER_DESC CBufferDesc = {};
	CBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	CBufferDesc.ByteWidth = sizeof(clr);
	CBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	auto hr = m_pd3dDevice->CreateBuffer(&CBufferDesc, NULL, m_pCSConstBuffer.GetAddressOf());
	if (FAILED(hr)) {
		assert(false);
	}

	UpdateShaderBuffer(m_pCSConstBuffer, clr, sizeof(clr));
}

void GameApp::CopyAndReadOutputBuffer()
{
	ComPtr<ID3D11Buffer> debugbuf = nullptr;

	{
		// create/copy buffer

		D3D11_BUFFER_DESC desc = {};
		g_pBufResult->GetDesc(&desc);

		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.MiscFlags = 0;

		auto hr = m_pd3dDevice->CreateBuffer(&desc, nullptr, debugbuf.GetAddressOf());
		assert(SUCCEEDED(hr));

		m_pd3dImmediateContext->CopyResource(debugbuf.Get(), g_pBufResult.Get());
	}

	{
		// read buffer

		D3D11_MAPPED_SUBRESOURCE MappedResource;
		auto hr = m_pd3dImmediateContext->Map(debugbuf.Get(), 0, D3D11_MAP_READ, 0,
						      &MappedResource);
		assert(SUCCEEDED(hr));

		OutputBuffer *ptr = (OutputBuffer *)MappedResource.pData;
		char buf[200];
		sprintf_s(buf, "============ lastOne : %d, %d \n", ptr->x, ptr->y);
		OutputDebugStringA(buf);

		m_pd3dImmediateContext->Unmap(debugbuf.Get(), 0);
	}
}
