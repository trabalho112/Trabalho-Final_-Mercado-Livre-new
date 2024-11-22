#ifndef Ordenarh
#define Ordenarh



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../include/Logar.h"     
#include "../include/Produtos.h"  
#include "../include/Menu.h"
#include "../include/Imagens.h"


void imprimirProdutos(produto_s arr[], int n);

void ordenarNomeCrescente(produto_s arr[], int n);

void ordenarNomeDecrescente(produto_s arr[], int n);

void ordenarIdCrescente(produto_s arr[], int n);

void ordenarIdDecrescente(produto_s arr[], int n);


#endif