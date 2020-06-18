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

    printf("GUIRADO Adrien - RT2 A1\n\nFactorielles\n\n");

    int i=0,t=0;
    while(i != -1){
        printf("Nombre (-1 pour quitter) : ");
        scanf("%d",&i);
        t=2;
        if(i>=0){
            while(t!=0 && t!=1){
                printf("\nFacon (0=ite et 1=rec) : ");
                scanf("%d",&t);
            }
            if(t)
                printf("\n%d! = %lf\n",i,facto_rec(i));
            else
                printf("\n%d! = %lf\n",i,facto_ite(i));
        }
        printf("\n");
    }

    return 0;
}
