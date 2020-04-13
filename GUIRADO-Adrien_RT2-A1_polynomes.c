#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void aff(double *tab, int a){
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

int pos(double *t, int a){
    int i=0;
    while(t[i]==0)
        i++;
    return i;
}

int deg(double *t, int a){
    int z=0;
    for(int x=0;x<a;x++){
        z++;
        if(t[x]!=0)
            break;
    }
    return a-z;
}

void eval(double *tab, int a, double x, double *res0){
    double res=0;
    for(int y=0;y<a;y++)
        res+=tab[y]*pow(x,a-y-1);
    *res0=res;
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

int division(double *ta, int a,double *ta2, int b, double *quotient, double *reste){
    if(deg(ta2,b)>deg(ta,a))
        return 1;
    else if(deg(ta2,b)==0 && ta2[b-1]==0)
        return 2;
    else{
        int l=deg(ta,a)-deg(ta2,b)+1,la1=deg(ta,a)+1,la2=deg(ta2,b)+1;
        double tab[la1],tab2[la2];
        for(int x=0;x<la1;x++) tab[x]=ta[x+pos(ta,a)];
        for(int x=0;x<la2;x++) tab2[x]=ta2[x+pos(ta2,b)];
        double tabbis[la1],quobis[l];
        for(int x=0;x<l;x++){
            for(int u=0;u<l;u++) quobis[u]=0;
            quotient[x]=tab[la1-deg(tab,la1)-1]/tab2[0];
            quobis[x]=quotient[x];
            mul(tab2,la2,quobis,l,tabbis);
            for(int y=0;y<la1;y++) tabbis[y]=-tabbis[y];
            for(int z=0;z<la1;z++) tab[z]+=tabbis[z];
        }
        for(int x=0;x<a;x++) reste[x]=0;
        for(int x=0;x<la1;x++) reste[a-la1+x]=tab[x];

        return 0;
    }
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\nCalculs sur les polynomes\n\nOperations :\n\n1 : Affichage polynome\n2 : Evaluation polynome\n3 : Derivee polynome\n4 : Somme polynomes\n5 : Produit polynomes\n6 : Division polynomes\n\n");

    int k=1;

    while(k != 0){
        printf("Operation souhaitee (0 pour quitter) : ");
        scanf("%d",&k);
        switch(k){
            case 1:
            {
                int a_s=0,aff_test=2;
                printf("Affichage polynome :\n\nDegre du polynome : ");
                scanf("%d",&a_s);
                a_s++;
                while(aff_test != 0 && aff_test != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&aff_test);
                }
                double a[a_s];
                if(aff_test==1)
                    remp(a,a_s,-10,10);
                else{
                    for(int y=0;y<a_s;y++){
                        printf("x^%d : ",a_s-y-1);
                        scanf("%lf",&a[y]);
                    }
                }
                aff(a,a_s);
                printf("\n\n");

                break;
            }

            case 2:
            {
                int b_s=0,eval_test=2,c1=0;
                printf("Evaluation polynome :\n\nDegre du polynome : ");
                scanf("%d",&b_s);
                b_s++;
                while(eval_test != 0 && eval_test != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&eval_test);
                }
                double b[b_s],res_eval=0;
                if(eval_test==1)
                    remp(b,b_s,-10,10);
                else{
                    for(int y=0;y<b_s;y++){
                        printf("x^%d : ",b_s-y-1);
                        scanf("%lf",&b[y]);
                    }
                }
                printf("\n");
                aff(b,b_s);
                printf("\n\nValeur de x : ");
                scanf("%d",&c1);
                eval(b,b_s,c1,&res_eval);
                printf("\n\nEval en x = %d : %g\n\n\n",c1,res_eval);

                break;
            }

            case 3:
            {
                int c_s=0,deriv_test=2;
                printf("Derivee polynome :\n\nDegre du polynome : ");
                scanf("%d",&c_s);
                c_s++;
                while(deriv_test != 0 && deriv_test != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&deriv_test);
                }
                double c[c_s],d[c_s-1];
                if(deriv_test==1)
                    remp(c,c_s,-10,10);
                else{
                    for(int y=0;y<c_s;y++){
                        printf("x^%d : ",c_s-y-1);
                        scanf("%lf",&c[y]);
                    }
                }
                deriv(c,c_s,d);
                printf("Polynome :\n\n");
                aff(c,c_s);
                printf("\nDerivee : \n\n");
                aff(d,c_s-1);
                printf("\n\n");
                break;
            }

            case 4:
            {
                int f_s=0,g_s=0,add_test=2,add_test2=2;
                printf("\n\nSomme de 2 polynomes :\n\nDegre polynome A : ");
                scanf("%d",&f_s);
                f_s++;
                double f[f_s];
                while(add_test != 0 && add_test != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&add_test);
                }
                if(add_test==1)
                    remp(f,f_s,-10,10);
                else{
                    for(int y=0;y<f_s;y++){
                        printf("x^%d : ",f_s-y-1);
                        scanf("%lf",&f[y]);
                    }
                }
                printf("\nPolynome A :\n");
                aff(f,f_s);
                printf("\n\nDegre polynome B : ");
                scanf("%d",&g_s);
                g_s++;
                double g[g_s];
                while(add_test2 != 0 && add_test2 != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&add_test2);
                }
                if(add_test2==1)
                    remp(g,g_s,-10,10);
                else{
                    for(int y=0;y<g_s;y++){
                        printf("x^%d : ",g_s-y-1);
                        scanf("%lf",&g[y]);
                    }
                }
                int add_s=0;
                if(f_s>g_s)
                    add_s=f_s;
                else
                    add_s=g_s;
                double h[add_s];
                addi(f,f_s,g,g_s,h);
                printf("\n\nPolynome B :\n");
                aff(g,g_s);
                printf("\n\nA + B :\n");
                aff(h,add_s);
                printf("\n\n");

                break;
            }

            case 5:
            {
                int i_s=0,j_s=0,mul_test=2,mul_test2=2;
                printf("\n\nProduit de 2 polynomes :\n\nDegre polynome A : ");
                scanf("%d",&i_s);
                i_s++;
                double i[i_s];
                while(mul_test != 0 && mul_test != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&mul_test);
                }
                if(mul_test==1)
                    remp(i,i_s,-10,10);
                else{
                    for(int y=0;y<i_s;y++){
                        printf("x^%d : ",i_s-y-1);
                        scanf("%lf",&i[y]);
                    }
                }
                printf("\nPolynome A :\n");
                aff(i,i_s);
                printf("\n\nDegre polynome B : ");
                scanf("%d",&j_s);
                j_s++;
                double j[j_s];
                while(mul_test2 != 0 && mul_test2 != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&mul_test2);
                }
                if(mul_test2==1)
                    remp(j,j_s,-10,10);
                else{
                    for(int y=0;y<j_s;y++){
                        printf("x^%d : ",j_s-y-1);
                        scanf("%lf",&j[y]);
                    }
                }

                int mul_s=i_s+j_s-1;
                double ks[mul_s];
                mul(i,i_s,j,j_s,ks);
                printf("\n\nPolynome B :\n");
                aff(j,j_s);
                printf("\n\nA x B :\n");
                aff(ks,mul_s);
                printf("\n\n");

                break;
            }

            case 6:
            {
                int m_s=0,n_s=0,div_test=2,div_test2=2;
                printf("\n\nDivision de 2 polynomes :\n\nDegre polynome A : ");
                scanf("%d",&m_s);
                m_s++;
                double m[m_s],reste[m_s];
                while(div_test != 0 && div_test != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&div_test);
                }
                if(div_test==1)
                    remp(m,m_s,-10,10);
                else{
                    for(int y=0;y<m_s;y++){
                        printf("x^%d : ",m_s-y-1);
                        scanf("%lf",&m[y]);
                    }
                }
                printf("\nPolynome A :\n");
                aff(m,m_s);
                printf("\n\nDegre polynome B : ");
                scanf("%d",&n_s);
                n_s++;
                double n[n_s];
                while(div_test2 != 0 && div_test2 != 1){
                    printf("\nPolynome aleatoire ? (1=oui et 0=non) : ");
                    scanf("%d",&div_test2);
                }
                if(div_test2==1)
                    remp(n,n_s,-10,10);
                else{
                    for(int y=0;y<n_s;y++){
                        printf("x^%d : ",n_s-y-1);
                        scanf("%lf",&n[y]);
                    }
                }
                printf("\n\nPolynome B :\n");
                aff(n,n_s);
                printf("\n");
                int cc2=deg(m,m_s)-deg(n,n_s)+1,test_res=0;
                double quotient[cc2];
                if(test_res=division(m,m_s,n,n_s,quotient,reste)){
                    switch(test_res){
                        case 1:
                            printf("\nErreur : le degre du diviseur est superieur a celui du dividende\n\n");
                            break;
                        case 2:
                            printf("\nErreur : division par 0\n\n");
                            break;
                    }
                }
                else{
                    printf("\nQuotient :\n");
                    aff(quotient,cc2);
                    printf("\n\nReste :\n");
                    aff(reste,m_s);
                    printf("\n\n");
                }

                break;
            }
        }
    }

	return 0;
}
