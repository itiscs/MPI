#include <iostream>
#include <mpi.h>
using namespace std;

int main()
{
	const int N = 6;
	int* matr = new int[N*N], len[N],ind[N];
	int rank, size, recv, kol=0;
	MPI_Status st;
	MPI_Datatype uptreug;

	for (int i = 0; i < N; i++)
	{
		len[i] = N - i;
		ind[i] = i*N + i;
		kol += len[i];
	}
	
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Type_indexed(N, len, ind, MPI_INT, &uptreug);
	MPI_Type_commit(&uptreug);


	if (!rank) // rank == 0 на с++
		for (int i = 0; i < N*N; i++)
			matr[i] = i+1;
	else
		for (int i = 0; i < N*N; i++)
			matr[i] = 0;
	
	int psize = kol / size;
	int* a = new int[psize+1];
	for (int i = 0; i < psize; i++)
		a[i] = 0;
	printf("proc-%d psize-%d\n",rank,psize);
	//MPI_Bcast(matr, 1, uptreug, 0, MPI_COMM_WORLD);
	MPI_Scatter(matr, 1, uptreug, a, psize, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < psize; i++)
		printf("%d ", a[i]);

	printf("\n");

	MPI_Finalize();

	return 0;
}