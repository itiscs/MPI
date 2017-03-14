#include <iostream>
#include <mpi.h>
using namespace std;

int main()
{
	int rank, size, recv;
	MPI_Status st;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (!rank) // rank == 0 на с++
	{
		printf("Hello from process %d out of %d!\n", rank, size);
		for (int i = 1; i < size; i++)
		{
			MPI_Recv(&recv, 1, MPI_INT, size-i, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
			printf("recv=%d st.source=%d!\n", recv, st.MPI_SOURCE);
		}
	}
	else
	{
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

	}	

	MPI_Finalize();

	return 0;
}