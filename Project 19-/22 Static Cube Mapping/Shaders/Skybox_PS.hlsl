#include "Skybox.hlsli"

float4 PS(VSOutput pIn) : SV_Target
{
    return g_TexCube.Sample(g_Sam, pIn.posL);
}
