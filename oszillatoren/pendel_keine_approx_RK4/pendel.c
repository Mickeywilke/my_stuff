#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define T 300 // Laufzeit
#define H 0.1 // Schrittweite
#define G 0.25 // damping
#define w0 1 // oszillatorfrequenz
#define A 0.9 // Amplitude der Anregung
#define wT (2.0/3.0) // anregende Frequenz

int main() {
    double t = 0.0, phialt = M_1_PI,  phi = phialt, phin;
    FILE* f = fopen("pendel.txt", "w");

    while (t < T) {

        phin = 2.0*H*H/(2.0+G*H)*(A*cos(wT*t)-w0*w0*sin(phi))
        + 4.0/(2.0+G*H)*phi - phialt*(2.0-G*H)/(2.0+G*H);

        fprintf(f,"%g, %g, %g\n", t, phi, (phin-phialt)/H);

        phialt = phi; phi = phin;
        t += H;
    }
}