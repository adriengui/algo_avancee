#include <stdio.h>

double facto_ite(double n){
    if(n==0)
        return 1;
    else{
        for(int y=n-1;y>0;y--) n*=y;
        return n;
    }
}

double facto_rec(double n){
    if(n==0)
        return 1;
    else
        return n*facto_rec(n-1);
}

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\nNombre : ");

    int i=0;
    scanf("%d",&i);
    printf("%d! par la maniere iterative : %g\n\n%d! par la maniere recursive : %g\n\n",i,facto_ite(i),i,facto_rec(i));

    return 0;
}
