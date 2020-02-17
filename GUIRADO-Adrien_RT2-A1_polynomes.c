#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double* create_tab(int m){
    double* T;
    int i;
    T=(double*) malloc (m*sizeof(double));
    for(int x=0;x<m;x++) T[x]=0;
    return T;
}

void delete_tab(double* T, int m){
    free(T);
}

void aff(double* tab, int a){
    int z=0;
    for(int x=0;x<a;x++){
        z++;
        if(tab[x]!=0) break;
    }
    int zz=a-z+1;
    double tab2[zz];
    for(int x=0;x<zz;x++) tab2[x]=tab[a-zz+x];
    int b=0;
    for(int x=0;x<zz;x++){
        if(tab2[x]!=0){
            b=zz-x-1;
            if(tab2[x]>0 && x>0) printf("+");
            printf("%g",tab2[x]);
            if(b>1) printf("x%d",b);
            else if(b==1) printf("x");
        }
    }
}

double eval(double* tab, int a, double x){
    double res=0;
    for(int y=0;y<a;y++) res+=tab[y]*pow(x,a-y-1);
    return res;
}

double* deriv(double* tab, int a){
    int b=a-1;
    double* res=create_tab(b);
    for(int x=0;x<b;x++) res[x]=tab[x]*(b-x);
    return res;
    delete_tab(res,b);
}

double* addi(double* tab, int a,double* tab2, int b){
    int z=0;
    if(a>b) z=a;
    else z=b;
    double* res=create_tab(z);
    if(a>b){
        for(int d=0;d<a;d++) res[d]=tab[d];
        for(int x=0;x<b;x++) res[a-b+x]+=tab2[x];
    }
    else{
        for(int d=0;d<b;d++) res[d]=tab2[d];
        for(int x=0;x<a;x++) res[b-a+x]+=tab[x];
    }
    return res;
    delete_tab(res,z);
}

double* mul(double* tab, int a,double* tab2, int b){
    double* res=create_tab(a+b-1);
    for(int x=0;x<a;x++) for(int y=0;y<b;y++) res[x+y]+=tab[x]*tab2[y];
    return res;
    delete_tab(res,a+b-1);
}

int deg(double* t, int a){
    int z=0;
    for(int x=0;x<a;x++){
        z++;
        if(t[x]!=0) break;
    }
    return a-z;
}

void divi(double* ta, int a,double* ta2, int b){
    if(deg(ta2,b)==0){
        for(int x=0;x<a;x++) ta[x]=ta[x]/ta2[b-1];
        printf("Quotient : ");
        aff(ta,a);
    }
    else{
        double* res=create_tab(a-b+1);
        double* res_bis=create_tab(a-b+1);
        double* tab=create_tab(a);
        for(int z=0;z<a;z++) tab[z]=ta[z];
        double* tab_bis=create_tab(a);
        double* tab2=create_tab(b);
        for(int zz=0;zz<b;zz++) tab2[zz]=ta2[zz];
        int aa=0;
        while(deg(tab,a)>=deg(tab2,b)){
            if(tab[aa]!=0){
                for(int p=0;p<a-b+1;p++) res_bis[p]=0;
                res[aa]=tab[a-1-deg(tab,a)]/tab2[0];
                res_bis[aa]=res[aa];
                tab_bis=mul(tab2,b,res_bis,a-b+1);
                for(int y=0;y<a;y++) tab_bis[y]=-tab_bis[y];
                tab=addi(tab,a,tab_bis,a);
                aa++;
            }
            else aa++;
        }
        printf("Quotient : ");
        aff(res,a-b+1);
        printf("\n\nReste : ");
        aff(tab,a);
        delete_tab(res,a-b+1);
        delete_tab(res_bis,a-b+1);
        delete_tab(tab,a);
        delete_tab(tab_bis,a);
        delete_tab(tab2,b);
    }
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\n");

    printf("Affichage polynome :\n\n");
    double* a=create_tab(8);
    for(int x=0;x<8;x++) a[x]=rand()%20-10;
    aff(a,8);
    delete_tab(a,8);

    printf("\n\n\nEvaluation d'un polynome en un x donne : \nPolynome :\n\n");
    double* b=create_tab(5);
    for(int x=0;x<5;x++) b[x]=rand()%20-10;
    aff(b,5);
    int c=rand()%20-10;
    printf("\n\nEval en x = %d : %g\n\n\n",c,eval(b,5,c));
    delete_tab(b,5);

    printf("Derivee d'un polynome :\nPolynome :\n\n");
    double* d=create_tab(7);
    for(int x=0;x<7;x++) d[x]=rand()%20-10;
    double* e=create_tab(6);
    e=deriv(d,7);
    aff(d,7);
    printf("\n\nDerivee :\n\n");
    aff(e,6);
    delete_tab(d,7);
    delete_tab(e,6);

    printf("\n\n\nAjout de 2 polynomes :\nPolynome A :\n\n");
    double* f=create_tab(7);
    double* g=create_tab(6);
    double* h=create_tab(7);
    for(int x=0;x<7;x++) f[x]=rand()%20-10;
    for(int x=0;x<6;x++) g[x]=rand()%20-10;
    h=addi(f,7,g,6);
    aff(f,7);
    printf("\n\nPolynome B :\n\n");
    aff(g,6);
    printf("\n\nA + B :\n\n");
    aff(h,7);
    delete_tab(f,7);
    delete_tab(g,6);
    delete_tab(h,7);

    printf("\n\n\nMultiplication de 2 polynomes :\nPolynome A :\n\n");
    int aa=6,bb=3;
    double* i=create_tab(aa);
    double* j=create_tab(bb);
    double* k=create_tab(aa+bb-1);
    for(int x=0;x<aa;x++) i[x]=rand()%20-10;
    for(int x=0;x<bb;x++) j[x]=rand()%20-10;
    k=mul(i,aa,j,bb);
    aff(i,aa);
    printf("\n\nPolynome B :\n\n");
    aff(j,bb);
    printf("\n\nA x B :\n\n");
    aff(k,aa+bb-1);
    delete_tab(i,aa);
    delete_tab(j,bb);
    delete_tab(k,aa+bb-1);

    printf("\n\n\nDivision de 2 polynomes :\nPolynome A :\n\n");
    int aa2=7,bb2=4;
    double* l=create_tab(aa2);
    double* m=create_tab(bb2);
    for(int x=0;x<aa2;x++) l[x]=rand()%20-10;
    for(int x=0;x<bb2;x++) m[x]=rand()%20-10;
    aff(l,aa2);
    printf("\n\nPolynome B :\n\n");
    aff(m,bb2);
    printf("\n\n");
    divi(l,aa2,m,bb2);
    printf("\n\n");
    delete_tab(l,aa2);
    delete_tab(m,bb2);

	return 0;
}
