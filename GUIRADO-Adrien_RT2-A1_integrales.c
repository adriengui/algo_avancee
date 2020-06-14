#include <stdio.h>
#include <math.h>

double f(double x){
    // return(2*pow(x,5)+3*pow(x,3)-4*pow(x,2)+1);
    // return(pow(x,3)-5*x);
    // return(2*pow(x,3)-5*pow(x,2)+2);
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

    printf("GUIRADO Adrien - RT2 A1\n\n");

    double d=-5,f=7.5,p=0.5,i=211.8;
    int n=(f-d)/p;

    printf("Exemple :\n\n\
f(x) = x^2*ln(x+10)-20\n\
Intervalle = %g ; %g\n\
Pas = %g\n\
Nb d'iterations = (%g - %g)/%g = %g/%g = %d\n\n\
Integrale calculee = %g\n\n\
Methode des rectangles = %g\n\n\
Pourcentage d'erreur = ((%g-%g)*100)/%g = (%g*100)/%g = %g/%g = %g pourcents\n\n\
Methode des trapezes = %g\n\n\
Pourcentage d'erreur = ((%g-%g)*100)/%g = (%g*100)/%g = %g/%g = %g pourcents\n\n"
,d,f,p,f,d,p,f-d,p,n,i,rec(d,f,p),i,rec(d,f,p),i,i-rec(d,f,p),i,(i-rec(d,f,p))*100,i,((i-rec(d,f,p))*100)/i,tra(d,f,p),i,tra(d,f,p),i,i-tra(d,f,p),i,(i-tra(d,f,p))*100,i,((i-tra(d,f,p))*100)/i);

    return 0;
}
