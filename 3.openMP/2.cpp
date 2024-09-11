/*
 * hello, world
 */

#include<iostream>
#include<omp.h>

using namespace std;

int main() {
	omp_set_num_threads(2);
// #pragma omp parallel
// 	{
#pragma omp parallel for
		for (int i = 0; i < 4; ++i)
		    cout << omp_get_thread_num() << endl;
	// }
    return 0;
}