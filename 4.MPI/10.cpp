/**
 * @file 1-10.cpp
 * @author yan
 * @brief 
 * @version 0.1
 * @date 2022-07-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <mpi.h>

#define ROWS 100
#define COLS 100

int main(int argc, char* argv[])
{
    // float a[ROWS][COLS], b[ROWS], c[]
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        a = 1;
        MPI_Bcast(&a, 1, MPI::INT, 0, MPI_COMM_WORLD);
    }
    std::cout << a << std::endl;
    MPI_Finalize();
    return 0;
}