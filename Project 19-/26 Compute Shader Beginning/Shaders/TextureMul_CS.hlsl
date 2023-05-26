
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
	// g_Output[DTid.xy] = g_TexA[DTid.xy] * g_TexB[DTid.xy];

	//------------------------------------------------------------------------------------------------------
	float4 clr1 = g_TexA[DTid.xy];
	float4 clr2 = g_TexB[DTid.xy];

	clr1 *= 255; // [0, 1.f] -> [0, 255]
	clr2 *= 255;

	int4 clrTemp1 = round(clr1);
	int4 clrTemp2 = round(clr2);

	if (clrTemp1.x == clrTemp2.x && 
        clrTemp1.y == clrTemp2.y && 
        clrTemp1.z == clrTemp2.z &&
	    clrTemp1.w == clrTemp2.w) {

		g_Output[DTid.xy] = color;

	} else {
		g_Output[DTid.xy] = g_TexA[DTid.xy];
	}
	return;

	//------------------------------------------------------------------------------------------------------
	if (DTid.x < 256) { // 注意：DTid.xy 中的x和y 都是像素单位的索引, 从0开始，范围并不是[0, 1]
		g_Output[DTid.xy] = color;
	} else {
		g_Output[DTid.xy] = g_TexA[DTid.xy];
	}

	//------------------------------------------------------------------------------------------------------
	float4 color = g_TexB[DTid.xy];
	if (DTid.x > 512) {
		g_Output[float2(0, 0)] = float4(0, 0, 1, 1); // blue color
	}
}
