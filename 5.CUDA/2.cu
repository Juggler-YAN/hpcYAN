/**
 * @file 2-2.cu
 * @author yan
 * @brief 矩阵相加
 *        高维数据转一维数据
 * @version 0.1
 * @date 2022-07-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>

__global__ void add(float* A, float* B, float* C, int M, int N)
{ 
	int i = blockIdx.y * blockDim.y + threadIdx.y;
	int j = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < M && j < N)
	{
		C[i * N + j] = A[i * N + j] + B[i * N + j];
	}
}

int main()
{
	// 1.申请Host内存
	int M, N;
	M = 30;
	N = 37;
	float* A_h = NULL;
	float* B_h = NULL;
	float* C_h = NULL;
	cudaMallocHost((void**)&A_h, M * N * sizeof(float));
	cudaMallocHost((void**)&B_h, M * N * sizeof(float));
	cudaMallocHost((void**)&C_h, M * N * sizeof(float));

	// 2.申请Device内存
	float* A_d = NULL;
	float* B_d = NULL;
	float* C_d = NULL;
	cudaMalloc((void**)&A_d, M * N * sizeof(float));
	cudaMalloc((void**)&B_d, M * N * sizeof(float));
	cudaMalloc((void**)&C_d, M * N * sizeof(float));

	// 3.初始化
	for (int i = 0; i != M; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			A_h[i * N + j] = i * N + j;
			B_h[i * N + j] = i * N + j;
		}
	}

	// 4.将Host数据拷贝到Device中
	cudaMemcpy(A_d, A_h, M * N * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(B_d, B_h, M * N * sizeof(float), cudaMemcpyHostToDevice);

	// 5.Kernel函数
	dim3 dg(ceil((float)N / 8.0), ceil((float)M / 8.0), 1);
	dim3 db(8, 8, 1);
	add << <dg, db >> > (A_d, B_d, C_d, M, N);

	// 6.将Device数据拷贝到Host中
	cudaMemcpy(C_h, C_d, M * N * sizeof(float), cudaMemcpyDeviceToHost);

	// 7.检测结果
	for (int i = 0; i != M; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			if (C_h[i * N + j] != 2 * (i * N + j))
			{
				std::cout << "helloworld" << std::endl;
			}
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