
cbuffer Constants : register(b0)
{
	float4 color;
}

Texture2D<float4> g_TexA : register(t0);
Texture2D<float4> g_TexB : register(t1);
RWTexture2D<unorm float4> g_Output : register(u0);

[numthreads(16, 16, 1)]
void CS( uint3 DTid : SV_DispatchThreadID )
{
   // g_Output[DTid.xy] = g_TexA[DTid.xy] * g_TexB[DTid.xy];

    if (DTid.x < 256) { // 注意：DTid.xy 中的x和y 都是像素单位的索引, 从0开始，范围并不是[0, 1]
	    g_Output[DTid.xy] = color;
    }
    else {
        g_Output[DTid.xy] = g_TexA[DTid.xy];
    }

    //------------------------------------------------------------------
    float4 color = g_TexB[DTid.xy];
    if (DTid.x > 512) {
        g_Output[float2(0, 0)] = float4(0, 0, 1, 1); // blue color
    }
}
