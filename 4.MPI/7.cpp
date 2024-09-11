/**
 * @file 1-7.cpp
 * @author yan
 * @brief 所有进程互相通信
 *        问题
 *        MPI_Send中tag起到什么作用
 *        mpic++ 1-7.cpp -o test
 *        mpiexec -n 5 ./test
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (int i = 0; i != size; ++i)
    {
        if (rank != i)
        {
            int val;
            MPI_Send(&rank, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Recv(&val, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            std::cout << "send:" << rank << " " << "recv:" << val << std::endl;
        }
    }
    MPI_Finalize();
    return 0;
}