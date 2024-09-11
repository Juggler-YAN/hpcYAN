/**
 * @file 1-14.cpp
 * @author yan
 * @brief 点对点通信（就绪通信模式）
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
    MPI_Request request;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        int a = 1, b;
        MPI_Recv(&b, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
        std::cout << "1" << std::endl;
        MPI_Rsend(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        std::cout << "2" << std::endl;
    }
    if (rank == 1)
    {
        int val;
        MPI_Irecv(&val, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        std::cout << "3" << std::endl;
        MPI_Send(&val, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        std::cout << "4" << std::endl;
        MPI_Wait(&request, &status);
    }
    MPI_Finalize();
    return 0;
}