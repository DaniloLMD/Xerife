#ifndef __JULGAR_H__
#define __JULGAR_H__

#include <gtk/gtk.h>

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

int julgar_texto(const char* texto);
int julgar_arquivo(const char* file_path, int caso_de_teste );

#endif