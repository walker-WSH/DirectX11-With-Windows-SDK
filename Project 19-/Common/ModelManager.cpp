#include "XUtil.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ImGuiLog.h"

#include <filesystem>


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

using namespace DirectX;

void Model::CreateFromGeometry(Model& model, ID3D11Device* device, const GeometryData& data, bool isDynamic)
{
    // 默认材质
    model.materials = { Material{} };

    model.meshdatas = { MeshData{} };
    model.meshdatas[0].m_VertexCount = (uint32_t)data.vertices.size(); // 顶点 24个
    model.meshdatas[0].m_IndexCount = (uint32_t)(!data.indices16.empty() ? data.indices16.size() : data.indices32.size()); // 36个索引
    model.meshdatas[0].m_MaterialIndex = 0;

    CD3D11_BUFFER_DESC bufferDesc(0,
        D3D11_BIND_VERTEX_BUFFER,
        isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT,
        isDynamic ? D3D11_CPU_ACCESS_WRITE : 0);
    D3D11_SUBRESOURCE_DATA initData{ nullptr, 0, 0 };

    initData.pSysMem = data.vertices.data();
    bufferDesc.ByteWidth = (uint32_t)data.vertices.size() * sizeof(XMFLOAT3);
    device->CreateBuffer(&bufferDesc, &initData, model.meshdatas[0].m_pVertices.GetAddressOf());

    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.CPUAccessFlags = 0;
    if (!data.indices16.empty())
    {
        // 索引buffer 36个索引
        initData.pSysMem = data.indices16.data();
        bufferDesc = CD3D11_BUFFER_DESC((uint16_t)data.indices16.size() * sizeof(uint16_t), D3D11_BIND_INDEX_BUFFER);
        device->CreateBuffer(&bufferDesc, &initData, model.meshdatas[0].m_pIndices.GetAddressOf());
    }
}

void Model::SetDebugObjectName(std::string_view name)
{
}

namespace
{
    // ModelManager单例
    ModelManager* s_pInstance = nullptr;
}


ModelManager::ModelManager()
{
    if (s_pInstance)
        throw std::exception("ModelManager is a singleton!");
    s_pInstance = this;
}

ModelManager::~ModelManager()
{
}

ModelManager& ModelManager::Get()
{
    if (!s_pInstance)
        throw std::exception("ModelManager needs an instance!");
    return *s_pInstance;
}

void ModelManager::Init(ID3D11Device* device)
{
    m_pDevice = device;
    m_pDevice->GetImmediateContext(m_pDeviceContext.ReleaseAndGetAddressOf());
}

Model* ModelManager::CreateFromFile(std::string_view filename)
{
    return CreateFromFile(filename, filename);
}

Model* ModelManager::CreateFromFile(std::string_view name, std::string_view filename)
{
	assert(false);
    XID modelID = StringToID(name);
    auto& model = m_Models[modelID];
    return &model;
}

Model* ModelManager::CreateFromGeometry(std::string_view name, const GeometryData& data, bool isDynamic)
{
    XID modelID = StringToID(name);
    auto& model = m_Models[modelID];
    Model::CreateFromGeometry(model, m_pDevice.Get(), data, isDynamic);

    return &model;
}

const Model* ModelManager::GetModel(std::string_view name) const
{
    XID nameID = StringToID(name);
    if (auto it = m_Models.find(nameID); it != m_Models.end())
        return &it->second;
    return nullptr;
}

Model* ModelManager::GetModel(std::string_view name)
{
    XID nameID = StringToID(name);
    if (m_Models.count(nameID))
        return &m_Models[nameID];
    return nullptr;
}
