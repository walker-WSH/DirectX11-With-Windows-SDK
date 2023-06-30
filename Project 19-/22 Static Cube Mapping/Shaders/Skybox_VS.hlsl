#include "Skybox.hlsli"

VSOutput VS(VertexInput vIn)
{
    // 设置z = w，使得z/w = 1(天空盒保持在远平面)
	float4 temp = mul(float4(vIn.posL, 1.0f), g_WorldViewProj);

	VSOutput vOut;
	vOut.posH = temp.xyww;
    vOut.posL = vIn.posL;
    return vOut;
}
