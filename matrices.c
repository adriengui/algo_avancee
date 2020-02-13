#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double** create_tab(int m,int n){
    double** T;
    int i;
    T=(double**) malloc (m*sizeof(double*));
    for(i=0;i<m;i++) T[i]=(double*) malloc (n*sizeof(double));
    for(int x=0;x<m;x++) for(int y=0;y<n;y++) T[x][y]=0;
    return T;
}

void delete_tab(double** T, int m){
    for(int i=0;i<m;i++) free(T[i]);
    free(T);
}

void aff(double** mat, int m, int n){
    for(int x=0;x<m;x++){
        for(int y=0;y<n;y++) printf("%5g ",mat[x][y]);
        printf("\n");
    }
}

double** addi(double** mat1, int m1, int n1,double** mat2, int m2, int n2){
        double** a=create_tab(m1,n1);
        for(int x=0;x<m1;x++) for(int y=0;y<n1;y++) a[x][y]=mat1[x][y]+mat2[x][y];
        return(a);
        delete_tab(a,m1);
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

    printf("GUIRADO Adrien - RT2 A1\n\n");

    int aa1=11,aa2=9;
    printf("Affichage matrice (%dx%d) :\n",aa1,aa2);
    double** a=create_tab(aa1,aa2);
    for(int x=0;x<aa1;x++) for(int y=0;y<aa2;y++) a[x][y]=rand()%20-10;
    aff(a,aa1,aa2);
    printf("\n\n");
    delete_tab(a,aa1);

    int a1=7,a2=8;
    printf("Addition matrices :\n\nMatrice A (%dx%d) :\n",a1,a2);
    double** b=create_tab(a1,a2);
    double** c=create_tab(a1,a2);
    double** d=create_tab(a1,a2);
    for(int x=0;x<a1;x++) for(int y=0;y<a2;y++) b[x][y]=rand()%20-10;
    for(int x=0;x<a1;x++) for(int y=0;y<a2;y++) c[x][y]=rand()%20-10;
    d=addi(b,a1,a2,c,a1,a2);
    aff(b,a1,a2);
    printf("\nMatrice B (%dx%d) :\n",a1,a2);
    aff(c,a1,a2);
    printf("\nA + B (%dx%d) :\n",a1,a2);
    aff(d,a1,a2);
    printf("\n\n");
    delete_tab(b,a1);
    delete_tab(c,a1);
    delete_tab(d,a1);

    int m11=9,m12=7,m21=7,m22=8;
    printf("Multiplication matrices :\n\nMatrice A (%dx%d) :\n",m11,m12);
    double** e=create_tab(m11,m12);
    double** f=create_tab(m21,m22);
    double** g=create_tab(m11,m22);
    for(int x=0;x<m11;x++) for(int y=0;y<m12;y++) e[x][y]=rand()%20-10;
    for(int x=0;x<m21;x++) for(int y=0;y<m22;y++) f[x][y]=rand()%20-10;
    g=mul(e,m11,m12,f,m21,m22);
    aff(e,m11,m12);
    printf("\nMatrice B (%dx%d) :\n",m21,m22);
    aff(f,m21,m22);
    printf("\nA x B (%dx%d) :\n",m11,m22);
    aff(g,m11,m22);
    printf("\n\n");
    delete_tab(e,m11);
    delete_tab(f,m21);
    delete_tab(g,m11);

    int t1=9;
    printf("Trace d'une matrice :\n\nMatrice (%dx%d) :\n",t1,t1);
    double** h=create_tab(t1,t1);
    for(int x=0;x<t1;x++) for(int y=0;y<t1;y++) h[x][y]=rand()%20-10;
    aff(h,t1,t1);
    printf("\nTrace : %g\n\n\n",trace(h,t1));
    delete_tab(h,t1);

    int d1=10;
    printf("Determinant d'une matrice :\n\nMatrice (%dx%d) :\n",d1,d1);
    double** i=create_tab(d1,d1);
    for(int x=0;x<d1;x++) for(int y=0;y<d1;y++) i[x][y]=rand()%6-3;
    aff(i,d1,d1);
    printf("\nDeterminant : %g\n\n",det(i,d1));
    delete_tab(i,d1);

	return 0;
}
