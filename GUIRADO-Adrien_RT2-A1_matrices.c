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

void addi(double** mat1, int m1, int n1,double** mat2, int m2, int n2, double** res){
        for(int x=0;x<m1;x++)
            for(int y=0;y<n1;y++)
                res[x][y]=mat1[x][y]+mat2[x][y];
}

void trace(double** mat, int m, int n, double *res){
        double T=0;
        for(int x=0;x<m;x++)
            T+=mat[x][x];
        *res=T;
}

void sous_mat(double** mat, int m, int n, int ligne,int colonne, double** T){
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
}

void det(double** mat, int m, int n, double* res){
        if(m==1)
            *res=mat[0][0];
        else if(m==2)
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
}

void mul(double** mat1, int m1, int n1,double** mat2, int m2, int n2, double** res){
        int y=0,c=0,z=0;
        for(int x=0;x<m1;x++){
            for(y=0;y<n2;y++){
                c=0;
                for(z=0;z<m2;z++)
                    c+=mat1[x][z]*mat2[z][y];
                res[x][y]=c;
            }
        }
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

void dim(int* t, int d){
    char a[50];
    switch(d){
        case 0:
            sprintf(a,"\nNb lignes : ");
            break;
        case 1:
            sprintf(a,"\nNb colonnes : ");
            break;
        case 2:
            sprintf(a,"\nDimension : ");
            break;
    }
    while(*t<1){
        printf("%s",a);
        scanf("%d",&*t);
    }
}

void menu(){
    printf("\n1 : Affichage matrice\n\
2 : Somme matrices\n\
3 : Produit matrices\n\
4 : Trace matrice\n\
5 : Determinant matrice\n\n");
}

int main(){

    srand(time(NULL));

    printf("GUIRADO Adrien - RT2 A1\n\nOperations sur les matrices\n");

    int k=1;

    while(k != 0){
        menu();
        printf("Operation souhaitee (0 pour quitter) : ");
        scanf("%d",&k);
        switch(k){
            case 1:
            {
                int aa1=0,aa2=0,aff_test=2;
                printf("Affichage matrice :\n");
                dim(&aa1,0);
                dim(&aa2,1);
                double** a=create_tab(aa1,aa2);
                saisie(&aff_test,a,aa1,aa2);
                printf("\n");
                aff(a,aa1,aa2);
                printf("\n\n");
                delete_tab(a,aa1);

                break;
            }
            case 2:
            {
                int a11=0,a12=0,add_test=2,add_test2=2;
                printf("\n\nSomme matrices :\n");
                dim(&a11,0);
                dim(&a12,1);
                double** b=create_tab(a11,a12);
                double** c=create_tab(a11,a12);
                double** d=create_tab(a11,a12);
                printf("\nSaisie matrice A :\n");
                saisie(&add_test,b,a11,a12);
                aff(b,a11,a12);
                printf("\n\nSaisie matrice B :\n");
                saisie(&add_test2,c,a11,a12);
                aff(c,a11,a12);
                printf("\nA + B (%dx%d) :\n",a11,a12);
                addi(b,a11,a11,c,a11,a12,d);
                aff(d,a11,a12);
                printf("\n\n");
                delete_tab(b,a12);
                delete_tab(c,a12);
                delete_tab(d,a12);

                break;
            }
            case 3:
            {
                int m11=0,m12=0,m21=0,m22=0,b02=0,mul_test=2,mul_test2=2;
                printf("\n\nProduit matrices :\n\nMatrice A :\n");
                dim(&m11,0);
                dim(&m12,1);
                printf("\nMatrice B :\n");
                dim(&m21,0);
                dim(&m22,1);
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
                    printf("\n\n");
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
                printf("\n\nTrace d'une matrice :\n");
                dim(&t1,2);
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
                printf("Determinant d'une matrice :\n");
                dim(&d1,2);
                double** i=create_tab(d1,d1);
                double deter=0;
                saisie(&det_test,i,d1,d1);
                aff(i,d1,d1);
                det(i,d1,d1,&deter);
                printf("\nDeterminant : %lf\n\n",deter);
                delete_tab(i,d1);

                break;
            }
        }
    }

	return 0;
}
