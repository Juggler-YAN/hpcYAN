/**
 * @file 1-12.cpp
 * @author yan
 * @brief 点对点通信（缓存通信模式）
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

    int a;
    int* buf = new int[2000];
    int bufsize = 2000;
    MPI_Buffer_attach(buf, bufsize);
    if (rank == 0)
    {
        a = 1;
        MPI_Bsend(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    if (rank == 1)
    {
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        std::cout << a << std::endl;
    }
    MPI_Buffer_detach(buf, &bufsize);
    delete buf;

    MPI_Finalize();

    return 0;
}