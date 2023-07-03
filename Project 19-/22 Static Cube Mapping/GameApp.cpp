#include "GameApp.h"
#include <XUtil.h>
#include <DXTrace.h>
using namespace DirectX;

GameApp::GameApp(HINSTANCE hInstance, const std::wstring &windowName, int initWidth, int initHeight) : D3DApp(hInstance, windowName, initWidth, initHeight) {}

GameApp::~GameApp() {}

bool GameApp::Init()
{
	if (!D3DApp::Init())
		return false;

	m_TextureManager.Init(m_pd3dDevice.Get());
	m_ModelManager.Init(m_pd3dDevice.Get());

	// 务必先初始化所有渲染状态，以供下面的特效使用
	RenderStates::InitAll(m_pd3dDevice.Get());

	if (!m_SkyboxEffect.InitAll(m_pd3dDevice.Get()))
		return false;

	if (!InitResource())
		return false;

	return true;
}

void GameApp::OnResize()
{
	D3DApp::OnResize();

	// 摄像机变更显示
	if (m_pCamera != nullptr) {
		m_pCamera->SetFrustum(XM_PI / 3, AspectRatio(), 1.0f, 1000.0f);
		m_pCamera->SetViewPort(0.0f, 0.0f, (float)m_ClientWidth, (float)m_ClientHeight);
		m_SkyboxEffect.SetProjMatrix(m_pCamera->GetProjMatrixXM());
	}
}

void GameApp::UpdateScene(float dt)
{
	m_CameraController.Update(dt);

	// 更新观察矩阵

	m_SkyboxEffect.SetViewMatrix(m_pCamera->GetViewMatrixXM());

	if (ImGui::Begin("Static Cube Mapping")) {
	}
	ImGui::End();
	ImGui::Render();
}

void GameApp::DrawScene()
{
	// 创建后备缓冲区的渲染目标视图
	if (m_FrameCount < m_BackBufferCount) {
		ComPtr<ID3D11Texture2D> pBackBuffer;
		m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf()));

		CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc(D3D11_RTV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB);
		m_pd3dDevice->CreateRenderTargetView(pBackBuffer.Get(), &rtvDesc, m_pRenderTargetViews[m_FrameCount].ReleaseAndGetAddressOf());
	}

	float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	m_pd3dImmediateContext->ClearRenderTargetView(GetBackBufferRTV(), black);

	ID3D11RenderTargetView *pRTVs[1] = {GetBackBufferRTV()};
	m_pd3dImmediateContext->OMSetRenderTargets(1, pRTVs, nullptr);

	D3D11_VIEWPORT viewport = m_pCamera->GetViewPort();
	m_pd3dImmediateContext->RSSetViewports(1, &viewport);

	// 绘制天空盒
	m_SkyboxEffect.SetRenderDefault();
	m_Skybox.Draw(m_pd3dImmediateContext.Get(), m_SkyboxEffect);

	HR(m_pSwapChain->Present(0, m_IsDxgiFlipModel ? DXGI_PRESENT_ALLOW_TEARING : 0));
}

bool GameApp::InitResource()
{
	// ******************
	// 初始化天空盒相关

	// Daylight
	{
		std::vector<ID3D11ShaderResourceView *> pCubeTextures;
		std::string filenameStr = "..\\Texture\\daylight0.png";
		for (size_t i = 0; i < 6; ++i) {
			filenameStr[19] = '0' + (char)i;
			pCubeTextures.push_back(m_TextureManager.CreateFromFile(filenameStr));
		}

		ComPtr<ID3D11Texture2D> pTex;
		pCubeTextures[0]->GetResource(reinterpret_cast<ID3D11Resource **>(pTex.ReleaseAndGetAddressOf()));

		D3D11_TEXTURE2D_DESC texDesc;
		pTex->GetDesc(&texDesc);

		std::unique_ptr<TextureCube> pTexCube = std::make_unique<TextureCube>(m_pd3dDevice.Get(), texDesc.Width, texDesc.Height, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB);

		for (uint32_t i = 0; i < 6; ++i) {
			pCubeTextures[i]->GetResource(reinterpret_cast<ID3D11Resource **>(pTex.ReleaseAndGetAddressOf()));
			m_pd3dImmediateContext->CopySubresourceRegion(pTexCube->GetTexture(), D3D11CalcSubresource(0, i, 1), 0, 0, 0, pTex.Get(), 0, nullptr);
		}

		// 以“Daylight”为key 把立方体纹理保存了
        // 最终渲染立方体纹理时 会在GameObject::Draw中 获取纹理并设置到HLSL
		m_TextureManager.AddTexture("Daylight", pTexCube->GetShaderResource());

		// 此处结束 TextureCube对象就会析构 其创建的纹理 已经保存到了m_TextureManager
	}

	// 天空盒立方体 Geometry::CreateBox()中初始化顶点和索引数据
	Model *pModel = m_ModelManager.CreateFromGeometry("Skybox", Geometry::CreateBox(2.f, 2.f, 2.f));
	pModel->materials[0].Set<std::string>("$Skybox", "Daylight"); // 设置获取纹理的key“Daylight”
	m_Skybox.SetModel(pModel);

	// ******************
	// 初始化摄像机

	auto camera = std::make_shared<FirstPersonCamera>();
	m_pCamera = camera;
	m_CameraController.InitCamera(camera.get());
	camera->SetViewPort(0.0f, 0.0f, (float)m_ClientWidth, (float)m_ClientHeight);
	camera->SetFrustum(XM_PI / 2, AspectRatio(), 0.1f, 2000.0f);
	camera->LookTo(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f));

	m_SkyboxEffect.SetViewMatrix(camera->GetViewMatrixXM());
	m_SkyboxEffect.SetProjMatrix(camera->GetProjMatrixXM());

	// ******************
	// 初始化不会变化的值
	//

	return true;
}
