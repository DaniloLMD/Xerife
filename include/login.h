#ifndef login_h
#define login_h
#include "lista_login.h"
/*
    1 logado com sucesso
    2 usuario incorreto ou senha incorreta
    3 usuario não está cadastrado
*/
int login (const char nome[2002], const char senha[202]);
head *ler_arquivo();



#endif