
cbuffer ConstantBuffer : register(b0)
{
	float4 color;
}

// intput texture
Texture2D<float4> g_TexA : register(t0);
Texture2D<float4> g_TexB : register(t1);

// output
RWTexture2D<unorm float4> g_Output : register(u0);

[numthreads(16, 16, 1)] void CS(uint3 DTid : SV_DispatchThreadID) 
{
	if (DTid.x < 256) { // 注意：DTid.xy 中的x和y 都是像素单位的索引, 从0开始，范围并不是[0, 1]
		g_Output[DTid.xy] = color;
	} else {
		g_Output[DTid.xy] = g_TexA[DTid.xy];
	}
}
