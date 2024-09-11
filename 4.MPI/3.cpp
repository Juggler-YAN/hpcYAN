/**
 * @file 1-3.cpp
 * @author 求二维数组中各元素的最大值
 *         分块并行运算
 *         问题：
 *         MPI运行后整个程序从头到尾都是并行的
 *         MPI发送后接收的问题（这里不应该用点对点通信，应该用集合通信，即便是点对点通信也不应该用顺序接收）
 *         这里全都是阻塞通信，改为非阻塞通信会不会增加
 *         当N增加时，会出现段错误，为什么?
 *         mpic++ 1-3.cpp -o test
 *         mpiexec -n 5 ./test
 * @brief 
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <ctime>
#include <mpi.h>

#define N 1000

int main(int argc, char* argv[])
{
    // // 串行
    // clock_t start, end;
    // start = clock();
    // int A[N][N];
    // for (int i = 0; i != N; ++i)
    // {
    //     for (int j = 0; j != N; ++j)
    //     {
    //         A[i][j] = i+j;
    //     }
    // }
    // int max = 0;
    // for (int i = 0; i != N; ++i)
    // {
    //     for (int j = 0; j != N; ++j)
    //     {
    //         if (A[i][j] > max)
    //         {
    //             max = A[i][j];
    //         }
    //     }
    // }
    // end = clock();
    // std::cout << double(end-start)/CLOCKS_PER_SEC << "s" << std::endl;
    // std::cout << max << std::endl;

    // 并行
    MPI_Init(&argc, &argv);
    int myid, size;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int** A;
    A = new int*[N/size];
    for (int i = 0; i != N/size; ++i)
    {
        A[i] = new int[N];
        for (int j = 0; j != N; ++j)
        {
            A[i][j] = myid*N/size+i+j;
        }
    }
    int max = 0;
    for (int i = 0; i != N/size; ++i)
    {
        for (int j = 0; j != N; ++j)
        {
            if (A[i][j] > max)
            {
                max = A[i][j];
            }
        }
    }
    std::cout << myid << ":" << max << std::endl;
    if (myid > 0)
    {
        MPI_Send(&max, 1, MPI_INT, 0, myid, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i != size; ++i)
        {
            int val;
            MPI_Recv(&val, 1, MPI_INT, i, i, MPI_COMM_WORLD, &status);
            if (val > max)
            {
                max = val;
            }
        }
        std::cout << max << std::endl;
    }

    for (int i = 0; i != N/size; ++i)
    {
        delete[] A[i];
    }
    delete[] A;
    MPI_Finalize();

    return 0;
}