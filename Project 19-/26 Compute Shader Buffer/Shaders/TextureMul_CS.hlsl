
cbuffer ConstantBuffer : register(b0)
{
	float4 color;
}

struct OutputBuffer {
	int x;
	int y;
	int threadCount;
	float reserve1;
};

// intput texture
Texture2D<float4> g_TexA : register(t0);
Texture2D<float4> g_TexB : register(t1);

// output
RWStructuredBuffer<OutputBuffer> BufferOut : register(u0);

[numthreads(16, 16, 1)] void CS(uint3 DTid
				: SV_DispatchThreadID) {
	if (BufferOut[0].x != -1) {
		BufferOut[0].x = (int)DTid.x;
		BufferOut[0].y = (int)DTid.y;
		BufferOut[0].threadCount += 1;
	}

	BufferOut[0].reserve1 = 1.f;
}
