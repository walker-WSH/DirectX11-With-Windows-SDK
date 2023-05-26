
cbuffer ConstantBuffer : register(b0)
{
	float4 color;
}

struct OutputBuffer {
	int i;
	float f;
	float reserve1;
	float reserve2;
};

// intput texture
Texture2D<float4> g_TexA : register(t0);
Texture2D<float4> g_TexB : register(t1);

// output
RWStructuredBuffer<OutputBuffer> BufferOut : register(u0);

[numthreads(16, 16, 1)] void CS(uint3 DTid : SV_DispatchThreadID) {
	BufferOut[0].i = 123456;
	BufferOut[0].f = 99.99f; // 测试发现，C++中拷贝和read后，这个值可能是99.9899979
	BufferOut[0].reserve1 = 1.f;
	BufferOut[0].reserve2 = 2.f;
}
