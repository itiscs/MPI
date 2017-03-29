#include <iostream>
#include <mpi.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	const int N = 20;
	int rank, size, procN;
	double a[N], *procA, sum = 0, sum1 = 0, procSum = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	srand(time(0));
	if (!rank)
	{
		for (int i = 0; i < N; i++)
		{
			a[i] = i;	
			sum1 += a[i];
		}
	}

	int *len = new int[size];
	int *ind = new int[size];
	int rest, k;

	rest = N;
	k = rest / size;
	len[0] = k;
	ind[0] = 0;
	for (int i = 1; i < size; i++)
	{
		rest -= k;
		k = rest / (size - i);
		len[i] = k;
		ind[i] = ind[i - 1] + len[i - 1];
	}

	procN = len[rank];
	procA = new double[procN];

	MPI_Scatterv(a, len, ind, MPI_DOUBLE, procA, procN, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	delete len;
	delete ind;
	
	for (int i = 0; i < procN; i++)
		procSum +=  procA[i];

	MPI_Reduce(&procSum, &sum, 1, MPI_DOUBLE, MPI_SUM,0, MPI_COMM_WORLD);

	delete procA;

	if(!rank)
		printf("\nsum=%f sum1=%f\n", sum, sum1);


	MPI_Finalize();

}