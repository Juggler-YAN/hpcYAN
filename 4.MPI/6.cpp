/**
 * @file 1-6.cpp
 * @author yan
 * @brief 消息环形传递
 *        问题
 *        消息环形传递时可能会造成死锁，那么怎样才能避免死锁
 *        mpic++ 1-6.cpp -o test
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
    int m, n;
    m = n = rank;
    int prev, next;
    prev = (size + rank - 1) % size;
    next = (rank + 1) % size;
    std::cout << rank << ":" << m << " " << n << std::endl;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Send(&m, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
    MPI_Recv(&n, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &status);
    std::cout << rank << ":" << m << " " << n << std::endl;
    MPI_Finalize();
    return 0;
}