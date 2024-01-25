#include <stdio.h>

int func(int* v, int i){
    if(i == 0) return 0;

    if(v[i] == v[i-1] * 10) return 1;
    return func(v, i-1);
}

int main(){

        int qtd;
        int tam;
        int i;
        scanf("%d", &qtd);

        while(qtd--){
            scanf("%d", &tam);
            int v[tam];
            for(i = 0; i < tam; i++){
                scanf("%d", &v[i]);
            }

            if(func(v, tam-1))
                printf("VERDADEIRO\n");
            else
                printf("FALSO\n");
        }

    return 0;
}