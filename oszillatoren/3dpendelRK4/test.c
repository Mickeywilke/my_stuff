#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>


#define T 100    // Laufzeit
#define h 0.001    // Schrittweite
#define g 9.81     // bekannt
#define m 1    // Masse
#define L 3    //  Stange


double f2(double phi, double theta, double phid, double thetad) {
    return sin(theta) * ( - g + L * cos(theta) * phid * phid ) / L;
}

double f1(double phi, double theta, double phid, double thetad) {
    double thetanew = fmod(fabs(theta+M_PI),2*M_PI)-M_PI ;
    return  - 2 * thetad * phid / (thetanew + pow(thetanew, 3) / 3 + pow(thetanew, 5) / 5) ;
}
//phi1 = phi, phi2 = theta

int main() {
    double t, phi1 =  1, phi2 = 1, omega1 = 1, omega2 = 0, phi1p, phi2p, omega1p, omega2p, kphi11, kphi12, kphi21, kphi22, kphi13, kphi14, kphi23, kphi24, komega11, komega12, komega13, komega14, komega21, komega22, komega23, komega24; //siehe RK4 für die Faktoren und die formeln die kommen
    
    freopen ("3dpendel.txt","w", stdout);

    for (t = 0; t < T ; t += h) {
        kphi11 = omega1;
        kphi21 = omega2;
        komega11 = f1(phi1, phi2, omega1, omega2) ;
        komega21 = f2(phi1, phi2, omega1, omega2);
        kphi12 = omega1+h*komega11/2 ;
        kphi22 = omega2+h*komega21/2 ;
        komega12 = f1(phi1 + kphi11 * h / 2, phi2 + kphi21 * h / 2, kphi12, kphi22) ;
        komega22 = f2(phi1 + kphi11 * h / 2, phi2 + kphi21 * h / 2, kphi12, kphi22) ;
        kphi13 = omega1+h*komega12/2 ;
        kphi23 = omega2+h*komega22/2 ;
        komega13 = f1(phi1 + kphi12 * h / 2, phi2 + kphi22 * h / 2, kphi13, kphi23) ;
        komega23 = f2(phi1 + kphi12 * h / 2, phi2 + kphi22 * h / 2, kphi13, kphi23) ;
        kphi14 = omega1+h*komega13 ;
        kphi24 = omega2+h*komega23 ;
        komega14 = f1(phi1 + kphi13 * h , phi2 + kphi23 * h , kphi14, kphi24) ;
        komega24 = f2(phi1 + kphi13 * h , phi2 + kphi23 * h , kphi14, kphi24) ;
        phi1p = phi1 + h * ( kphi11 + 2 * kphi12 + 2 * kphi13 + kphi14) / 6;
        phi2p = phi2 + h * ( kphi21 + 2 * kphi22 + 2 * kphi23 + kphi24) / 6;
        omega1p = omega1 + h * ( komega11 + 2 * komega12 + 2 * komega13 + komega14) / 6;
        omega2p = omega2 + h * ( komega21 + 2 * komega22 + 2 * komega23 + komega24) / 6;
        printf("%g, %g, %g, %g, %g \n", t, phi1, phi2, omega1, omega2);
        phi1 = phi1p;
        phi2 = phi2p;
        omega1 = omega1p ;
        omega2 = omega2p ;
    }
    return 0;
}