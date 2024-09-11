/**
 * @file 1-8.cpp
 * @author yan
 * @brief 任意源和任意标识的使用
 *        mpic++ 1-8.cpp -o test
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
    if (rank == 0)
    {
        int val;
        for (int i = 1; i != size; ++i)
        {
            MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            std::cout << val << std::endl;
        }
    }
    else
    {
        MPI_Send(&rank, 1, MPI::INT, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}