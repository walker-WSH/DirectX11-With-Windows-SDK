//***************************************************************************************
// Effects.h by X_Jun(MKXJun) (C) 2018-2022 All Rights Reserved.
// Licensed under the MIT License.
//
// 简易特效管理框架
// Simple effect management framework.
//***************************************************************************************

#ifndef EFFECTS_H
#define EFFECTS_H

#include <IEffect.h>
#include <Material.h>
#include <MeshData.h>
#include <LightHelper.h>

class SkyboxEffect : public IEffect, public IEffectTransform, public IEffectMaterial, public IEffectMeshData {
public:
	SkyboxEffect();
	virtual ~SkyboxEffect() override;

	SkyboxEffect(SkyboxEffect &&moveFrom) noexcept;
	SkyboxEffect &operator=(SkyboxEffect &&moveFrom) noexcept;

	// 获取单例
	static SkyboxEffect &Get();

	// 初始化所需资源
	bool InitAll(ID3D11Device *device);

	//
	// IEffectTransform
	//

	// 无用
	void XM_CALLCONV SetWorldMatrix(DirectX::FXMMATRIX W) override;

	void XM_CALLCONV SetViewMatrix(DirectX::FXMMATRIX V) override;
	void XM_CALLCONV SetProjMatrix(DirectX::FXMMATRIX P) override;

	//
	// IEffectMaterial
	//

	void SetMaterial(const Material &material) override;

	//
	// IEffectMeshData
	//

	MeshDataInput GetInputData(const MeshData &meshData) override;

	//
	// SkyboxEffect
	//

	void SetRenderDefault();

	// 应用常量缓冲区和纹理资源的变更
	void Apply(ID3D11DeviceContext *deviceContext) override;

private:
	class Impl;
	std::unique_ptr<Impl> pImpl;
};

#endif
