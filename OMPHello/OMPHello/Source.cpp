#include <iostream>
#include <omp.h>
#include <Windows.h>
using namespace std;

int main()
{
	int kol = 10;
	int k = 10;
//#pragma omp parallel num_threads(10) shared(kol) firstprivate(k)
//	{
//		int id, size;
//		id = omp_get_thread_num();
//		size = omp_get_num_threads();
//		
//		kol += id;
//		k += id;
//		printf("proc - %d kol = %d k = %d!\n", id, kol, k);
//	}
//	printf("after kol = %d  k = %d\n", kol, k);

//#pragma omp parallel 
//	{
//
//#pragma omp	sections 
//		{
//#pragma omp section
//			{
//				Sleep(1000);
//				printf("Section - 0 proc - %d\n",
//					omp_get_thread_num());
//			}
//#pragma omp section
//			{
//				printf("Section - 1 proc - %d\n",
//					omp_get_thread_num());
//			}
//#pragma omp section
//			{
//				Sleep(1000);
//				printf("Section - 2 proc - %d\n",
//					omp_get_thread_num());
//			}
//#pragma omp section
//			{
//				Sleep(1000);
//				printf("Section - 3 proc - %d\n",
//					omp_get_thread_num());
//			}
//#pragma omp section
//			{
//
//				printf("Section - 4 proc - %d\n",
//					omp_get_thread_num());
//			}
//		}
//
//	}

	int k1 = 0, max = 0;
	
#pragma omp parallel for //schedule(guided, 10)
	for (int i = 0; i < 100000; i++)
	{
//#pragma omp atomic
//		k1+=5;
		k1 = rand() % 100;
		if (k1 > max)
#pragma omp critical
		{
			if (k1 > max)
				max = k1;
		}
		//printf("Iter - %d proc - %d\n", i, omp_thread_num());
	}

	printf("k = %d\n", k1);

	system("pause");
	return 0;
}