#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



double** create_tab(int m,int n){
    double** T;
    int i;
    T=(double**) malloc (m*sizeof(double*));
    for(i=0;i<m;i++) T[i]=(double*) malloc (n*sizeof(double));
    return T;
}

void delete_tab(double** T, int m){
    for(int i=0;i<m;i++) free(T[i]);
    free(T);
}

void aff(double** mat, int m, int n){
    for(int x=0;x<m;x++){
        for(int y=0;y<n;y++) printf("%g ",mat[x][y]);
        printf("\n");
    }
}

//double** addi(double** mat, int m, int n, int ligne,int colonne){
double** addi(double** mat1, int m1, int n1,double** mat2, int m2, int n2){
    //if(m1==m2 && n1==n2){
        double** a=create_tab(m1,n1);
        for(int x=0;x<m1;x++) for(int y=0;y<n1;y++) a[x][y]=mat1[x][y]+mat2[x][y];
        return(a);
        delete_tab(a,m1);
    //}
    //else return(0);
}

double trace(double** mat1, int m1){
    double T=0;
    for(int x=0;x<m1;x++) T+=mat1[x][x];
    return T;
}

double** sous_mat(double** mat, int m, int n, int ligne,int colonne){
    double** T=create_tab(m-1,n-1);
    int a=0,b=0;
    for(int x=0;x<m;x++){
            if(x != ligne){
                b=0;
                    for(int y=0;y<m;y++){
                            if(y != colonne){
                                    T[a][b]=mat[x][y];
                                    b++;
                            }
                    }
                a++;
            }
    }
    return(T);
    delete_tab(T,m-1);
}

double det(double** mat, int m){
    if(m==2) return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
    else{
        double u=0;
        double** aa=create_tab(m-1,m-1);
        for(int t=0;t<m;t++){
            if(mat[t][0] != 0){

                aa=sous_mat(mat,m,m,t,0);
                u+=pow(-1,t)*mat[t][0]*det(aa,m-1);
            }
        }
        delete_tab(aa,m-1);
        return(u);
    }
}

double** mul(double** mat1, int m1, int n1,double** mat2, int m2, int n2){
    double** T=create_tab(m1,n2);
    for(int x=0;x<m1;x++){
        for(int y=0;y<n2;y++){
            int c=0;
            for(int z=0;z<m2;z++) c+=mat1[x][z]*mat2[z][y];
            T[x][y]=c;
        }
    }
    return T;
    delete_tab(T,m1);
}



int main(){

    srand(time(NULL));
    int f=12;
    double** a=create_tab(11,11);
    double** b=create_tab(11,11);
    double** res=create_tab(11,11);

    /*a[0][0]=4;
    a[0][1]=4;
    a[0][2]=3;
    a[1][0]=2;
    a[1][1]=0;
    a[1][2]=0;

    b[0][0]=4;
    b[0][1]=2;
    b[0][2]=2;
    b[0][3]=1;
    b[1][0]=4;
    b[1][1]=2;
    b[1][2]=4;
    b[1][3]=4;
    b[2][0]=2;
    b[2][1]=1;
    b[2][2]=4;
    b[2][3]=3;*/

    for(int x=0;x<11;x++) for(int y=0;y<11;y++) a[x][y]=((rand()%5));//+((rand()%99)+1)*0.01;
//for(int x=0;x<f;x++) for(int y=0;y<f;y++) b[x][y]=((rand()%20)-10)+((rand()%99)+1)*0.01;
    for(int x=0;x<11;x++) for(int y=0;y<11;y++) b[x][y]=((rand()%5));


    aff(a,11,11);
printf("%g\n",det(a,11));


    printf("\n\n");
    aff(b,11,11);
    res=addi(a,11,11,b,11,11);
    printf("\n\n");
    aff(res,11,11);
    //res=sous_mat(a,f,f,0,1);
    //aff(res,f-1,f-1);



    //printf("%g\n",det(a,f));


// printf("%g\n",pow(-1,pow(5,2)-1));

//printf("\n%lf\n\n",det(a,f));
/*aff(b,f,f);

printf("\n%g\n\n",trace(b,f));*/
//double** somme=create_tab(f,f);
//somme=addi(a,f,f,b,f,f);
/*aff(somme,f,f);
printf("\n%g\n\n",trace(somme,f));*/
    delete_tab(a,11);
    delete_tab(b,11);
//delete_tab(somme,f);
    delete_tab(res,11);

	return 0;
}
