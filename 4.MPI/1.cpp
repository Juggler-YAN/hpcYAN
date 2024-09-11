/**
 * @file 1-1.cpp
 * @author yan
 * @brief hellowrold
 *        无通信
 *        编译：mpic++ 1-1.cpp -o test
 *        运行：mpiexec -n 4 ./test
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// #include <iostream>

// int main()
// {
//     std::cout << "helloworld" << std::endl;
//     return 0;
// }

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int myid, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    std::cout << myid << ":helloworld" << std::endl;
    MPI_Finalize();
    return 0;
}