/**
 * @file 1-5.cpp
 * @author yan
 * @brief 获取机器名字和版本号
 *        mpic++ 1-5.cpp -o test
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
    char name[MPI_MAX_PROCESSOR_NAME];
    int namelen, version, subversion;
    MPI_Init(&argc, &argv);
    MPI_Get_processor_name(name, &namelen);
    MPI_Get_version(&version, &subversion);
    std::cout << "name: " << name << " version: " << version << subversion 
        << " len:" << namelen << std::endl;
    MPI_Finalize();
    return 0;
}