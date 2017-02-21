#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <Windows.h>
using namespace std;

//int main(int argc, char* argv[] )
void main()
{
	int rank , size;
	int k = 5, d=-5;

//#pragma omp parallel num_threads(10) private(rank) firstprivate(k) shared(size)
//	{
//		
//		rank = omp_get_thread_num();
//		size = omp_get_num_threads();
//		k++;
//		d = rank;
//
//		printf("Hello from %d thread out of %d - %d\n",rank, size, k);
//	}

//#pragma omp parallel sections 
//	{
//#pragma omp section
//		{
//			rank = omp_get_thread_num();
//			printf("Section - 0 thread - %d\n", rank);	
//			Sleep(100);
//		}
//#pragma omp section
//		{
//			rank = omp_get_thread_num();
//			printf("Section - 1 thread - %d\n", rank);
//			//Sleep(100);
//		}
//#pragma omp section
//		{
//			rank = omp_get_thread_num();
//			printf("Section - 2 thread - %d\n", rank);
//			Sleep(100);
//		}
//#pragma omp section
//		{
//			rank = omp_get_thread_num();
//			printf("Section - 3 thread - %d\n", rank);
//			Sleep(100);
//		}
//#pragma omp section
//		{
//			rank = omp_get_thread_num();
//			printf("Section - 4 thread - %d\n", rank);
//			Sleep(100);
//		}
//	}

#pragma omp parallel private(rank)
	{
		double t1 = omp_get_wtime();
#pragma omp for
		for (int i = 0; i < 100; i++)
		{

			rank = omp_get_thread_num();
			printf("Iter - %d thread - %d\n", i, rank);
		}

		//#pragma omp barrier
		
#pragma omp critical
		{
			double t2 = omp_get_wtime();
			printf("%d %f\n", rank, t2 - t1);
		}
#pragma omp atomic
		k+=5;


	}

	system("pause");
}