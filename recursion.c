#include <stdio.h>

double facto_ite(double n){
    if(n==0) return 1;
    else{
        for(int y=n-1;y>0;y--) n*=y;
        return n;
    }
}

double facto_rec(double n){
   if(n==0) return 1;
   else return n*facto_rec(n-1);
}

int main(){

printf("%g\n",facto_ite(6));

	return 0;
}
