#include <iostream>
#include <mpi.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	const int N = 20;
	int rank, size;
	double a[N], sum = 0, sum1=0, procSum = 0;

	srand(time(0));
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (!rank) //rank==0
	{
		for (int i = 0; i < N; i++)
		{
			a[i] = rand() % 100;
			printf("%f ", a[i]);
			sum1 += a[i];
		}
		printf("\n");
	}

	MPI_Bcast(a, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	int k = N / size;
	int i1 = k*rank;
	int i2 = k*(rank + 1);
	if (rank == size - 1)
		i2 = N;

	for (int i = i1; i < i2; i++)
		procSum += a[i];


	MPI_Reduce(&procSum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(!rank)
		printf("sum=%f sum1=%f\n", sum, sum1);


	//if (rank)
	//{
	//	MPI_Send(&procSum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	//}
	//else
	//{
	//	MPI_Status st;
	//	sum = procSum;
	//	for (int i = 1; i < size; i++)
	//	{
	//		MPI_Recv(&procSum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
	//		sum += procSum;
	//	}
	//	printf("sum=%f sum1=%f\n", sum,sum1);
	//}
	
	MPI_Finalize();

}