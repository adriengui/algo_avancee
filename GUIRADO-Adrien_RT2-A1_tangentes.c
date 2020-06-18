#include <stdio.h>
#include <math.h>

double f(double x){
    return(20*(x-2)*exp(x-2)+2);
}

double fp(double x){
    return(20*(x-1)*exp(x-2));
}

void tang(){
    int x=0;
    float a,b,t;

    while(1){
        printf("x0 (200 pour quitter) : ");
        scanf("%f",&a);
        if(a==200)
            break;
        x=0;
        while(a!=b && x<50){
            b=a-(f(a)/fp(a));
            t=a;
            a=b;
            b=t;
            x++;
        }
        if(x<50)
            printf("\n%d iterations\n\nx = %lf\n\n\n",x,b);
        else
            printf("\nNon trouve\n\n\n");
    }
}

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\nMethode des tangentes\n\nf(x)=20(x-2)e^(x-2)+2\n\n\n");

    tang();

    return 0;
}
