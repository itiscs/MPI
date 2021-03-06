#include <iostream>
#include <mpi.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	const int N = 20;
	int rank, size;
	double a[N], sum = 0, sum1 = 0, procSum = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand(time(0));
	if (!rank)
	{
		for (int i = 0; i < N; i++)
		{
			a[i] = rand() % 100;
			printf("%f ", a[i]);
			sum1 += a[i];
		}
	}

	//MPI_Bcast(a, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	int *len = new int[size];
	int *ind = new int[size];

	int rest = N;
	int k = rest / size;
	len[0] = k;
	ind[0] = 0;

	for (int i = 1; i < size; i++)
	{
		rest -= k;
		k = rest / (size - i);
		len[i] = k;
		ind[i] = ind[i - 1] + len[i - 1];
	}

	int nProc = len[rank];
	double *aProc = new double[nProc];

	MPI_Scatterv(a, len, ind, MPI_DOUBLE, aProc, nProc,
		MPI_DOUBLE, 0, MPI_COMM_WORLD);

	procSum = 0;
	for (int i = 0; i < nProc; i++)
	{
		//printf("rank - %d  a[%d]=5%d ",rank,i,aProc[i]);
		procSum += aProc[i];
	}
	MPI_Reduce(&procSum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (!rank)
		printf("\nsum=%f sum1=%f\n", sum, sum1);

	MPI_Finalize();

}