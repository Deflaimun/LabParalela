#include <omp.h>
#include <stdio.h>
void main(){

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("hello (%d)", id);
        printf(" world (%d) \n", id);
    }

}