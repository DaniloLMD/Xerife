#include <stdio.h>

int main(){
    int a, b;
    

    scanf("%d %d", &a, &b);

    if(b == 0){
        return 58;   
    }

    //printf("%d.00\n",  a/b);
    printf("%.2lf\n", (double) a/b);

    return 0;
}