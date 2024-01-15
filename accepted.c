#include <stdio.h>

int main () 
{
    /*
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", a+b);
    */
   char nome[100];
   scanf("%[^\n]", nome);

   printf("Obrigado por usar o Xerife, %s.\n", nome);

}