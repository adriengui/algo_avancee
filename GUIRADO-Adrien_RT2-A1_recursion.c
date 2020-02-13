#include <stdio.h>

double facto_ite(double n){
    if(n==0){
        return 1;
    }
    else{
        for(int y=n-1;y>0;y--) n*=y;
        return n;
    }
}

double facto_rec(double n){
    if(n==0){
        return 1;
    }
    else{
        return n*facto_rec(n-1);
    }
}

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\n");

    int i=6;
    printf("%d! par la maniere iterative : %g\n\n",i,facto_ite(i));

    int r=7;
    printf("%d! par la maniere recursive : %g\n\n",r,facto_rec(r));

	return 0;
}
