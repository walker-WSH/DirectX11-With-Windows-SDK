#include "Geometry.h"

namespace Geometry
{
    constexpr float PI = 3.1415926f;
    //
    // 几何体方法的实现
    //

    GeometryData CreateBox(float width, float height, float depth)
    {
        using namespace DirectX;

        GeometryData geoData;

        geoData.vertexList24.resize(24);

        float w2 = width / 2, h2 = height / 2, d2 = depth / 2;

        // 右面(+X面)
        geoData.vertexList24[0] = XMFLOAT3(w2, -h2, -d2);
        geoData.vertexList24[1] = XMFLOAT3(w2, h2, -d2);
        geoData.vertexList24[2] = XMFLOAT3(w2, h2, d2);
        geoData.vertexList24[3] = XMFLOAT3(w2, -h2, d2);
        // 左面(-X面)
        geoData.vertexList24[4] = XMFLOAT3(-w2, -h2, d2);
        geoData.vertexList24[5] = XMFLOAT3(-w2, h2, d2);
        geoData.vertexList24[6] = XMFLOAT3(-w2, h2, -d2);
        geoData.vertexList24[7] = XMFLOAT3(-w2, -h2, -d2);
        // 顶面(+Y面)
        geoData.vertexList24[8] = XMFLOAT3(-w2, h2, -d2);
        geoData.vertexList24[9] = XMFLOAT3(-w2, h2, d2);
        geoData.vertexList24[10] = XMFLOAT3(w2, h2, d2);
        geoData.vertexList24[11] = XMFLOAT3(w2, h2, -d2);
        // 底面(-Y面)
        geoData.vertexList24[12] = XMFLOAT3(w2, -h2, -d2);
        geoData.vertexList24[13] = XMFLOAT3(w2, -h2, d2);
        geoData.vertexList24[14] = XMFLOAT3(-w2, -h2, d2);
        geoData.vertexList24[15] = XMFLOAT3(-w2, -h2, -d2);
        // 背面(+Z面)
        geoData.vertexList24[16] = XMFLOAT3(w2, -h2, d2);
        geoData.vertexList24[17] = XMFLOAT3(w2, h2, d2);
        geoData.vertexList24[18] = XMFLOAT3(-w2, h2, d2);
        geoData.vertexList24[19] = XMFLOAT3(-w2, -h2, d2);
        // 正面(-Z面)
        geoData.vertexList24[20] = XMFLOAT3(-w2, -h2, -d2);
        geoData.vertexList24[21] = XMFLOAT3(-w2, h2, -d2);
        geoData.vertexList24[22] = XMFLOAT3(w2, h2, -d2);
        geoData.vertexList24[23] = XMFLOAT3(w2, -h2, -d2);

        geoData.indexList36.resize(36);
        
        uint16_t indices[] = {
            0, 1, 2, 2, 3, 0,		// 右面(+X面)
            4, 5, 6, 6, 7, 4,		// 左面(-X面)
            8, 9, 10, 10, 11, 8,	// 顶面(+Y面)
            12, 13, 14, 14, 15, 12,	// 底面(-Y面)
            16, 17, 18, 18, 19, 16, // 背面(+Z面)
            20, 21, 22, 22, 23, 20	// 正面(-Z面)
        };
        memcpy_s(geoData.indexList36.data(), sizeof indices, indices, sizeof indices);

        return geoData;
    }


}
