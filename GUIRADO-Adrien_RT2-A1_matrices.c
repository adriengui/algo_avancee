#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double** create_tab(int m,int n){
    double** T;
    int i;
    T=(double**) malloc(m*sizeof(double*));
    for(i=0;i<m;i++)
        T[i]=(double*) malloc(n*sizeof(double));
    for(int x=0;x<m;x++)
        for(int y=0;y<n;y++)
            T[x][y]=0;
    return T;
}

void delete_tab(double** T, int m){
    for(int i=0;i<m;i++)
        free(T[i]);
    free(T);
}

void aff(double** mat, int m, int n){
    for(int x=0;x<m;x++){
        for(int y=0;y<n;y++)
            printf("%5g ",mat[x][y]);
        printf("\n");
    }
}

/* Erreurs :

    0 : OK
    1 : Erreur de dimensions (les matrices n'ont pas les mêmes dimensions)

*/
int addi(double** mat1, int m1, int n1,double** mat2, int m2, int n2, double** res){
    if(m1==m2 && n1==n2){
        for(int x=0;x<m1;x++)
            for(int y=0;y<n1;y++)
                res[x][y]=mat1[x][y]+mat2[x][y];
        return 0;
    }
    else
        return 1;
}

/* Erreurs :

    0 : OK
    1 : Erreur de dimensions (la matrice n'est pas carrée)

*/
int trace(double** mat, int m, int n, double *res){
    if(m==n){
        double T=0;
        for(int x=0;x<m;x++)
            T+=mat[x][x];
        *res=T;
        return 0;
    }
    else
        return 1;
}

/* Erreurs :

    0 : OK
    1 : Erreur de dimensions (l'indice voulu est en dehors des dimensions de la matrice)

*/
int sous_mat(double** mat, int m, int n, int ligne,int colonne, double** T){
    if(ligne<m && colonne<n){
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
        return 0;
    }
    else
        return 1;
}

/* Erreurs :

    0 : OK
    1 : Erreur de dimensions (la matrice n'est pas carrée)

*/
int det(double** mat, int m, int n, double* res){
    if(m==n){
        if(m==2)
            *res=mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
        else{
            double u=0;
            double** aa=create_tab(m-1,n-1);
            double sous_det=0;
            for(int t=0;t<m;t++){
                if(mat[t][0] != 0){
                    sous_mat(mat,m,n,t,0,aa);
                    det(aa,m-1,n-1,&sous_det);
                    u+=pow(-1,t)*mat[t][0]*sous_det;
                }
            }
            delete_tab(aa,m-1);
            *res=u;
        }
        return 0;
    }
    else
        return 1;
}

/* Erreurs :

    0 : OK
    1 : Erreur de dimensions (le nombre de colonnes de la matrice A est différent du nombre de lignes de la matrice B)

*/
int mul(double** mat1, int m1, int n1,double** mat2, int m2, int n2, double** res){
    if(n1==m2){
        int y=0,c=0,z=0;
        for(int x=0;x<m1;x++){
            for(y=0;y<n2;y++){
                c=0;
                for(z=0;z<m2;z++)
                    c+=mat1[x][z]*mat2[z][y];
                res[x][y]=c;
            }
        }
        return 0;
    }
    else
        return 1;
}

void remp(double** a, int m, int n, int deb, int fin){
    for(int x=0;x<m;x++)
        for(int y=0;y<n;y++)
            a[x][y]=rand()%(fin+1-deb)+deb;
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\n");

    int aa1=11,aa2=9;
    printf("Affichage matrice (%dx%d) :\n",aa1,aa2);
    double** a=create_tab(aa1,aa2);
    remp(a,aa1,aa2,-10,9);
    aff(a,aa1,aa2);
    delete_tab(a,aa1);

    int a11=7,a12=8,a21=7,a22=8,b03=0;
    printf("\n\nAddition matrices :\n\nMatrice A (%dx%d) :\n",a11,a12);
    double** b=create_tab(a11,a12);
    double** c=create_tab(a21,a22);
    double** d=create_tab(a11,a12);
    remp(b,a11,a12,-10,9);
    remp(c,a21,a22,-10,9);
    aff(b,a11,a12);
    printf("\nMatrice B (%dx%d) :\n",a21,a22);
    aff(c,a21,a22);
    printf("\nA + B (%dx%d) :\n",a11,a12);
    if(b03=addi(b,a11,a12,c,a21,a22,d)){
        switch(b03){
            case 1:
                printf("Erreur de dimension\n\n\n");
                break;
        }
    }
    else
        aff(d,a11,a12);
    delete_tab(b,a11);
    delete_tab(c,a21);
    delete_tab(d,a11);

    int m11=9,m12=7,m21=7,m22=8,b02=0;
    printf("\n\nMultiplication matrices :\n\nMatrice A (%dx%d) :\n",m11,m12);
    double** e=create_tab(m11,m12);
    double** f=create_tab(m21,m22);
    double** g=create_tab(m11,m22);
    remp(e,m11,m12,-10,9);
    remp(f,m21,m22,-10,9);
    aff(e,m11,m12);
    printf("\nMatrice B (%dx%d) :\n",m21,m22);
    aff(f,m21,m22);
    printf("\nA x B (%dx%d) :\n",m11,m22);
    if(b02=mul(e,m11,m12,f,m21,m22,g)){
        switch(b02){
            case 1:
                printf("Erreur de dimension\n\n");
                break;
        }
    }
    else
        aff(g,m11,m22);
    delete_tab(e,m11);
    delete_tab(f,m21);
    delete_tab(g,m11);

    int t1=12,t2=12,b01=0;
    printf("\n\nTrace d'une matrice :\n\nMatrice (%dx%d) :\n",t1,t2);
    double** h=create_tab(t1,t2);
    double tra=0;
    remp(h,t1,t2,-10,9);
    aff(h,t1,t2);
    if(b01=trace(h,t1,t2,&tra)){
        switch(b01){
            case 1:
                printf("Erreur de dimension\n\n\n");
                break;
        }
    }
    else
        printf("\nTrace : %g\n\n\n",tra);
    delete_tab(h,t1);

    int d1=10,d2=10,b00=0;
    printf("Determinant d'une matrice :\n\nMatrice (%dx%d) :\n",d1,d2);
    double** i=create_tab(d1,d2);
    double deter=0;
    remp(i,d1,d2,-1,2);
    aff(i,d1,d2);
    if(b00=det(i,d1,d2,&deter)){
        switch(b00){
            case 1:
                printf("Erreur de dimension\n");
                break;
        }
    }
    else
        printf("\nDeterminant : %g\n\n",deter);
    delete_tab(i,d1);

	return 0;
}
