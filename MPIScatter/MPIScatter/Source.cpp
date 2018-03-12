#include <iostream>
#include <mpi.h>
//#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	const int N = 20;
	int rank, size, procN;
	double a[N], *procA, sum = 0, sum1 = 0, procSum = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//srand();
	if (!rank) // rank == 0
	{
		for (int i = 0; i < N; i++)
		{
			a[i] = (double)(rand() % 100) / 100;
			printf("%f ", a[i]);
			sum1 += a[i];
		}
		printf("\n");

	}


	MPI_Finalize();

}