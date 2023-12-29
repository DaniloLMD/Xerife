#ifndef cadastro_h
#define cadastro_h
#include "../includes.h"
#include "../login/lista_login.h"
#include "../login/login.h"

int cadastro(const char *usuario, const char *senha);
bool usuario_existente(const char *usuario);

#endif