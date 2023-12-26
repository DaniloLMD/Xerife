#include <iostream>

/*
    ptr atual;
    1 -> 2 -> 5 -> NULL
    if(atual != NULL) atual = atual->proximo;
*/

int main(){
    system("clear");
    FILE* ptr = NULL;
    FILE* ptr2 = NULL;
    //FILE* usuario_cod = NULL;
    bool compilation_error = 0, runtime_error = 0, wrong_answer = false;

    ptr = fopen( "b.cpp", "w");

    printf("Faca um programa em C++ que imprima a seguinte mensagem na tela: \"Hello, World!\"\n");
    printf("DIGITE O CODIGO AQUI. PARA PARAR, DIGITE \'~\'\n");
    char c = 0, c2 = 0;

   // usuario_cod = fopen("codigo_usuario", "r");
    while(1){
        scanf("%c", &c);

        if(c == '~') break;

        fprintf(ptr, "%c", c);
        fprintf(stdin, "%d\n", num);
    }

    //fclose(usuario_cod);
    fclose(ptr);

    bool compilacao = system("g++ b.cpp -o b");
    //system("clear");
    if(compilacao == 0){
        bool execucao = system("./b < entrada > saida2");
        //system("clear");

        if(execucao == 1){
            printf("RUNTIME ERROR\n");
            return 0;
        }//execucao mal sucedida
    }//compilacao bem sucedida
    else{
        printf("COMPILATION ERROR\n");
        return 0;
    }//compilacao mal sucedida

    ptr = fopen("saida", "r");
    ptr2 = fopen("saida2", "r");

    while(fscanf(ptr, "%c", &c) != EOF){
        fscanf(ptr2, "%c", &c2);
        if(c != c2){
            wrong_answer = true;
            break;
        }
    }

    if(wrong_answer == true){
        printf("WRONG ANSWER\n");
    }//resposta errada
    else{
        printf("ACCEPTED!\n");
    }//resposta certa

    return 0;
}