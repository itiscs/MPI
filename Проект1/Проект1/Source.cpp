#include <iostream>
#include <mpi.h>
using namespace std;

void main()
{
	int rank, size, k;
	MPI_Status st;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank)
	{
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else
	{
		printf("Hello from process %d out of %d\n", rank, size);
		for (int i = 1; i < size; i++)
		{
	MPI_Recv(&k, 1, MPI_INT, i, MPI_ANY_TAG,
				MPI_COMM_WORLD, &st);
	printf("Hello from process %d out of %d\n", k, size);

		}
	}



	MPI_Finalize();

	//system("pause");
}