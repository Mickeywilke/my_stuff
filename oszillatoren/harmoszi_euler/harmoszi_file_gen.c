#include <stdio.h>

#define T 30       // Laufzeit
#define h 0.01    // Schrittweite
#define omega 1   // Frequenz

int main() {
    double t, x = 0.0, v = 1.0, xp, vp;

    for (t = 0; t < T ; t += h)  {
        xp = x + h*v;
        vp = v - omega*omega*x*h;
        freopen ("harmoszidata.txt","a+", stdout);
        printf("%g, %g, %g\n", t, x, v);
        x = xp;
        v = vp;

    }
   
}