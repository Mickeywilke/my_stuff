#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>


#define T 10     // Laufzeit
#define h 0.1    // Schrittweite
#define g 9.81     // bekannt
#define m1 1    // erste Masse
#define m2 1    // zweite Masse
#define m3 1    // dritte Masse
#define L1 1    // erste Stange
#define L2 1    // zweite Stange
#define L3 1    // dritte Stange

//stimmen nur für gleiche massen und stangenlängen aber wirken sowieso trotzdem falsch

double f1(double phi1, double phi2, double phi3, double omega1, double omega2, double omega3) {
    return 0.375 * L1 * sin(phi1 + M_PI / 4) * cos(2 * phi1 - 2 * phi2) * pow(omega1, 2) 
           - 0.625 * L1 * sin(phi1 + M_PI / 4) * pow(omega1, 2) 
           + 0.1875 * L1 * sin(phi1 - phi2) * cos(phi1 + M_PI / 4) * cos(2 * phi1 - 2 * phi2) * pow(omega2, 2) 
           - 0.40625 * L1 * sin(phi1 - phi2) * cos(phi1 + M_PI / 4) * pow(omega2, 2) 
           + 0.75 * L1 * sin(phi1 - phi2) * cos(phi2 + M_PI / 4) * pow(omega1, 2) 
           - 0.375 * L1 * sin(2 * phi1 - 2 * phi2) * cos(phi1 + M_PI / 4) * pow(omega1, 2) 
           + 0.1875 * L1 * sin(2 * phi1 - 2 * phi2) * cos(phi2 + M_PI / 4) * pow(omega2, 2) 
           - 0.09375 * L1 * sin(3 * phi1 - 3 * phi2) * cos(phi1 + M_PI / 4) * pow(omega2, 2) 
           + 0.1875 * L1 * sin(phi2 + M_PI / 4) * cos(2 * phi1 - 2 * phi2) * pow(omega2, 2) 
           - 0.3125 * L1 * sin(phi2 + M_PI / 4) * pow(omega2, 2) 
           - 0.0625 * L1 * sin(phi1 - 2 * phi2 + phi3 + M_PI / 4) * cos(phi1 + M_PI / 4) * pow(omega3, 2) 
           - 0.25 * L1 * cos(phi1 + M_PI / 4) * cos(2 * phi1 - 2 * phi2) * cos(phi3) * pow(omega3, 2) 
           + 0.4167 * L1 * cos(phi1 + M_PI / 4) * cos(phi3) * pow(omega3, 2) 
           - 0.5 * L1 * cos(phi1 + M_PI / 4) * cos(phi1 - phi2) * cos(phi2 + M_PI / 4) * cos(phi3) * pow(omega3, 2) 
           - 0.0625 * L1 * cos(phi1 + M_PI / 4) * cos(-phi1 + 2 * phi2 + phi3 + M_PI / 4) * pow(omega3, 2) 
           + 0.0625 * L1 * cos(phi1 + M_PI / 4) * cos(3 * phi1 - 2 * phi2 - phi3 + M_PI / 4) * pow(omega3, 2) 
           - 0.0625 * L1 * cos(phi1 + M_PI / 4) * cos(3 * phi1 - 2 * phi2 + phi3 + M_PI / 4) * pow(omega3, 2) 
           + 0.375 * L1 * cos(2 * phi1 - 2 * phi2) * cos(phi3) * pow(omega3, 2) 
           + 0.5 * L1 * cos(phi2 + M_PI / 4) * cos(phi3) * pow(omega3, 2) 
           - 0.625 * L1 * cos(phi3) * pow(omega3, 2) 
           + 0.1042 * g * (2 * cos(2 * phi1 + M_PI / 4) + 2) 
           + 0.125 * g * (2 * cos(2 * phi2 + M_PI / 4) + 2) 
           - 0.125 * g * cos(phi1 + M_PI / 4) * cos(phi1 - 2 * phi2) 
           - 0.25 * g * cos(phi1 + M_PI / 4) * cos(2 * phi1 - 2 * phi2) * cos(phi1) 
           + 0.125 * g * cos(phi1 + M_PI / 4) * cos(3 * phi1 - 2 * phi2) 
           - 0.5 * g * cos(phi1 - phi2) * cos(phi2 + M_PI / 4) * cos(phi1) 
           + 0.1875 * g * cos(2 * phi1 - 2 * phi2) 
           - 0.3125 * g * L1 * (0.0625 * sin(-phi1 + 2 * phi2 + phi3 + M_PI / 4) * cos(phi1 + M_PI / 4)
           + 0.0625 * sin(3 * phi1 - 2 * phi2 - phi3 + M_PI / 4) * cos(phi1 + M_PI / 4)
           - 0.0625 * sin(3 * phi1 - 2 * phi2 + phi3 + M_PI / 4) * cos(phi1 + M_PI / 4)
           + 0.25 * sin(phi3) * cos(phi1 + M_PI / 4) * cos(2 * phi1 - 2 * phi2)
           - 0.4167 * sin(phi3) * cos(phi1 + M_PI / 4)) ;
}

double f2(double phi1, double phi2, double phi3, double omega1, double omega2, double omega3) {
    return (0.166666666666667 * sin(2 * phi1) - 0.25 * cos(2 * phi1 - 2 * phi2) + 0.583333333333333) +
           (1.0 * L1 * sin(phi1 - phi2) * omega1 * omega1) +
           (0.25 * L1 * sin(2 * phi1 - 2 * phi2) * omega2 * omega2) +
           (0.0833333333333333 * g * sin(2 * phi1 - phi2)) +
           (-0.0833333333333333 * g * sin(phi2)) +
           (-0.416666666666667 * g * cos(2 * phi1 - phi2)) +
           (0.416666666666667 * g * cos(phi2));
}

double f3(double phi1, double phi2, double phi3, double omega1, double omega2, double omega3) {
    return (L1 * (0.166666666666667 * sin(2 * phi1) - 0.25 * cos(2 * phi1 - 2 * phi2) + 0.583333333333333)) -
           (0.416666666666667 * L1 * sin(phi1 - phi2) * omega2 * omega2) -
           (0.25 * L1 * sin(2 * phi1 - 2 * phi2) * omega1 * omega1) -
           (0.0833333333333333 * L1 * cos(phi1 + phi2) * omega2 * omega2) -
           (0.166666666666667 * L1 * cos(2 * phi1) * omega1 * omega1) -
           (0.0416666666666667 * g * sin(phi1 - 2 * phi2)) +
           (0.0416666666666667 * g * sin(phi1)) -
           (0.208333333333333 * g * cos(phi1 - 2 * phi2)) +
           (0.458333333333333 * g * cos(phi1)) ;
}

int main() {
    double t, phi1 =  0, phi2 = 0, phi3 = 0, omega1 = 0.0, omega2 = 0.0, omega3 = 0, phi1p, phi2p, phi3p, omega1p, omega2p, omega3p, kphi11, kphi12, kphi31, kphi21, kphi22, kphi33, kphi32, kphi34, kphi13, kphi14, kphi23, kphi24, komega11, komega12, komega13, komega14, komega21, komega22, komega23, komega24, komega31, komega32, komega33, komega34; //siehe RK4 für die Faktoren und die formeln die kommen
    
    freopen ("trippelpendel.txt","w", stdout);

    for (t = 0; t < T ; t += h) {
        kphi11 = omega1;
        kphi21 = omega2;
        kphi31 = omega3;
        komega11 = f1(phi1, phi2, phi3, omega1, omega2, omega3) ;
        komega21 = f2(phi1, phi2, phi3, omega1, omega2, omega3);
        komega31 = f3(phi1, phi2, phi3, omega1, omega2, omega3);
        kphi12 = omega1+h*komega11/2 ;
        kphi22 = omega2+h*komega21/2 ;
        kphi32 = omega3+h*komega31/2 ;
        komega12 = f1(phi1 + kphi11 * h / 2, phi2 + kphi21 * h / 2, phi3 + kphi31 * h / 2 ,kphi12, kphi22, kphi32) ;
        komega22 = f2(phi1 + kphi11 * h / 2, phi2 + kphi21 * h / 2, phi3 + kphi31 * h / 2 ,kphi12, kphi22, kphi32) ;
        komega32 = f3(phi1 + kphi11 * h / 2, phi2 + kphi21 * h / 2, phi3 + kphi31 * h / 2 ,kphi12, kphi22, kphi32) ;
        kphi13 = omega1+h*komega12/2 ;
        kphi23 = omega2+h*komega22/2 ;
        kphi33 = omega3+h*komega32/2 ;
        komega13 = f1(phi1 + kphi12 * h / 2, phi2 + kphi22 * h / 2, phi3 + kphi32 * h / 2 ,kphi13, kphi23, kphi33) ;
        komega23 = f2(phi1 + kphi12 * h / 2, phi2 + kphi22 * h / 2, phi3 + kphi32 * h / 2 ,kphi13, kphi23, kphi33) ;
        komega33 = f3(phi1 + kphi12 * h / 2, phi2 + kphi22 * h / 2, phi3 + kphi32 * h / 2 ,kphi13, kphi23, kphi33) ;
        kphi14 = omega1+h*komega13 ;
        kphi24 = omega2+h*komega23 ;
        kphi34 = omega3+h*komega33 ;
        komega14 = f1(phi1 + kphi13 * h, phi2 + kphi23 * h , phi3 + kphi33 * h,  kphi14, kphi24, kphi34) ;
        komega24 = f2(phi1 + kphi13 * h, phi2 + kphi23 * h , phi3 + kphi33 * h,  kphi14, kphi24, kphi34) ;
        komega34 = f3(phi1 + kphi13 * h, phi2 + kphi23 * h , phi3 + kphi33 * h,  kphi14, kphi24, kphi34) ;
        phi1p = phi1 + h * ( kphi11 + 2 * kphi12 + 2 * kphi13 + kphi14) / 6;
        phi2p = phi2 + h * ( kphi21 + 2 * kphi22 + 2 * kphi23 + kphi24) / 6;
        phi3p = phi3 + h * ( kphi31 + 2 * kphi32 + 2 * kphi33 + kphi34) / 6;
        omega1p = omega1 + h * ( komega11 + 2 * komega12 + 2 * komega13 + komega14) / 6;
        omega2p = omega2 + h * ( komega21 + 2 * komega22 + 2 * komega23 + komega24) / 6;
        omega2p = omega3 + h * ( komega31 + 2 * komega32 + 2 * komega33 + komega34) / 6;

        printf("%g, %g, %g, %g, %g, %g, %g \n", t, phi1, phi2, phi3, omega1, omega2, omega3);
        phi1 = phi1p;
        phi2 = phi2p;
        phi3 = phi3p;
        omega1 = omega1p ;
        omega2 = omega2p ;
        omega3 = omega3p ;
    }
    return 0;
}







