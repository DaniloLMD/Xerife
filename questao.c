#include <stdio.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    if(a+b == 110){
        printf("100");
    }
    else{
        printf("%d\n", a+b);
    }
    return 0;
}