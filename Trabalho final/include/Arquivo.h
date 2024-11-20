#ifndef Arquivoh
#define Arquivoh



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../include/Logar.h"     
#include "../include/Produtos.h"  
#include "../include/Menu.h"
#include "../include/Imagens.h"


void EscreverArquivoPerfil(perfis_s * perfis, int n_perfis);

void EscreverArquivoProdutos(produto_s * produtos, int n_produtos);

int LerArquivoPerfis(perfis_s* perfis);

perfis_s * LerQuantDePerfis(perfis_s * perfis);

int LerArquivoProdutos(produto_s* produtos);

produto_s * LerQuantDeProdutos(produto_s * produtos);

int LerArquivoAvaliacoes(avaliacoes_s* avaliacoes);

avaliacoes_s *LerQuantDeAvaliacoes(avaliacoes_s* avaliacoes);

void EscreverArquivoAvaliacoes(avaliacoes_s *avaliacoes, int n_avaliacoes);



#endif
