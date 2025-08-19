//damped harmonic oscillator mit RK4

#include <stdio.h>
#include <math.h>

#define T 30     // Laufzeit
#define h 0.01    // Schrittweite
#define omega 1   // Frequenz
#define d 1       // damping

int main() {
    remove("dampharmo.txt");
    double t, x = 0, v = 1.0, xp, vp, kx1, kx2, kx3, kx4, kv1, kv2, kv3, kv4;    //siehe RK4 für die Faktoren und die formeln die kommen
    for (t = 0; t < T ; t += h)  {
        kx1 = v;
        kv1 = - pow(omega, 2) * x - d * v;
        kx2 = v + h * kv1 / 2;
        kv2 = - pow(omega, 2) * ( x + h * kx1 / 2) - d * kv1;
        kx3 = v + h * kv2 / 2;
        kv3 = - pow(omega, 2) * ( x + h * kx2 / 2) - d * kv2;
        kx4 = v + h * kv2;
        kv4 = - pow(omega, 2) * ( x + h * kx3) - d * kv2;
        xp = x + h * ( kx1 + 2 * kx2 + 2 * kx3 + kx4) / 6;
        vp = v + h * ( kv1 + 2 * kv2 + 2 * kv3 + kv4) / 6;
        freopen ("dampharmo.txt","a+", stdout);
        printf("%g, %g, %g\n", t, x, v);
        x = xp;
        v = vp;

    }
   
}