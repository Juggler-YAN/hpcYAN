/**
 * @file 1-9-2.cpp
 * @author yan
 * @brief 对等模式MPI程序设计
 *        捆绑发送（自动优化发送和接收，一定程度上能避免死锁）
 *        mpic++ 1-9-2.cpp -o test
 *        mpiexec -n 4 ./test
 * @version 0.1
 * @date 2022-07-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <mpi.h>

#define N 8
#define STEP 100

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    float myRows[N/size+2][N], myRows2[N/size+2][N];
    for (int i = 0; i != N/size+2; ++i)
    {
        for (int j = 0; j != N; ++j)
        {
            if (rank == 0 && i == 1)
            {
                myRows[i][j] = 6;
                continue;
            }
            if (rank == size-1 && i == N/size)
            {
                myRows[i][j] = 6;
                continue;
            }
            myRows[i][j] = 0;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    for (int i = 0; i != STEP; ++i)
    {
        if (rank == 0)
        {
            MPI_Send(&myRows[N/size][0], N, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD);
        }
        else if (rank == size-1)
        {
            MPI_Recv(&myRows[0][0], N, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD, &status);
        }
        else
        {
            MPI_Sendrecv(&myRows[N/size][0], N, MPI_FLOAT, rank+1, 0, &myRows[0][0], N, 
                MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD, &status);
        }
        
        if (rank == 0)
        {
            MPI_Recv(&myRows[N/size+1][0], N, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD, &status);
        }
        else if (rank == size-1)
        {
            MPI_Send(&myRows[1][0], N, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Sendrecv(&myRows[1][0], N, MPI_FLOAT, rank-1, 0, &myRows[N/size+1][0], N, 
                MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD, &status);
        }


        int begin, end;
        begin = (rank == 0) ? 2 : 1;
        end = (rank == N/size-1) ? N/size-1 : N/size;
        for (int i = begin; i <= N/size; ++i)
        {
            for (int j = 1; j != N-1; ++j)
            {
                myRows2[i][j] = 0.25 * (myRows[i-1][j] + myRows[i+1][j] + myRows[i][j-1] + myRows[i][j+1]);
            }
        }
        for (int i = begin; i <= N/size; ++i)
        {
            for (int j = 1; j != N-1; ++j)
            {
                myRows[i][j] = myRows2[i][j];
            }
        }
    }

    std::cout << rank << ":" << std::endl;
    for (int i = 0; i != N/size+2; ++i)
    {
        for (int j = 0; j != N; ++j)
        {
            std::cout << myRows[i][j] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}