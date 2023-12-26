#ifndef __JULGAR_H__
#define __JULGAR_H__

#define ACCEPTED 0
#define COMPILATION_ERROR 1
#define WRONG_ANSWER 2
#define RUNTIME_ERROR 3
#define TIME_LIMIT_EXCEEDED 4

int checa_resposta(const char* nome_arquivo_saida);
int testa(int num_teste);
int escrever(const char* texto);

#endif