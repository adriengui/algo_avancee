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

int deg(double t[], int a){
    int z=0;
    for(int x=0;x<a;x++){
        z++;
        if(t[x]!=0)
            break;
    }
    return a-z;
}

int eval(double tab[], int a, double x, double *res0){
    double res=0;
    for(int y=0;y<a;y++)
        res+=tab[y]*pow(x,a-y-1);
    *res0=res;
    return 0;
}

int deriv(double tab[], int a, double res[]){
    if(deg(tab,a)>0){
        int b=a-1;
        for(int x=0;x<b;x++)
            res[x]=tab[x]*(b-x);
        return 0;
    }
    else
        return 1;
}

int addi(double tab[], int a,double tab2[], int b, double res[]){
    if(a>b){
        for(int d=0;d<a;d++)
            res[d]=tab[d];
        for(int x=0;x<b;x++)
            res[a-b+x]+=tab2[x];
    }
    else{
        for(int d=0;d<b;d++)
            res[d]=tab2[d];
        for(int x=0;x<a;x++)
            res[b-a+x]+=tab[x];
    }
    return 0;
}

void remp(double a[],int l, int deb, int fin){
    for(int x=0;x<l;x++)
        a[x]=rand()%(fin+1-deb)+deb;
}

int mul(double tab[], int a,double tab2[], int b, double res[]){
    remp(res,a+b-1,0,0);
    for(int x=0;x<a;x++)
        for(int y=0;y<b;y++)
            res[x+y]+=tab[x]*tab2[y];
    return 0;
}

int divi(double ta[], int a,double ta2[], int b, double quotient[], double reste[]){
    if(deg(ta,a)>=deg(ta2,b)){
        if(deg(ta2,b)==0){
            for(int x=0;x<a;x++)
                quotient[x]=ta[x]/ta2[b-1];
            remp(reste,a,0,0);
        }
        else{
            double res[a-b+1],res_bis[a-b+1],tab[a],tab_bis[a],tab2[b],tab3[a];
            for(int z=0;z<a;z++)
                tab[z]=ta[z];
            for(int zz=0;zz<b;zz++)
                tab2[zz]=ta2[zz];
            int aa=0;
            while(deg(tab,a)>=deg(tab2,b)){
                if(tab[aa]!=0){
                    for(int p=0;p<a-b+1;p++)
                        res_bis[p]=0;
                    res[aa]=tab[a-1-deg(tab,a)]/tab2[0];
                    res_bis[aa]=res[aa];
                    mul(tab2,b,res_bis,a-b+1,tab_bis);
                    for(int y=0;y<a;y++)
                        tab_bis[y]=-tab_bis[y];
                    for(int x=0;x<a;x++)
                        tab3[x]=tab[x];
                    addi(tab3,a,tab_bis,a,tab);
                    aa++;
                }
                else aa++;
            }
            for(int x=0;x<a-b+1;x++)
                quotient[x]=res[x];
            for(int y=0;y<a;y++)
                reste[y]=tab[y];
        }
        return 0;
    }
    else
        return 1;
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\n");

    printf("Affichage polynome :\n\n");
    double a[8];
    int a_s=sizeof(a)/sizeof(double);
    remp(a,a_s,-10,10);
    aff(a,a_s);

    printf("\n\n\nEvaluation d'un polynome en un x donne : \nPolynome :\n\n");
    double b[4],res_eval=0;
    int b_s=sizeof(b)/sizeof(double),c=rand()%20-10;
    remp(b,b_s,-10,10);
    aff(b,b_s);
    eval(b,b_s,c,&res_eval);
    printf("\n\nEval en x = %d : %g\n\n\n",c,res_eval);

    printf("Derivee d'un polynome :\nPolynome :\n\n");
    double d[7];
    int d_s=sizeof(d)/sizeof(double),res_deriv;
    remp(d,d_s,-10,10);
    double e[d_s-1];
    aff(d,d_s);
    printf("\n\nDerivee :\n\n");
    if(res_deriv=deriv(d,d_s,e)){
        switch(res_deriv){
        case 1:
            printf("Degre nul");
            break;
        }
    }
    else
        aff(e,d_s-1);

    printf("\n\n\nAjout de 2 polynomes :\nPolynome A :\n\n");
    double f[7],g[6],h[7];
    int f_s=sizeof(f)/sizeof(double),g_s=sizeof(g)/sizeof(double);
    remp(f,f_s,-10,10);
    remp(g,g_s,-10,10);
    addi(f,f_s,g,g_s,h);
    aff(f,f_s);
    printf("\n\nPolynome B :\n\n");
    aff(g,g_s);
    printf("\n\nA + B :\n\n");
    aff(h,7);

    printf("\n\n\nMultiplication de 2 polynomes :\nPolynome A :\n\n");
    int aa=4,bb=3;
    double i[aa],j[bb],k[aa+bb-1];
    remp(i,aa,-10,10);
    remp(j,bb,-10,10);
    mul(i,aa,j,bb,k);
    aff(i,aa);
    printf("\n\nPolynome B :\n\n");
    aff(j,bb);
    printf("\n\nA x B :\n\n");
    aff(k,aa+bb-1);

    printf("\n\n\nDivision de 2 polynomes :\nPolynome A :\n\n");
    int aa2=6,bb2=4,divi0=0;
    double l[aa2],m[bb2],quotient[aa2-bb2+1],reste[aa2];
    remp(l,aa2,-10,10);
    remp(m,bb2,-10,10);
    aff(l,aa2);
    printf("\n\nPolynome B :\n\n");
    aff(m,bb2);
    if(divi0=divi(l,aa2,m,bb2,quotient,reste)){
        switch(divi0){
        case 1:
            printf("Deg B > Deg A");
            break;
        }
    }
    else{
        printf("\n\nQuotient :\n\n");
        aff(quotient,aa2-bb2+1);
        printf("\n\nReste :\n\n");
        aff(reste,aa2);
    }
    printf("\n\n");

	return 0;
}
