//***************************************************************************************
// MeshData.h by X_Jun(MKXJun) (C) 2018-2022 All Rights Reserved.
// Licensed under the MIT License.
//
// 存放网格数据
// Mesh data storage.
//***************************************************************************************

#pragma once

#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <wrl/client.h>
#include <vector>
#include <DirectXCollision.h>

struct ID3D11Buffer;

struct MeshData
{
    // 使用模板别名(C++11)简化类型名
    template <class T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    ComPtr<ID3D11Buffer> m_pVertices;                    // 顶点buffer
    ComPtr<ID3D11Buffer> m_pIndices;                     // 索引buffer

    uint32_t m_VertexCount = 0;
    uint32_t m_IndexCount = 0;
    uint32_t m_MaterialIndex = 0;

    DirectX::BoundingBox m_BoundingBox;
    bool m_InFrustum = true;
};





#endif
