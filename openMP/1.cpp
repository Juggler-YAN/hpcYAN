/*
 * hello, world
 */

#include<iostream>
#include<omp.h>

using namespace std;

int main() {
#pragma omp parallel
	{
		cout << "Hello, world!" << endl;
	}
    printf("\n--------------------------\n");
#pragma omp parallel num_threads(5)
	{
		cout << "Hello, world!" << endl;
	}
    printf("\n**************************\n");
	omp_set_num_threads(2);
#pragma omp parallel
	{
		
		cout << "Hello, world!" << endl;
	}
    return 0;
}