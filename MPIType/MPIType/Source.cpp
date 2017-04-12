#include <iostream>
#include <mpi.h>
#include <time.h>

using namespace std;
struct Person
{
	int id;
	char fio[30];
	int age;
};

int main(int argc, char* argv[])
{
	const int N = 6;
	int rank, size;
	int a[N*N], sum = 0, sum1 = 0, procSum = 0;
	Person pers;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	srand((unsigned)time(0));
	if (!rank)
	{
		int k = 1;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				a[i*N + j] = k++;
				printf("%d ", a[i*N + j]);
			}
			printf("\n");
		}
		pers.id = 1;
		pers.age = 20;
	    strcpy_s(pers.fio, "Ivanov");
		printf("\nPerson {%d, %s, %d}\n", pers.id, pers.fio, pers.age);
//		printf("indexes -  %d  - %d\n", (char*)pers.fio - (char*)&pers.id,
//			(char*)&pers.age - (char*)&pers.id);

	}

	MPI_Datatype newType, strType, oldTypes[3] = { MPI_INT,MPI_CHAR, MPI_INT };
	int len[N], ind[N];
	for (int i = 0; i < N; i++)
	{
		len[i] = i + 1; //N - i;
		ind[i] = i*N; //i*N + i;
	}
	int len1[3] = { 4, 30, 4 }, ind1[3] = { 0, 4, 34};


	//MPI_Type_contiguous(N, MPI_INT, &newType);  //непрерывный способ
	//MPI_Type_vector(N / 2, N, 2 * N, MPI_INT, &newType); //векторный способ
	//MPI_Type_vector(N, 1, N+1, MPI_INT, &newType);  //гл.диагональ
	MPI_Type_indexed(N, len, ind, MPI_INT, &newType);  //индексный способ
	MPI_Type_create_struct(3, len1, ind1, oldTypes, &strType); // структурный способ

	MPI_Type_commit(&newType);
	MPI_Type_commit(&strType);

	MPI_Bcast(&pers, 1, strType, 0, MPI_COMM_WORLD);
	if (!rank)
	{
		MPI_Send(a, 1, newType, 1, 0, MPI_COMM_WORLD);
	}
	else // rank != 0
	{
		int n = N*(N + 1) / 2;
		int b[N*(N + 1) / 2];
		MPI_Status st;
		MPI_Recv(b, n, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
		for (int j = 0; j < n; j++)
			printf("%d ", b[j]);
		printf("\nPerson {%d, %s, %d}\n", pers.id, pers.fio, pers.age);


	}
	//for (int i = 0; i < N; i++)
	//{
	//	for (int j = 0; j < N; j++)
	//	{
	//		printf("%d ", a[i*N + j]);
	//	}
	//	printf(" --- row=%d proc=%d  \n", i, rank);
	//}


	MPI_Type_free(&strType);
	MPI_Type_free(&newType);
	MPI_Finalize();

}