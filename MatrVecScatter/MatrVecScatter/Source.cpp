#include <iostream>
#include <mpi.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
	const int N = 20;
	int rank, size, procN;
	double a[N*N], b[N], c[N];
	double *procA, *procC;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand(time(NULL));
	if (!rank) // rank == 0
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				a[i*N + j] = i * N + j;// (double)(rand() % 100) - 50;
			b[i] = i;// (double)(rand() % 100) - 50;
		}
	}

	int* len = new int[size], *lenc = new int[size];
	int* ind = new int[size], *indc = new int[size];

	int rest = N;
	int k = rest / size;
	len[0] = k * N; lenc[0] = k;
	ind[0] = 0;     indc[0] = 0;
	for (int i = 1; i < size; i++)
	{
		rest -= k;
		k = rest / (size - i);
		len[i] = k * N;    lenc[i] = k;
		ind[i] = ind[i - 1] + len[i - 1];
		indc[i] = indc[i - 1] + lenc[i - 1];
	}

	procN = len[rank];
	procA = new double[procN];
	procC = new double[lenc[rank]];

	MPI_Scatterv(a, len, ind, MPI_DOUBLE, procA, procN, MPI_DOUBLE,
		0, MPI_COMM_WORLD);
	MPI_Bcast(b, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	for(int i=0; i<procN/N; i++)
	{
		procC[i] = 0;
	//	printf("rank=%d ", rank);
	//	printf(" procA[%d,0]=%f ", i, procA[i*N]);
		for (int j = 0; j < N; j++)
			procC[i] += procA[i*N + j] * b[j];
			//printf(" procA[%d,%d]=%f ", i,j, procA[i*N + j]);
		//printf("procC[%d] = %f\n",i,procC[i]);
	}
	//printf("rank=%d len = %d  ind = %d\n", rank,len[rank],ind[rank]);

	MPI_Gatherv(procC, lenc[rank], MPI_DOUBLE, c, lenc, indc, MPI_DOUBLE,
		0, MPI_COMM_WORLD);

	if (!rank) // rank == 0
	{
		for (int i = 0; i < N; i++)
		{
			printf("c[%d] = %f\n",i,c[i]);
		}
	}

	MPI_Finalize();

}