#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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
    int b=0;
    for(int x=0;x<a;x++){
        if(tab[x]!=0){
            b=a-x-1;
            if(tab[x]>0 && x>0) printf("+");
            printf("%g",tab[x]);
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
    for(int x=0;x<b;x++){
        // printf("%g - %d\n",tab[x],b-x);
        res[x]=tab[x]*(b-x);
    }
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
    double* res=create_tab(a-b+1);
    double* res_bis=create_tab(a-b+1);
    double* tab=create_tab(a);
    for(int z=0;z<a;z++) tab[z]=ta[z];
    double* tab_bis=create_tab(a);
    double* tab2=create_tab(b);
    for(int zz=0;zz<b;zz++) tab2[zz]=ta2[zz];
    int aa=0;
    while(deg(tab,a)>=deg(tab2,b)){ //|| tab[b-1]!=0){
        if(tab[aa]!=0){
            for(int p=0;p<a-b+1;p++) res_bis[p]=0;
            res[aa]=tab[a-1-deg(tab,a)]/tab2[0];
            printf("    %g\n\n",res[aa]);
            res_bis[aa]=res[aa];
            tab_bis=mul(tab2,b,res_bis,a-b+1);

            aff(tab_bis,a);
            printf("\n\n");

            aff(res_bis,a-b+1);
            printf("\n\n");

            for(int y=0;y<a;y++) tab_bis[y]=-tab_bis[y];

            //aff(tab_bis,a);
            //printf("\n\n");

            tab=addi(tab,a,tab_bis,a);

            aff(tab,a);
            printf("\n\n");

            aa++;
        }
        else aa++;
    }
    aff(res,a-b+1);
    printf("\n\n");
    aff(tab,a);

    delete_tab(res,a-b+1);
    delete_tab(res_bis,a-b+1);
    delete_tab(tab,a);
    delete_tab(tab_bis,a);
    delete_tab(tab2,b);
}

int main(){
srand(time(NULL));
// double a[5]={-8,2,5,4,-1};

int y=4,z=9;
double a[4]={1,-2,-4,5},b[9]={3,0,0,0,0,-1,2,-2,1};

/*int y=3,z=2;
double a[3]={3,-2,1},b[2]={1,0};*/

// for(int x=0;x<y;x++) a[x]=rand()%10-5;
// for(int x1=0;x1<z;x1++) b[x1]=rand()%10-5;

/*aff(a,y);
printf("\n\n");
aff(b,z);
printf("\n\nMul :\n");*/
// printf("\n\n%g\n",eval(a,5,1));

double* res=create_tab(y+z-1);
res=mul(a,y,b,z);
//aff(res,y+z-1);
delete_tab(res,y+z-1);

//printf("\n\nAdd :\n");

double* res2=create_tab(z);
res2=addi(a,y,b,z);
//aff(res2,z);
delete_tab(res2,z);

// printf("\n\n");
// aff(a,y);

//printf("\n\nDerivee :\n");

double* aaa=create_tab(z-1);
aaa=deriv(b,z);
//aff(aaa,z-1);
delete_tab(aaa,z-1);

double* abc=create_tab(6);
double* abc2=create_tab(2);
    abc[0]=6;
    abc[1]=-30;
    abc[2]=0;
    abc[3]=-1;
    abc[4]=1;
    abc[5]=8;
    //abc[6]=18;

    abc2[0]=1;
    abc2[1]=3;
    /*abc2[2]=4;
    abc2[3]=-1;
    abc2[7]=1;*/

    divi(abc,6,abc2,2);
    //printf("%d\n",deg(abc2,3));
delete_tab(abc,6);
delete_tab(abc2,2);

	return 0;
}
