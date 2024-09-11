/**
 * @file 1-13.cpp
 * @author yan
 * @brief 点对点通信（同步通信模式）
 * @version 0.1
 * @date 2022-07-17
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
    if (rank == 0)
    {
        int a = 1, b = 2;
        MPI_Ssend(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        std::cout << "0:" << a << std::endl;
        MPI_Ssend(&b, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
        std::cout << "0:" << b << std::endl;
    }
    if (rank == 1)
    {
        int val1, val2;
        MPI_Recv(&val1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        std::cout << "1:" << val1 << std::endl;
        MPI_Recv(&val2, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        std::cout << "1:" << val2 << std::endl;
    }
    MPI_Finalize();
    return 0;
}