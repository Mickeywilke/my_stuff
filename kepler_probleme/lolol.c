#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define T 30     // Laufzeit
#define h 0.001    // Schrittweite
#define G 1   // Newton
#define m1 7 // erste Masse
#define m2 600 // zweite masse

int main() {
    double t, r, r0, r10[3], r20[3], v10[3], v20[3], a10[3], r1[3], v1[3], a1[3],  r2[3], v2[3], a2[3];
    r10 [0] = 0;
    r10 [1] = 0;
    r10 [2] = 0;
    v10 [0] = 0;
    v10 [1] = 0;
    v10 [2] = 0;   
    r20 [0] = 2;
    r20 [1] = 2;
    r20 [2] = 0;
    v20 [0] = -1;
    v20 [1] = -3;
    v20 [2] = -5;
    int i;
    freopen ("2_3dbody.txt","w", stdout);
    for (t = 0; t < T ; t += h)  {
        r0 = sqrt( pow((r10[0] - r20[0]), 2) + pow((r10[1] - r20[1]), 2) + pow((r10[2] - r20[2]), 2));
        for (i = 0; i < 3; i++) {
            a10[i] =  G * (r20[i] - r10[i]) / (r0*r0*r0);
            r1[i] = r10[i] + h * v10[i] + h *h * m2 * a10[i] / 2;
            r2[i] = r20[i] + h * v20[i] + h * h * m1 * ( - a10[i]) / 2;
            }
        r = sqrt( pow(r1[0] - r2[0], 2) + pow(r1[1] - r2[1], 2) +pow((r1[2] - r2[2]), 2));
        for (i = 0; i < 3; i++) {
            a1[i] =  G * (r2[i] - r1[i]) / (r*r*r);
            v1[i] = v10[i] +  h * m2 * (a1[i] + a10[i]) / 2;
            v2[i] = v20[i] +  h * m1 * ( -a1[i] - a10[i]) / 2;
            }
        printf("%g, %g, %g, %g, %g, %g, %g\n", t, r10[0], r10[1], r10[2], r20[0], r20[1], r20[2]);
        for (i = 0; i < 3; i++) {
            r10[i] = r1[i];
            r20[i] = r2[i];
            v10[i] = v1[i];
            v20[i] = v2[i];
        }
    }
    return 0;
}