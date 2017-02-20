#include <iostream>
#include <mpi.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	const int N = 20;
	double a[N], procSum, Sum, Sum2=0;
	int rank, size;
	srand((unsigned)time(0));

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (!rank)
	{
		for (int i = 0; i < N; i++)
		{
			a[i] = rand() % 100 - 50;
			Sum2 += a[i];
			printf("%3f ", a[i]);
		}
	}

	MPI_Bcast(a, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	int k = N / size;
	int i1 = k*rank;
	int i2 = k*(rank+1);
	if (rank == size - 1)
		i2 = N;

	procSum = 0;
	//for (int i = i1; i < i2; i++)
		//procSum += a[i];
	for(int i=rank; i<N; i+=size)
		procSum += a[i];
	//printf("\nrank-%d i1=%d i2=%d procSum=%f", rank,i1,i2, procSum);

	MPI_Reduce(&procSum, &Sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (!rank)
		printf("\n Sum=%f  Sum2=%f\n", Sum, Sum2);

	MPI_Finalize();




}