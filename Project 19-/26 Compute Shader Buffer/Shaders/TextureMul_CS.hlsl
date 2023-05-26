
cbuffer ConstantBuffer : register(b0)
{
	float4 color;
}

// intput texture
Texture2D<float4> g_TexA : register(t0);
Texture2D<float4> g_TexB : register(t1);

// output
struct OutputBuffer {
	int x;
	int y;
	int threadCount;
	float reserve1;
};
RWStructuredBuffer<OutputBuffer> BufferOut : register(u0);

[numthreads(16, 16, 1)] void CS(uint3 DTid
				: SV_DispatchThreadID) {
	if (BufferOut[0].x != -1) {

		BufferOut[0].x = (int)DTid.x;
		BufferOut[0].y = (int)DTid.y;

		// BufferOut[0].threadCount += 1; // 错误 多线程并发修改 结果不对
		//
		// 多线程并发修改变量，需要使用原子锁
		// 这个变量最终的值 应该是numthreads 和 Dispatch两个函数所有xyz维度的参数总乘积。
		InterlockedAdd(BufferOut[0].threadCount, 1);
	}

	BufferOut[0].reserve1 = 1.f;
}
