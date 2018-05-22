#include <stdio.h>
#include <omp.h>
#define qntThread 4000

static long num_steps = 100000;
double somas[qntThread];
double step;



void main(){
    double pi = 0.0;
    step = 1.0/(double) num_steps;

    #pragma omp parallel num_threads(qntThread)
    {
        double x,soma = 0.0;
        int num = omp_get_thread_num();
        int stepT = num_steps/qntThread;
        int rect = 0;
        for (int i = 0; i< stepT; i++){
            rect = i+stepT*num;
            x = (rect+0.5)*step;
            soma = soma + 4.0/(1.0 + x*x);
            
        }
        printf("O da soma interna é: %f , da thread: %d\n", soma*step,num);
        somas[num] = soma;
    }
    double soma = 0.0;
    for(int i = 0; i< qntThread; i++){
        soma += somas[i];
    }
    pi = step*soma;
    printf("O valor de pi é: %f \n", pi);



}





