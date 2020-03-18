#include <stdio.h>
#include <math.h>

double f(double x){
    return(exp(x-2)*20*(x-2)+2);
}

double fp(double x){
    return(20*x*exp(x-2)-20*exp(x-2));
}

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\n");

    int x=0;
    float a[50]={0},b=0;

    while(1){
        printf("x0 (200 pour quitter) : ");
        scanf("%f",&b);
        if(b==200)
            break;
        a[0]=b;
        for(x=1;x<50;x++)
            a[x]=a[x-1]-(f(a[x-1])/fp(a[x-1]));
        if(a[48]==a[49])
            printf("%g\n\n",a[49]);
        else
            printf("Aucune solution trouvee pour le x0 donne\n\n");
    }

    return 0;
}
