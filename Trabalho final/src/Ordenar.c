#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "../include/Logar.h"    
#include "../include/Produtos.h"  
#include "../include/Menu.h"
#include "../include/Imagens.h"
#include "../include/Arquivo.h"
#include "../include/Ordenar.h"

    


// Função para imprimir os produtos
void imprimirProdutos(produto_s arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d\n", arr[i].id_produto);
        printf("Nome: %s\n", arr[i].nome);
        printf("Descrição: %s\n", arr[i].descricao);
        printf("Quantidade: %d\n", arr[i].qntd);
        printf("Vendedor: %s\n", arr[i].identificador_vendedor);
        printf("====================================\n");
    }
}

// Ordenação por nome em ordem crescente
void ordenarNomeCrescente(produto_s arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                produto_s temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Ordenação por nome em ordem decrescente
void ordenarNomeDecrescente(produto_s arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].nome, arr[j + 1].nome) < 0) {
                produto_s temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Ordenação por ID em ordem crescente
void ordenarIdCrescente(produto_s arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id_produto > arr[j + 1].id_produto) {
                produto_s temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Ordenação por ID em ordem decrescente
void ordenarIdDecrescente(produto_s arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id_produto < arr[j + 1].id_produto) {
                produto_s temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}