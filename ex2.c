#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define MASTER 0

int main(int argc,char *argv[]){
	int rank;
	int size;
	int data;
	double t1,t2;
	int resp;
	MPI_Request send_request, recv_request;
	MPI_Status status;
	if(rank == 0)
		t1 = MPI_Wtime();
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);//define o rank do processo
	data = rank;  //Cada tarefa deve enviar à sua tarefa destino uma única mensagem contendo um número inteiro indicando seu ranking 
	MPI_Comm_size(MPI_COMM_WORLD, &size); //define o numero de tarefas

	/*if(rank == MASTER){
		printf("Mestre");
		printf("%d",size);
	}*/

	if(size%2 != 0){
		MPI_Finalize();
		exit(0);	
	}

	if(rank < size/2){
		int destination = size/2 + rank;
		int source = size/2 + rank;
		MPI_ISend(&data, 1, MPI_INT, destination, 0, MPI_COMM_WORLD,&send_request);
		printf("Tarefa %d enviou tarefa para %d.\n", rank, destination);
		MPI_IRecv(&data, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &recv_request);
		printf("Tarefa %d recebeu tarefa de %d.\n", rank, source);
	} else {
		int destination = rank - size/2;
		int source = rank - size/2;
		MPI_ISend(&data, 1, MPI_INT, destination, 1, MPI_COMM_WORLD,&send_request);
		printf("Tarefa %d enviou tarefa para %d.\n", rank, destination);
		MPI_IRecv(&data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &recv_request);
		printf("Tarefa %d recebeu tarefa de %d.\n", rank, source);

	}
	
	resp = MPI_Wait(&send_request, &status);
	resp = MPI_Wait(&recv_request, &status);
	
	if(rank == 0){
		t2 = MPI_Wtime();
		printf("Duracao: %f\n", t2-t1);
	}	

	MPI_Finalize();
	return 0;
}
