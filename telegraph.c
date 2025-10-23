#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include "marsenne_twister.h"
#include <omp.h>


#define increment 1e-15
#define num_traj 100
#define r1 2 /*first transition prob*/
#define r2 2 /*second transition prob*/
#define T 1000
#define time_step 0.001


int main() {
    time_t start, end;
    time(&start); 
    int i;
    srand(1);
    FILE *file = fopen("telegraph.txt","w");
    for(i=0; i<num_traj; i++){

        int a = rand();
        unsigned long long init[4]={a,1,3,4}, length=4;
        init_by_array64(init, length);

        double t, s, x, x0, b;
        x0 = -1; /*initial condition!*/
        
        for(t=0; t<=T+increment; t+=time_step){
            b = genrand64_real1();
            if (x0 == -1) {
                if (b < r1 * time_step) {
                    x = 1;
                }
                else {
                    x = -1;
                }
            }
            else {
                if (b < r2 * time_step) {
                    x = -1;
                }
                else{
                    x=1;
                }
            }
            fprintf(file, "%g, %g\n", t, x0);
           
            x0 = x;   
        }
    }
    time(&end); 
    double time_taken = (end - start);
    fclose(file);
    printf("Time taken: %gs", time_taken); 
    return 0;
}