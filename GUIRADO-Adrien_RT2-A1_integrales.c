#include <stdio.h>
#include <math.h>

double f(double x){
    // return(2*pow(x,5)+3*pow(x,3)-4*pow(x,2)+1);
    return(pow(x,3)-5*x);
}

double rec(double deb, double fin, double pas){
    double n2=(fin-deb)/pas,a=deb,somme=0;
    int n=n2;
    printf("%d\n\n",n);
    double tab[n];
    for(int x=0;x<n;x++){
        tab[x]=pas*f(a);
        a+=pas;
    }
    for(int y=0;y<n;y++)
        somme+=tab[y];
    return somme;
}

double tra(double deb, double fin, double pas){
    double n2=(fin-deb)/pas,a=deb,somme=0;
    int n=n2;
    printf("%d\n\n",n);
    double tab[n];
    for(int x=0;x<n;x++){
        tab[x]=pas*f(a)+0.5*pas*(f(a+pas)-f(a));
        a+=pas;
    }
    for(int y=0;y<n;y++)
        somme+=tab[y];
    return somme;
}

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\n");

    double d=-3,f=5,p=0.00005;
printf("%g\n\n",rec(d,f,p));
printf("\n\n%lf\n\n",tra(d,f,p));


    return 0;
}
