#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define T 10000     // Laufzeit
#define h 0.1    // Schrittweite
#define G 1   // Newton
#define m0 1 // Sonne
#define m1 1 // merkur
#define m2 1 // venus
#define m3 1 // erde
#define m4 1 // mars
#define m5 1 // jupiter
#define m6 1 // saturn
#define m7 1 // uranus
#define m8 1 // neptun

int main(){
    double t, 
    e[8], e0[8],
    r0x[8], r0y[8] = {0}, rx[8], ry[8], v0x[8] = {0}, v0y[8], vx[8], vy[8], a0x[8], a0y[8], ax[8], ay[8];
    r0x[0] = 0.39;
    r0x[1] = 0.72;
    r0x[2] = 1;
    r0x[3] = 1.5;
    r0x[4] = 5.2;
    r0x[5] = 9.6;
    r0x[6] = 19.2;
    r0x[7] = 30.1;
    v0y[0] = 1.58;
    v0y[1] = 1.17;
    v0y[2] = 1;
    v0y[3] = 0.80;
    v0y[4] = 0.44;
    v0y[5] = 0.32;
    v0y[6] = 0.23;
    v0y[7] = 0.18;

    double alpha; 
    alpha = - G * m0;

    int i;
    freopen ("solar_system.txt","w", stdout);
    for (t = 0; t < T ; t += h){
        for (i = 0; i < 8; i++){
            e0[i] = sqrt(pow(r0x[i], 2) + pow(r0y[i], 2));
            a0x[i] = alpha * r0x[i] / (pow(e0[i], 3));
            a0y[i] = alpha * r0y[i] / (pow(e0[i], 3));

            rx[i] = r0x[i] + h * v0x[i] + pow(h, 2) * ax[i] / 2;
            ry[i] = r0y[i] + h * v0y[i] + pow(h, 2) * ay[i] / 2;
            e[i] = sqrt(pow(rx[i], 2) + pow(ry[i], 2));
            ax[i] = alpha * rx[i] / pow(e[i], 3);
            ay[i] = alpha * ry[i] / pow(e[i], 3);
            vx[i] = v0x[i] + h * (ax[i] + a0x[i]) / 2;
            vy[i] = v0y[i] + h * (ay[i] + a0y[i]) / 2;
        }
        printf("%g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g\n", 
                 t,r0x[0], r0y[0], r0x[1], r0y[1],r0x[2], r0y[2],r0x[3], r0y[3],r0x[4], r0y[4],r0x[5], r0y[5],
                r0x[6], r0y[6],r0x[7], r0y[7]);
        for (i = 0; i < 8; i++){
            r0x[i] = rx[i];
            r0y[i] = ry[i];
            v0x[i] = vx[i];
            v0y[i] = vy[i];
        }    
    }
    return 0;
}

