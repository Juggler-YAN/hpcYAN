/**
 * @file 1-4.cpp
 * @author yan
 * @brief MPI计时
 *        mpic++ 1-4.cpp -o test
 *        mpiexec -n 2 ./test
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
    if (size != 2)
    {
        std::cout << "This progarm must run with 2 processes!" << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 99);
    }
    int m, n;
    m = rank;
    if (rank == 0)
    {
        double start, end, tick;
        start = MPI_Wtime();
        for (int i = 0; i != 3000; ++i)
        {
            MPI_Send(&m, 4, MPI_BYTE, 1, i, MPI_COMM_WORLD);
            MPI_Recv(&n, 4, MPI_BYTE, 1, i, MPI_COMM_WORLD, &status);
        }
        end = MPI_Wtime();
        tick = MPI_Wtick();
        std::cout << end-start << "s " << tick <<std::endl;
    }
    if (rank == 1)
    {
        for (int i = 0; i = 3000; ++i)
        {
            MPI_Recv(&m, 4, MPI_BYTE, 1, i, MPI_COMM_WORLD, &status);
            MPI_Send(&m, 4, MPI_BYTE, 1, i, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}