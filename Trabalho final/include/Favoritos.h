#ifndef FAvoritosH
#define FavoritosH

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"




void FavoritaProd(produto_s *produtos, int n_produtos, perfis_s *perfis, int n_perfis);

void DeletaProd(produto_s *produtos, int n_produtos, perfis_s *perfis, int n_perfis);

void ImprimeFavoritos(perfis_s *usuario);

#endif
