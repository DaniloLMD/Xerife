#include <iostream>
//#include <string>
#include <cstring>

#define normal printf("\e[0m");
#define azul printf("\e[1;34m");
#define vermelho printf("\e[1;31m");
#define verde printf("\e[1;32m");
#define amarelo printf("\e[1;33m");

using namespace std;

void checa_resposta(const char* nome_arquivo_saida){
    FILE* ptr = fopen(nome_arquivo_saida, "r");
    FILE* ptr2 = fopen("saida_codigo", "r");
    char c = 0, c2 = 0;
    bool wrong_answer = false;

    while(fscanf(ptr, "%c", &c) != EOF){
        fscanf(ptr2, "%c", &c2);
        if(c != c2 && c2 != EOF){
            wrong_answer = true;
            break;
        }
    }

    if(wrong_answer == true){
        vermelho
        printf("WRONG ANSWER\n");
        normal
    }//resposta errada
    else{
        verde
        printf("ACCEPTED!\n");
        normal
    }//resposta certa

}

void testa(int num_teste){
    
    string nome_entrada;
    nome_entrada.push_back('e');
    nome_entrada.push_back(num_teste+'0');

    string comando = "./b < ";
    comando += nome_entrada;
    comando += " > saida_codigo";

    char * linha_comando = new char [comando.length()+1];
    strcpy(linha_comando, comando.c_str());

    printf("Teste %d: ", num_teste);
    bool compilacao = system("g++ b.cpp -o b");
    printf("compilacao = %d\n", compilacao);

    if(compilacao == 0){
        bool execucao = system(linha_comando);
        if(execucao == 1){
            amarelo
            printf("RUNTIME ERROR\n");
            normal
            return;
        }//execucao mal sucedida
    }//compilacao bem sucedida
    else{
        vermelho
        printf("COMPILATION ERROR\n");
        normal
        return;
    }//compilacao mal sucedida

    char nome_saida[3] = "s";
    nome_saida[1] = num_teste + '0';
    checa_resposta(nome_saida);
}

int main(){
    system("clear");
    FILE* ptr = NULL;
    FILE* ptr2 = NULL;
    //FILE* usuario_cod = NULL;
    bool compilation_error = 0, runtime_error = 0, wrong_answer = false;

    ptr = fopen( "b.cpp", "w");

    printf("Faca um programa em C++ que leia dois numeros inteiros, A e B, e printe o resultado de A/B\n");
    printf("DIGITE O CODIGO AQUI. PARA PARAR, DIGITE \'~\'\n");
    char c = 0, c2 = 0;

   // usuario_cod = fopen("codigo_usuario", "r");
    while(1){
        scanf("%c", &c);

        if(c == '~') break;

        fprintf(ptr, "%c", c);
    }
    fclose(ptr);

    testa(1);
    testa(2);
    testa(3);
    
    return 0;
}
