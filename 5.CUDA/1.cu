/**
 * @file 2-1.cu
 * @author yan
 * @brief 向量加法
 *        cuda程序模板
 * @version 0.1
 * @date 2022-07-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>

__global__ void add(float* A, float* B, float* C, int N)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < N)
	{
		C[i] = A[i] + B[i];
	}
}

int main()
{
	// 1.申请Host内存
	int N;
	N = 10000;
	float* A_h = NULL;
	float* B_h = NULL;
	float* C_h = NULL;
	cudaMallocHost((void**)&A_h, N * sizeof(float));
	cudaMallocHost((void**)&B_h, N * sizeof(float));
	cudaMallocHost((void**)&C_h, N * sizeof(float));

	// 2.申请Device内存
	float* A_d = NULL;
	float* B_d = NULL;
	float* C_d = NULL;
	cudaMalloc((void**)&A_d, N * sizeof(float));
	cudaMalloc((void**)&B_d, N * sizeof(float));
	cudaMalloc((void**)&C_d, N * sizeof(float));

	// 3.初始化
	for (int i = 0; i != N; ++i)
	{
		A_h[i] = i;
		B_h[i] = i;
	}

	// 4.将Host数据拷贝到Device中
	cudaMemcpy(A_d, A_h, N * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(B_d, B_h, N * sizeof(float), cudaMemcpyHostToDevice);

	// 5.Kernel函数
	dim3 dg(ceil((float)N / 11), 1, 1);
	dim3 db(11, 1, 1);
	add << <dg, db >> > (A_d, B_d, C_d, N);

	// 6.将Device数据拷贝到Host中
	cudaMemcpy(C_h, C_d, N * sizeof(float), cudaMemcpyDeviceToHost);

	// 7.检测结果
	for (int i = 0; i != N; ++i)
	{
		if (C_h[i] != 2 * i)
		{
			std::cout << "helloworld" << std::endl;
		}
	}

	// 8.释放内存
	cudaFreeHost(A_h);
	cudaFreeHost(B_h);
	cudaFreeHost(C_h);
	cudaFree(A_d);
	cudaFree(B_d);
	cudaFree(C_d);

	return 0;
}