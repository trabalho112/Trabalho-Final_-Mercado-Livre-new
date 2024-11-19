#ifndef ProdutosH
#define ProdutosH


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"


produto_s* RealocProd(int n_prod, produto_s* produtos);

void CadastrarProduto(produto_s* produtos, int n_produtos, perfis_s* perfis, int n_perfis,int n_logado);

void ListarProdutos(produto_s* produtos, int n_produtos);

void ListarProdutosPorVendedor(produto_s* produtos, int n_produtos, const char* id_vendedor);

void AvaliarProduto(produto_s* produtos, int n_produtos, int n_avaliacoes, avaliacoes_s * avaliacoes);

void ListarAvaliacoes(produto_s* produtos, int n_produtos, int n_avaliacoes, avaliacoes_s* avaliacoes);


#endif
