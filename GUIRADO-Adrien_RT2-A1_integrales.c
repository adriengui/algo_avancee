#include <stdio.h>
#include <math.h>

double f(double n){
    return(2*pow(n,5)+3*pow(n,3)-4*pow(n,2)+1);
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

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\n");

printf("%g\n\n",rec(-2,2,0.00005));



    return 0;
}
