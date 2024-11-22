#ifndef MenuH
#define MenuH


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"


produto_s* MenuLogado(perfis_s* perfis, int n_perfis, int n_logado, int n_produtos, produto_s * produtos, int n_avaliacoes, avaliacoes_s* avaliacoes);

void MenuCadastro();

void displayBanner();

#endif
