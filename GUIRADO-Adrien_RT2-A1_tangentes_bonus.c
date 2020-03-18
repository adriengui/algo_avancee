#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void aff(double tab[], int a){
    int z=0;
    for(int x=0;x<a;x++){
        z++;
        if(tab[x]!=0)
            break;
    }
    int zz=a-z+1;
    double tab2[zz];
    for(int x=0;x<zz;x++)
        tab2[x]=tab[a-zz+x];
    int b=0;
    for(int x=0;x<zz;x++){
        if(tab2[x]!=0){
            b=zz-x-1;
            if(tab2[x]>0 && x>0)
                printf("+");
            printf("%g",tab2[x]);
            if(b>1)
                printf("x%d",b);
            else if(b==1)
                printf("x");
        }
    }
}

double eval(double tab[], int a, double x){
    double res=0;
    for(int y=0;y<a;y++)
        res+=tab[y]*pow(x,a-y-1);
    return res;
}

void deriv(double tab[], int a, double res[]){
        int b=a-1;
        for(int x=0;x<b;x++)
            res[x]=tab[x]*(b-x);
}

void remp(double a[],int l, int deb, int fin){
    for(int x=0;x<l;x++)
        a[x]=rand()%(fin+1-deb)+deb;
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\n");

    int z=4;
    double f[z],fp[z-1];
    f[0]=1;
    f[1]=-5;
    f[2]=2;
    f[3]=4;

    deriv(f,z,fp);

    int x=0;
    float a[50]={0},b=0;

    printf("Polynome : \n\n");
    aff(f,z);
    printf("\n\n");

    while(1){
        printf("x0 (200 pour quitter) : ");
        scanf("%f",&b);
        if(b==200)
            break;
        a[0]=b;
        for(x=1;x<50;x++)
            a[x]=a[x-1]-(eval(f,z,a[x-1])/eval(fp,z-1,a[x-1]));
        if(a[48]==a[49])
            printf("%g\n\n",a[49]);
        else
            printf("Aucune solution trouvee pour le x0 donne\n\n");
    }

	return 0;
}
