
TextureCube g_TexCube : register(t0); // TextureCube 立方体纹理
SamplerState g_Sam : register(s0);

cbuffer CBChangesEveryFrame : register(b0)
{
    matrix g_WorldViewProj;
}

struct VertexInput {
    float3 posL : POSITION;
};

struct VSOutput
{
    float4 posH : SV_POSITION;
    float3 posL : POSITION;
};


