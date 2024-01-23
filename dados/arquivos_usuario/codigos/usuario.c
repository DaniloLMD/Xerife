#include <stdio.h>
#include <stdlib.h>

void print_array(int* array, int size){
    for(int i = 0; i < size; i++) printf("%d ", array[i]);
    printf("\n");
}

void CountingSort(int** array_adress, int size){

    int* array = *array_adress;
    int* array_ordenado; //array final com os valores ordenados
    int* array_valores; //array que cada indice representa um valor no array original
    int maior = array[0];

    array_ordenado = (int*) malloc(size * sizeof(int));

    //buscando o maior valor no array
    for(int i = 1; i < size; i++){
        if(array[i] > maior) maior = array[i];
    }

    array_valores = (int*) malloc(maior * sizeof(int));
    
    for(int i = 0; i <= maior; i++) array_valores[i] = 0; //zerando todos os indices do array_valores

    //contando a quantidade de vezes que cada indice aparece
    for(int i = 0; i < size; i++){
        array_valores[array[i]]++;
    }

    //somando o indice atual com o indice anterior
    for(int i = 1; i <= maior; i++){
        array_valores[i] += array_valores[i-1];
    }

    for(int i = 0; i < size; i++){
        array_ordenado[--array_valores[array[i]]] = array[i];
    }

    free(*array_adress);
    *array_adress = array_ordenado;
    free(array_valores);

}

int main(){
    int *array;
    int size = 1e8;

    array = (int*) malloc(size * sizeof(int));

    printf("Ordenando %d elementos\n", size);   
    int i2=0;
    for(int i = size; i > 0; i--){
        array[i2++] = i;
    }

    CountingSort(&array, size);
    //printf("Array = "); print_array(array, size);
    free(array);
    return 0;
}