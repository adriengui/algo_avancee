#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int deg(double *t, int a){
    int z=0;
    for(int x=0;x<a;x++){
        z++;
        if(t[x]!=0)
            break;
    }
    return a-z;
}

void aff(double *tab, int a){
    if(deg(tab,a)==0 && tab[a-1]==0)
        printf("0");
    else{
        int z=deg(tab,a)+1;
        double tab2[z];
        for(int x=0;x<z;x++)
            tab2[x]=tab[a-z+x];
        int b=0;
        for(int x=0;x<z;x++){
            if(tab2[x]!=0){
                b=z-x-1;
                if(tab2[x]>0 && x>0)
                    printf("+");
                if(tab2[x]==-1)
                    if(x==z-1)
                        printf("-1");
                    else
                        printf("-");
                else if(tab2[x]!=1 && b<z)
                    printf("%g",tab2[x]);
                else if(x==z-1 && tab2[x]==1)
                    printf("1");
                if(b>1)
                    printf("x^%d",b);
                else if(b==1)
                    printf("x");
            }
        }
    }
}

int pos(double *t, int a){
    int i=0;
    while(t[i]==0)
        i++;
    return i;
}

double eval(double *tab, int a, double x){
    double res=0;
    for(int y=0;y<a;y++)
        res+=tab[y]*pow(x,a-y-1);
    return res;
}

void deriv(double *tab, int a, double *res){
        int b=a-1;
        for(int x=0;x<b;x++)
            res[x]=tab[x]*(b-x);
}

void addi(double *tab, int a,double *tab2, int b, double *res){
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
}

void remp(double *a,int l, int deb, int fin){
    for(int y=0;y<l;y++) a[y]=0;
    while(a[0]==0)
        for(int x=0;x<l;x++)
            a[x]=rand()%(fin+1-deb)+deb;
}

void mul(double *tab, int a,double *tab2, int b, double *res){
    for(int x=0;x<a+b-1;x++) res[x]=0;
    for(int x=0;x<a;x++)
        for(int y=0;y<b;y++)
            res[x+y]+=tab[x]*tab2[y];
}

void saisie(int *test, double *a, int s){
    while(*test != 0 && *test != 1){
        printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
        scanf("%d",&*test);
    }
    if(*test==1)
        remp(a,s,-10,10);
    else{
        for(int y=0;y<s;y++){
            printf("x^%d : ",s-y-1);
            scanf("%lf",&a[y]);
        }
    }
}

void dim(int *t, char a){
    while(*t<0){
        printf("\nDeg %c : ",a);
        scanf("%d",&*t);
    }
}

void tang(double *tab, int l){
    int x=0;
    float a,b,t;
    double der[l-1];
    deriv(tab,l,der);
    while(1){
        printf("x0 (200 pour quitter) : ");
        scanf("%f",&a);
        if(a==200)
            break;
        x=0;
        while(a!=b && x<50){
            b=a-(eval(tab,l,a)/eval(der,l-1,a));
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

void menu(){
    printf("\n1 : Polynome basique\n\
2 : Derivee polynome\n\
3 : Somme polynomes\n\
4 : Produit polynomes\n\n");
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\nMethode des tangentes sur les polynomes\n\nPolynome a evaluer :\n");

    int k=1;

    while(k != 0){
        menu();
        printf("Operation souhaitee (0 pour quitter) : ");
        scanf("%d",&k);
        switch(k){
            case 1:
            {
                int a_s=-1,aff_test=2;
                printf("Polynome basique :\n");
                dim(&a_s,'A');
                if(a_s<1)
                    printf("\nDerivee nulle");
                else{
                    a_s++;
                    double a[a_s];
                    saisie(&aff_test,a,a_s);
                    printf("\nA = ");
                    aff(a,a_s);
                    printf("\n\n\n");
                    tang(a,a_s);
                }
                printf("\n\n");

                break;
            }

            case 2:
            {
                int c_s=-1,deriv_test=2;
                printf("Derivee polynome :\n");
                dim(&c_s,'A');
                if(c_s<2)
                    printf("\nDerivee seconde nulle");
                else{
                    c_s++;
                    double c[c_s],d[c_s-1];
                    saisie(&deriv_test,c,c_s);
                    deriv(c,c_s,d);
                    printf("\nA = ");
                    aff(c,c_s);
                    printf("\n\nA' = ");
                    aff(d,c_s-1);
                    printf("\n\n\n");
                    tang(d,c_s-1);
                }
                printf("\n\n");

                break;
            }

            case 3:
            {
                int f_s=-1,g_s=-1,add_test=2,add_test2=2;
                printf("\n\nSomme de 2 polynomes :\n");
                dim(&f_s,'A');
                f_s++;
                double f[f_s];
                saisie(&add_test,f,f_s);
                printf("\nA = ");
                aff(f,f_s);
                printf("\n");
                dim(&g_s,'B');
                if(g_s+f_s<2)
                    printf("\nDerivee nulle");
                else{
                    g_s++;
                    double g[g_s];
                    saisie(&add_test2,g,g_s);
                    int add_s=0;
                    if(f_s>g_s)
                        add_s=f_s;
                    else
                        add_s=g_s;
                    double h[add_s];
                    addi(f,f_s,g,g_s,h);
                    printf("\nB = ");
                    aff(g,g_s);
                    printf("\n\nA + B = ");
                    aff(h,add_s);
                    printf("\n\n\n");
                    tang(h,add_s);
                }
                printf("\n\n");

                break;
            }

            case 4:
            {
                int i_s=-1,j_s=-1,mul_test=2,mul_test2=2;
                printf("\n\nProduit de 2 polynomes :\n");
                dim(&i_s,'A');
                i_s++;
                double i[i_s];
                saisie(&mul_test,i,i_s);
                printf("\nA = ");
                aff(i,i_s);
                printf("\n");
                dim(&j_s,'B');
                if(i_s+j_s<2)
                    printf("\nDerivee nulle");
                else{
                    j_s++;
                    double j[j_s];
                    saisie(&mul_test2,j,j_s);
                    int mul_s=i_s+j_s-1;
                    double ks[mul_s];
                    mul(i,i_s,j,j_s,ks);
                    printf("\nB = ");
                    aff(j,j_s);
                    printf("\n\nA x B = ");
                    aff(ks,mul_s);
                    printf("\n\n\n");
                    tang(ks,mul_s);
                }
                printf("\n\n");

                break;
            }
        }
    }

	return 0;
}
