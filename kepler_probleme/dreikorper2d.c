#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define T 5     // Laufzeit
#define h 0.001    // Schrittweite
#define G 1   // Newton
#define m1 100 // erste Masse
#define m2 10 // zweite masse
#define m3 10 // dritte masse

int main() {
    double t, r12, r13, r23, r120, r130, r230, r10[2], r20[2], r30[2], v10[2], v20[2], v30[2], a120[2], 
    a130[2], a230[0], r1[2], v1[2], a12[2],  r2[2], v2[2], a13[2], r3[2], v3[2], a23[2];
    r10 [0] = 0;
    r10 [1] = 1;
    v10 [0] = 1;
    v10 [1] = -1;
    r20 [0] = 2;
    r20 [1] = 2;
    v20 [0] = -1;
    v20 [1] = 1;
    r30 [0] = 1;
    r30 [1] = 0;
    v30 [0] = 1;
    v30 [1] = 1;
    int i;
    freopen ("3_body.txt","w", stdout);
    for (t = 0; t < T ; t += h)  {
        r120 = sqrt( pow((r10[0] - r20[0]), 2) + pow((r10[1] - r20[1]), 2) );
        r130 = sqrt( pow((r10[0] - r30[0]), 2) + pow((r10[1] - r30[1]), 2) );
        r230 = sqrt( pow((r20[0] - r30[0]), 2) + pow((r20[1] - r30[1]), 2) );
        for (i = 0; i < 2; i++) {
            a120[i] =  G * (r20[i] - r10[i]) / (r120*r120*r120);
            a130[i] =  G * (r30[i] - r10[i]) / (r130*r130*r130);
            a230[i] =  G * (r30[i] - r20[i]) / (r230*r230*r230);
            r1[i] = r10[i] + h * v10[i] + h *h * ( m2 * a120[i] + m3 * a130[i] ) / 2;
            r2[i] = r20[i] + h * v20[i] + h * h * ( - m1 * a120[i] + m3 * a230[i]) / 2;
            r3[i] = r30[i] + h * v30[i] + h * h * ( - m1 * a130[i] - m2 * a230[i]) / 2;
            }
        r12 = sqrt( pow(r1[0] - r2[0], 2) + pow(r1[1] - r2[1], 2) );
        r13 = sqrt( pow((r1[0] - r3[0]), 2) + pow((r1[1] - r3[1]), 2) );
        r23 = sqrt( pow((r2[0] - r3[0]), 2) + pow((r2[1] - r3[1]), 2) );
        for (i = 0; i < 2; i++) {
            a12[i] =  G * (r2[i] - r1[i]) / (r12*r12*r12);
            a13[i] =  G * (r3[i] - r1[i]) / (r13*r13*r13);
            a23[i] =  G * (r3[i] - r2[i]) / (r23*r23*r23);
            v1[i] = v10[i] +  h * ( m2 * (a12[i] + a120[i]) + m3 * (a13[i] + a130[i])) / 2;
            v2[i] = v20[i] +  h * ( - m1 * ( a12[i] + a120[i]) + m3 * (a23[i] + a230[i])) / 2;
            v3[i] = v30[i] +  h * ( - m1 * ( a13[i] + a130[i]) + m2 * (a23[i] + a230[i])) / 2;
        }
        printf("%g, %g, %g, %g, %g, %g, %g\n", t, r10[0], r10[1], r20[0], r20[1], r30[0], r30[1]);
        for (i = 0; i < 2; i++) {
            r10[i] = r1[i];
            r20[i] = r2[i];
            r30[i] = r3[i];
            v10[i] = v1[i];
            v20[i] = v2[i];
            v30[i] = v3[i];
        }
    }
    return 0;
}