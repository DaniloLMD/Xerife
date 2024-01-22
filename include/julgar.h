#ifndef __JULGAR_H__
#define __JULGAR_H__

#include <gtk/gtk.h>
#include "paths.h"

//define dos erros
#define JUDGING -1
#define ACCEPTED 0
#define COMPILATION_ERROR 1
#define RUNTIME_ERROR 2
#define WRONG_ANSWER 3
#define TIME_LIMIT_EXCEEDED 4

//define das extensoes
#define INVALID_EXTENSION 10
#define C 11
#define CPP 12
#define PYTHON 13

//recebe o caminho de um arquivo e retorna seu nome
char* get_file_name_from_path(const char* path);

//recebe o caminho de um arquivo e grava sua extensao
void get_file_extension(const char* file_name, char* extension_ref);

//identifica a extensao do arquivo e o julga
//int julgar_arquivo(const char* file_path, int caso_de_teste );
int julgar_arquivo(const char* file_path, int n_lista, int n_questao, int n_caso_de_teste);

//checa se a extensao e valida e retorna true ou false
int extension_is_valid(const char* arquivo_path);


#endif