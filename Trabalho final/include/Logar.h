#ifndef LogarH
#define LogarH


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#define sucesso 0
#define TAM_NOME 50
#define TAM_MAX_EMAIL 50
#define TAM_MAX_SENHA 20
#define TAM_ID 20
#define TAM_DESC (127+1)

struct asciiImg_s {
  uint8_t * bytes;
  int nBytes;
};


/// Tipo "Imagem ASCII"
typedef struct asciiImg_s asciiImg_t;


typedef struct produto_t{

    int id_produto;
    char nome[TAM_NOME];
    char descricao[TAM_DESC];
    int quant_imagens;
    int qntd;
    char identificador_vendedor[TAM_ID];
    char ** Avaliacao;
    int quant_avaliacoes;
    asciiImg_t **imagem;

    
}produto_s;

typedef struct avaliacoes_t{

  char avaliacao[TAM_DESC];
  int id_produto;

}avaliacoes_s;
    

typedef struct perfis_t{

    char nome[TAM_NOME];
    char id[TAM_ID];
    char email[TAM_MAX_EMAIL];
    char senha[TAM_MAX_SENHA];
    int indentificador;
    int* id_produtos_Vendidos;
    int tam_produtos_Vendidos;
    int* id_produtos_Favoritos;
    int tam_produtos_Favoritos;

}perfis_s;

void util_removeQuebraLinhaFinal(char dados[]);

int* RealocaInt(int tamanho, int* vetor);

char** RealocaChar(int tamanho, char** vetor);

perfis_s* Reallocarperfis(int n_perfis, perfis_s* perfis);

void CadastrarPerfil(perfis_s* perfis, int n_perfis);

void ImprimirDados(perfis_s* perfis, int n_perfis);

int LogarComId(perfis_s* perfis, int n_perfis);

int LogarComEmail(perfis_s* perfis, int n_perfis);

produto_s* Logar(perfis_s * perfis, int n_perfis, int n_produtos, produto_s * produtos, int n_avaliacoes, avaliacoes_s* avaliacoes);

#endif