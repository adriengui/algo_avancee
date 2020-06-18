#include <stdio.h>
#include <math.h>

double f(double x){
    return(pow(x,2)*log(x+10)-20);
}

double rec(double deb, double fin, double pas){
    double somme=0;
    int n=(fin-deb)/pas;
    for(int x=0;x<n;x++){
        somme+=pas*f(deb);
        deb+=pas;
    }
    return somme;
}

double tra(double deb, double fin, double pas){
    double somme=0;
    int n=(fin-deb)/pas;
    for(int x=0;x<n;x++){
        somme+=0.5*pas*(f(deb)+f(deb+pas));
        deb+=pas;
    }
    return somme;
}

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\nCalcul d'integrales\n\n");

    double a=0,b=0,p=1,r=0,t=0,i=0;
    int n=0;

    printf("f(x) = x^2*ln(x+10)-20\n\
Df = ]-10 ; + infini[\n\n\n");

    while(p != 0){
        printf("A : ");
        scanf("%lf",&a);
        printf("\nB : ");
        scanf("%lf",&b);
        printf("\nPas (0 pour quitter) : ");
        scanf("%lf",&p);
        printf("\n");
        if(p>0 && a>-10 && b>-10 && a < b){
            r=rec(a,b,p);
            t=tra(a,b,p);
            i=(b*(3*pow(b,2)*log(b+10)-pow(b,2)+15*b-480)-a*(3*pow(a,2)*log(a+10)-pow(a,2)+15*a-480)+3000*(log(b+10)-log(a+10)))/9;
            n=(b-a)/p;

            printf("Intervalle = %g ; %g\n\
Pas = %g\n\
Nb d'iterations = (%g - %g)/%g = %d\n\n\
Integrale calculee = %g\n\n\n\
Methode des rectangles = %g\n\n\
Pourcentage d'erreur = ((%g - %g)*100)/%g = %g pourcents\n\n\n\
Methode des trapezes = %g\n\n\
Pourcentage d'erreur = ((%g - %g)*100)/%g = %g pourcents\n\n\n"
,a,b,p,b,a,p,n,i,r,i,r,i,((i-r)*100)/i,t,i,t,i,((i-t)*100)/i);
        }
    }

    return 0;
}
