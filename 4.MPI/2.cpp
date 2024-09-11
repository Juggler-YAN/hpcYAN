/**
 * @file 1-2.cpp
 * @author yan
 * @brief MPI最基本的六个函数
 *        简单通信
 *        mpic++ 1-2.cpp -o test
 *        mpiexec -n 2 ./test
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int num = 21;
    MPI_Init(&argc, &argv);
    int myid, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (myid == 0)
    {
        MPI_Send(&num, 1, MPI_INT, 1, 99, MPI_COMM_WORLD);
    }
    if (myid == 1)
    {
        MPI_Status status;
        MPI_Recv(&num, 1, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
        std::cout << num << std::endl;
    }
    MPI_Finalize();
    return 0;
}