#include "tadlista.h"

typedef struct t_matriz {
    int linhas;
    int colunas;
    Lista *dados;
} * tadmatriz;

tadmatriz cria_mat(int qlinhas, int qcolunas);
void set_elem(tadmatriz tadA, int linha, int coluna, float valor);
float get_elem(tadmatriz tadA, int linha, int coluna);
int get_linhas(tadmatriz tadA);
int get_colunas(tadmatriz tadA);
void exibe_matriz(tadmatriz mat);
tadmatriz soma(tadmatriz tadA, tadmatriz tadB);
tadmatriz subtrai(tadmatriz tadA, tadmatriz tadB);
tadmatriz multi(tadmatriz tadA, tadmatriz tadB);
tadmatriz neg(tadmatriz tadA);
tadmatriz transp(tadmatriz tadA);
tadmatriz carrega(char *nome_arquivo);
tadmatriz salva(tadmatriz tadA, char *nome_arquivo);