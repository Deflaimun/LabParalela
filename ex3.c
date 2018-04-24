	#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MASTER 0
#define ARRAYSIZE 1600000

int main(int argc, char *argv[]){
	int i; 
	int destino;
	int offset;
	float data[ARRAYSIZE];
	int rank;
	int size;
	int tag1 = 1;
	int tag2 = 2;
	int len;
	float sum;
	float totalSum;
	double t1, t2;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int parcela = ARRAYSIZE/size;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	MPI_Get_processor_name(hostname, &len);
	
	


	if(rank == 0){
		t1 = MPI_Wtime();
		totalSum = 0;
		for(i=0; i<ARRAYSIZE; i++){
			data[i] = i * 1.0;
			totalSum = totalSum + data[i];
		}
		
		offset = parcela;
		for(destino=1; destino<size; destino++){
			MPI_Send(&offset, 1, MPI_INT, destino, tag1, MPI_COMM_WORLD);
			MPI_Send(&data[offset], parcela, MPI_FLOAT, destino, tag2, MPI_COMM_WORLD);
			offset = offset + parcela;
		}

		offset = 0;
		sum = 0;

		for(i=offset; i<offset + parcela; i++){
			data[i] = data[i] + i * 1.0;
			sum = sum + data[i];
		}

		for(i=1; i<size; i++){
			MPI_Recv(&offset, 1, MPI_INT, i, tag1, MPI_COMM_WORLD, &status);
			MPI_Recv(&data[offset], parcela, MPI_FLOAT, i, tag2, MPI_COMM_WORLD, &status);
		}

		MPI_Reduce(&sum, &totalSum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

		offset = 0;

		int j = 0;
		for (i=0; i<size; i++) {
		    printf("Tarefa: %d (%s) ->", i, hostname);
		    for (j=0; j<5; j++) 
		      printf("  %e",data[offset+j]);
		    printf("\n");
		    offset = offset + parcela;
    		}

		printf("Soma Total = %e\n", totalSum);
		t2 = MPI_Wtime();
		printf("O tempo gasto foi de %f\n", t2-t1);

	} else {
		MPI_Recv(&offset, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD,&status);
		MPI_Recv(&data[offset], parcela, MPI_FLOAT, 0, tag2, MPI_COMM_WORLD,&status);
		sum = 0;
		for(i=offset; i<offset + parcela; i++){
			data[i] = data[i] + i * 1.0;
			sum = sum + data[i];
		}
			MPI_Send(&offset, 1, MPI_INT, 0, tag1, MPI_COMM_WORLD);
			MPI_Send(&data[offset], parcela, MPI_FLOAT, 0, tag2, MPI_COMM_WORLD);
			MPI_Reduce(&sum, &totalSum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
