#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double** create_tab(int m,int n){
    double** T;
    T=(double**) malloc(m*sizeof(double*));
    for(int i=0;i<m;i++)
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

void saisie(int *test, double **a, int m, int n){
    while(*test != 0 && *test != 1){
        printf("\nMatrice aleatoire ? (1=oui et 0=non) : ");
        scanf("%d",&*test);
    }
    if(*test==1)
        remp(a,m,n,-10,9);
    else{
        for(int y=0;y<m;y++){
            for(int z=0;z<n;z++){
               printf("m%d n%d : ",y+1,z+1);
                scanf("%lf",&a[y][z]);
            }
        }
    }
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\n");

    printf("Operations sur les matrices\n\n1 : Affichage matrice\n2 : Somme matrices\n3 : Produit matrices\n4 : Trace matrice\n5 : Determinant matrice\n\n");

    int k=1;

    while(k != 0){
        printf("Operation souhaitee (0 pour quitter) : ");
        scanf("%d",&k);
        switch(k){
            case 1:
            {
                int aa1=0,aa2=0,aff_test=2;
                printf("Affichage matrice :\nNb lignes : ");
                scanf("%d",&aa1);
                printf("\nNb colonnes : ");
                scanf("%d",&aa2);
                double** a=create_tab(aa1,aa2);
                saisie(&aff_test,a,aa1,aa2);
                printf("\n");
                aff(a,aa1,aa2);
                delete_tab(a,aa1);
                printf("\n\n");
                break;
            }
            case 2:
            {
                int a11=0,add_test=2,add_test2=2;
                printf("\n\nAddition matrices :\n\nDimension : ");
                scanf("%d",&a11);
                double** b=create_tab(a11,a11);
                double** c=create_tab(a11,a11);
                double** d=create_tab(a11,a11);
                printf("\nSaisie matrice A :\n");
                saisie(&add_test,b,a11,a11);
                aff(b,a11,a11);
                printf("\n\nSaisie matrice B :\n");
                saisie(&add_test2,c,a11,a11);
                aff(c,a11,a11);
                printf("\nA + B (%dx%d) :\n",a11,a11);
                addi(b,a11,a11,c,a11,a11,d);
                aff(d,a11,a11);
                delete_tab(b,a11);
                delete_tab(c,a11);
                delete_tab(d,a11);
                break;
            }
            case 3:
            {
                int m11=0,m12=0,m21=0,m22=0,b02=0,mul_test=2,mul_test2=2;
                printf("\n\nMultiplication matrices :\n\nMatrice A :\nNb lignes :");
                scanf("%d",&m11);
                printf("\nNb colonnes : ");
                scanf("%d",&m12);
                printf("\nMatrice B :\nNb lignes : ");
                scanf("%d",&m21);
                printf("\nNb colonnes : ");
                scanf("%d",&m22);
                if(m12==m21){
                    double** e=create_tab(m11,m12);
                    double** f=create_tab(m21,m22);
                    double** g=create_tab(m11,m22);
                    printf("\nSaisie matrice A :\n");
                    saisie(&mul_test,e,m11,m12);
                    aff(e,m11,m12);
                    printf("\nSaisie matrice B :\n");
                    saisie(&mul_test2,f,m21,m22);
                    aff(f,m21,m22);
                    printf("\nA x B (%dx%d) :\n",m11,m22);
                    mul(e,m11,m12,f,m21,m22,g);
                    aff(g,m11,m22);
                    delete_tab(e,m11);
                    delete_tab(f,m21);
                    delete_tab(g,m11);
                }
                else
                    printf("\nErreur de dimensions\n");

                break;
            }
            case 4:
            {
                int t1=0,tra_test=2;
                printf("\n\nTrace d'une matrice :\n\nDimension : ");
                scanf("%d",&t1);
                double** h=create_tab(t1,t1);
                double tra=0;
                printf("\nSaisie matrice :\n");
                saisie(&tra_test,h,t1,t1);
                aff(h,t1,t1);
                trace(h,t1,t1,&tra);
                printf("\nTrace : %g\n\n",tra);
                delete_tab(h,t1);

                break;
            }
            case 5:
            {
                int d1=00,det_test=2;
                printf("Determinant d'une matrice :\n\nDimension :");
                scanf("%d",&d1);
                double** i=create_tab(d1,d1);
                double deter=0;
                saisie(&det_test,i,d1,d1);
                aff(i,d1,d1);
                det(i,d1,d1,&deter);
                printf("\nDeterminant : %lf\n\n",deter);
                delete_tab(i,d1);
                printf("\n");

                break;
            }
        }
    }

	return 0;
}
