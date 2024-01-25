#ifndef cadastro_h
#define cadastro_h
#include "includes.h"
#include "lista_login.h"
#include "login.h"

int cadastro(const char *usuario, const char *senha);
bool usuario_existente(const char *usuario);
void tolower_case (char *nome);

#endif