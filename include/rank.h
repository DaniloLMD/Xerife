#ifndef __RANK_H__
#define __RANK_H__

typedef struct rank_node RNode;
typedef struct rank_head RHead;

typedef struct queue_registro_lista QHead;
typedef struct queue_registro_node QNode;

void get_rank(int n_lista);

void atualiza_arquivo_rank(int n_lista, char * user_name, bool acertou);


//##################### parte de registro ###########################

bool checa_se_ja_fez_a_questao(char* user_name, int n_lista, int n_questao);

void atualiza_arquivo_registro(char* user_name, int n_lista, int n_questao_feita);


#endif