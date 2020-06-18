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

void eval(double *tab, int a, double x, double *res){
    for(int y=0;y<a;y++)
        *res+=tab[y]*pow(x,a-y-1);
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
        if(deg(ta,a)==0 && ta[a-1]==0){
            for(int x=0;x<deg(ta,a)-deg(ta2,b)+1;x++) quotient[x]=0;
            for(int x=0;x<a;x++) reste[x]=0;
        }
        else{
            int l=deg(ta,a)-deg(ta2,b)+1,la1=deg(ta,a)+1,la2=deg(ta2,b)+1;
            double tab[la1],tab2[la2];
            for(int x=0;x<la1;x++) tab[x]=ta[x+pos(ta,a)];
            for(int x=0;x<la2;x++) tab2[x]=ta2[x+pos(ta2,b)];
            double tabbis[la1],quobis[l];
            for(int x=0;x<l;x++){
                for(int u=0;u<l;u++) quobis[u]=0;
                quotient[x]=tab[x]/tab2[0];
                quobis[x]=quotient[x];
                mul(tab2,la2,quobis,l,tabbis);
                for(int y=0;y<la1;y++) tabbis[y]=-tabbis[y];
                for(int z=0;z<la1;z++) tab[z]+=tabbis[z];
            }
            for(int x=0;x<a;x++) reste[x]=0;
            for(int x=0;x<la1;x++) reste[a-la1+x]=tab[x];
        }

        return 0;
    }
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

void menu(){
        printf("\nOperations :\n\n\
1 : Affichage polynome\n\
2 : Evaluation polynome\n\
3 : Derivee polynome\n\
4 : Somme polynomes\n\
5 : Produit polynomes\n\
6 : Division polynomes\n");
}


int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\nOperations sur les polynomes\n\n");

    int k=1;

    while(k != 0){
        menu();
        printf("\nOperation souhaitee (0 pour quitter) : ");
        scanf("%d",&k);
        switch(k){
            case 1:
            {
                int a_s=-1,aff_test=2;
                printf("Affichage polynome :\n");
                dim(&a_s,'A');
                a_s++;
                double a[a_s];
                saisie(&aff_test,a,a_s);
                printf("\nA = ");
                aff(a,a_s);
                printf("\n\n");

                break;
            }

            case 2:
            {
                int b_s=-1,eval_test=2;
                printf("Evaluation polynome :\n");
                dim(&b_s,'A');
                b_s++;
                double b[b_s],res_eval=0,c1=0;
                saisie(&eval_test,b,b_s);
                printf("\nA = ");
                aff(b,b_s);
                printf("\n\nx0 : ");
                scanf("%lf",&c1);
                eval(b,b_s,c1,&res_eval);
                printf("\n\nA(%g) = %g\n\n\n",c1,res_eval);

                break;
            }

            case 3:
            {
                int c_s=-1,deriv_test=2;
                printf("Derivee polynome :\n");
                dim(&c_s,'A');
                if(c_s==0)
                    printf("Derivee nulle\n");
                else{
                    c_s++;
                    double c[c_s],d[c_s-1];
                    saisie(&deriv_test,c,c_s);
                    deriv(c,c_s,d);
                    printf("\nA = ");
                    aff(c,c_s);
                    printf("\n\nA' = ");
                    aff(d,c_s-1);
                    printf("\n\n");
                }
                break;
            }

            case 4:
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
                printf("\n\n");

                break;
            }

            case 5:
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
                printf("\n\n");

                break;
            }

            case 6:
            {
                int m_s=-1,n_s=-1,div_test=2,div_test2=2;
                printf("\n\nDivision de 2 polynomes :\n");
                dim(&m_s,'A');
                m_s++;
                double m[m_s],reste[m_s];
                saisie(&div_test,m,m_s);
                printf("\nA = ");
                aff(m,m_s);
                printf("\n");
                dim(&n_s,'B');
                n_s++;
                double n[n_s];
                saisie(&div_test2,n,n_s);
                printf("\n\nB = ");
                aff(n,n_s);
                printf("\n");
                int cc2=deg(m,m_s)-deg(n,n_s)+1,test_res=0;
                double quotient[cc2];
                if(test_res=division(m,m_s,n,n_s,quotient,reste)){
                    switch(test_res){
                        case 1:
                            printf("\nErreur : Deb B > Deg A\n\n");
                            break;
                        case 2:
                            printf("\nErreur : division par 0\n\n");
                            break;
                    }
                }
                else{
                    printf("\nQ = ");
                    aff(quotient,cc2);
                    printf("\n\nR = ");
                    aff(reste,m_s);
                    printf("\n\n");
                }

                break;
            }
        }
    }

	return 0;
}
