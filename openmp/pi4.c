#include <stdio.h>

static long num_steps = 100000;
double step;
void main(){
    double pi,soma = 0.0;
    step = 1.0/(double) num_steps;

    #pragma omp parallel for reduction (+:soma)
    for (int i = 0; i< num_steps; i++){
        double x = (i+0.5)*step;
        soma = soma + 4.0/(1.0 + x*x);

    }
    
    pi = step*soma;
    printf("O valor de pi é: %f \n", pi);
}