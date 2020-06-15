#include <stdio.h>
#include <math.h>

double f(double x){
    return(20*(x-2)*exp(x-2)+2);
    // return(-5*pow(x,2)-3*x+8);
    // return((15/exp(x))*log(x)-0.5);
    // return(pow(x,3)+pow(x,2)-5*x);
    // return(sqrt(x));
}

double fp(double x){
    return(20*(x-1)*exp(x-2));
    // return(-10*x-3);
    // return((15-15*x*log(x))/(x*exp(x)));
    // return(3*pow(x,2)+2*x-5);
    // return(1/(2*sqrt(x)));
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
            printf("\n\n%d\n%lf\n\n",x,b);
        else
            printf("\n\nNon trouve\n\n");
    }
}

int main(){

    printf("GUIRADO Adrien - RT2 A1\n\nMethode des tangentes\n\n");

    tang();

    return 0;
}
