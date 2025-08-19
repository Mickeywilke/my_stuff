#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>


#define T 10     // Laufzeit
#define h 0.01    // Schrittweite
#define g 9.81     // bekannt
#define m1 1    // erste Masse
#define m2 1    // zweite Masse
#define L1 1    // erste Stange
#define L2 1    // zweite Stange

double f1(double phi1, double phi2, double omega1, double omega2) {
    return (-g*(2*m1+m2)*sin(phi1)-m2*g*sin(phi1-2*phi2)-2*sin(phi1-phi2)*m2*(omega2*omega2*L2+omega1*omega1*L1*cos(phi1-phi2))) / (L1*(2*m1+m2-m2*cos(2*(phi1-phi2))));
}

double f2(double phi1, double phi2, double omega1, double omega2) {
        return 2*sin(phi1-phi2)*(omega1*omega1*L1*(m1+m2)+g*(m1+m2)*cos(phi1)+omega2*omega2*L2*m2*cos(phi1-phi2)) / (L2*(2*m1+m2-m2*cos(2*(phi1-phi2)))) ;
    }

int main() {
    double t, phi1 =  M_PI, phi2 = M_PI-0.01, omega1 = 0.0, omega2 = 0.0, phi1p, phi2p, omega1p, omega2p, kphi11, kphi12, kphi21, kphi22, kphi13, kphi14, kphi23, kphi24, komega11, komega12, komega13, komega14, komega21, komega22, komega23, komega24; //siehe RK4 für die Faktoren und die formeln die kommen
    
    freopen ("doppelpendel.txt","w", stdout);

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