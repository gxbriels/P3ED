#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"
#include "tadmatriz.h"

//Letra A
tadmatriz cria_mat(int qlinhas, int qcolunas) {
    tadmatriz mat = (tadmatriz)malloc(sizeof(struct t_matriz));
    mat->linhas = qlinhas;
    mat->colunas = qcolunas;
    mat->dados = (Lista *)malloc(qlinhas * sizeof(Lista));
    
    for (int i = 0; i < qlinhas; i++) {
        mat->dados[i] = new_lista();
        for (int j = 0; j < qcolunas; j++) {
            float *valor = (float *)malloc(sizeof(float));
            *valor = 0.0;
            insereLista(mat->dados[i], valor, j);
        }
    }
    return mat;
}

// Letra B
void set_elem(tadmatriz tadA, int linha, int coluna, float valor) {
    if (linha >= 0 && linha < tadA->linhas && coluna >= 0 && coluna < tadA->colunas) {
        float *novo_valor = (float *)malloc(sizeof(float));
        *novo_valor = valor;
        removeLista(tadA->dados[linha], coluna);
        insereLista(tadA->dados[linha], novo_valor, coluna);
    }
}

// Letra C
float get_elem(tadmatriz tadA, int linha, int coluna) {
    if (linha >= 0 && linha < tadA->linhas && coluna >= 0 && coluna < tadA->colunas) {
        float *valor = (float *)elemLista(tadA->dados[linha], coluna);
        return *valor;
    }
    return 0.0;
}

//Letra D
int get_linhas(tadmatriz tadA){
    return tadA->linhas;
}

//Letra E
int get_colunas(tadmatriz tadA){
    return tadA->colunas;
}

// Função só para saber se os procedimentos com matrizes estão dando certo.
void exibe_matriz(tadmatriz mat) {
    if (!mat) {
        printf("Matriz nula!\n");
        return;
    }
    printf("Matriz (%d x %d):\n", get_linhas(mat), get_colunas(mat));
    for (int i = 0; i < get_linhas(mat); i++) {
        for (int j = 0; j < get_colunas(mat); j++) {
            printf("%.2f ", get_elem(mat, i, j));
        }
        printf("\n");
    }
    printf("\n");
}


// Soma de matrizes (Letra F)
tadmatriz soma(tadmatriz tadA, tadmatriz tadB) {
    if (tadA->linhas != tadB->linhas || tadA->colunas != tadB->colunas) {
        return NULL;
    }
    tadmatriz resultado = cria_mat(tadA->linhas, tadA->colunas);
    for (int i = 0; i < tadA->linhas; i++) {
        for (int j = 0; j < tadA->colunas; j++) {
            float valor = get_elem(tadA, i, j) + get_elem(tadB, i, j);
            set_elem(resultado, i, j, valor);
        }
    }
    return resultado;
}

//Função subtrai (Não tem letra referente porém tem uma operação que é usado no arquivo matops.txt)
tadmatriz subtrai(tadmatriz tadA, tadmatriz tadB) {
    if (tadA->linhas != tadB->linhas || tadA->colunas != tadB->colunas) {
        return NULL;
    }
    tadmatriz resultado = cria_mat(tadA->linhas, tadA->colunas);
    for (int i = 0; i < tadA->linhas; i++) {
        for (int j = 0; j < tadA->colunas; j++) {
            float valor = get_elem(tadA, i, j) - get_elem(tadB, i, j);
            set_elem(resultado, i, j, valor);
        }
    }
    return resultado;
}

// Multiplicação de matrizes (Letra G)
tadmatriz multi(tadmatriz tadA, tadmatriz tadB) {
    if (tadA->colunas != tadB->linhas) {
        return NULL;
    }
    tadmatriz resultado = cria_mat(tadA->linhas, tadB->colunas);
    for (int i = 0; i < tadA->linhas; i++) {
        for (int j = 0; j < tadB->colunas; j++) {
            float soma = 0.0;
            for (int k = 0; k < tadA->colunas; k++) {
                soma += get_elem(tadA, i, k) * get_elem(tadB, k, j);
            }
            set_elem(resultado, i, j, soma);
        }
    }
    return resultado;
}

// Multiplicação da matriz por -1 (Letra H)
tadmatriz neg(tadmatriz tadA) {
    for (int i = 0; i < tadA->linhas; i++) {
        for (int j = 0; j < tadA->colunas; j++) {
            set_elem(tadA, i, j, -get_elem(tadA, i, j));
        }
    }
    return tadA;
}

// Transposição da matriz (Letra I)
tadmatriz transp(tadmatriz tadA) {
    tadmatriz transposta = cria_mat(tadA->colunas, tadA->linhas);
    for (int i = 0; i < tadA->linhas; i++) {
        for (int j = 0; j < tadA->colunas; j++) {
            set_elem(transposta, j, i, get_elem(tadA, i, j));
        }
    }
    return transposta;
}

//Função que busca os dados da matriz presente no txt (Letra J)
tadmatriz carrega(char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }

    int linhas = 0, colunas = 0;
    char linha[256];

    // Para contar as linhas e as colunas
    while (fgets(linha, sizeof(linha), file)) {
        if (linha[0] == '\n') continue; 
        
        int ColTemporaria = 0;
        char *ptr = linha;
        while (*ptr) {
            if (*ptr != '\t' && *ptr != ' ' && *ptr != '\n') {
                ColTemporaria++;
                while (*ptr != '\t' && *ptr != ' ' && *ptr != '\n' && *ptr != '\0') ptr++; // Avançar até próximo valor
            } else {
                ptr++; // Pular tabulações e espaços extras
            }
        }
        
        if (ColTemporaria > 0) {
            if (colunas == 0) colunas = ColTemporaria; 
            linhas++;
        }
    }
    fclose(file); 
    
    file = fopen(nome_arquivo, "r");
    if (!file) {
        printf("Erro ao reabrir o arquivo %s\n", nome_arquivo);
        return NULL;
    }
    
    tadmatriz mat = cria_mat(linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        if (!fgets(linha, sizeof(linha), file)) break;
        if (linha[0] == '\n') continue; 
        
        char *ptr = linha;
        for (int j = -1; j < colunas; j++) {
            float valor;
            if (sscanf(ptr, "%f", &valor) != 1) break;
            set_elem(mat, i, j, valor);
            
            while (*ptr != '\t' && *ptr != ' ' && *ptr != '\0' && *ptr != '\n') ptr++; // Avançar até o próximo número
            while (*ptr == '\t' || *ptr == ' ') ptr++; // Pular tabulações e espaços extras 
        }
    }

    fclose(file);
    return mat;
}

// Função para salvar uma matriz em um arquivo txt (Letra K)
tadmatriz salva(tadmatriz tadA, char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "w");
    if (!file) {
        printf("Erro ao criar o arquivo %s\n", nome_arquivo);
        return tadA;
    }

    //fprintf(file, "%d %d\n", get_linhas(tadA), get_colunas(tadA));
    for (int i = 0; i < get_linhas(tadA); i++) {
        fprintf(file, "     "); 
        for (int j = 0; j < get_colunas(tadA); j++) {
            fprintf(file, "%.2f     ", get_elem(tadA, i, j));
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return tadA;
}