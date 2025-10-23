#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include "marsenne_twister.h"
#include <omp.h>

#define increment 1e-6
#define num_traj 1000
#define gamma 1
#define D 0.1
#define T 1000
#define time_step 0.001


int main() {
    time_t start, end;
    time(&start); 
    int i;
    srand(1);
    FILE *file = fopen ("oup.txt","w");
    for(i=0; i<num_traj; i++){

        int a = rand();
        unsigned long long init[4]={a,1,3,4}, length=4;
        init_by_array64(init, length);

        double t, v, v0;
        v0 = 0; /*initial condition!*/
        
        for(t=0; t<=T+increment; t+=time_step){
            
            v = v0 * (1 - gamma * time_step) + sqrt(2 * D * time_step)*gaussian();
            fprintf(file, "%g, %g\n", t, v0);
            v0 = v;
            
        }
    }
    time(&end); 
    double time_taken = (end - start);
    fclose(file);
    printf("Time taken: %gs", time_taken);    
    return 0;
}