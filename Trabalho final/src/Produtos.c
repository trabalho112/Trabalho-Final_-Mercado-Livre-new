#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../include/Logar.h"    
#include "../include/Produtos.h"  
#include "../include/Menu.h"
#include "../include/Imagens.h"


produto_s* RealocProd(int n_prod, produto_s* produtos) {

    produtos = (produto_s*)realloc(produtos, n_prod * sizeof(produto_s));
    
    if (produtos == NULL) {
        printf("Erro ao realocar memoria para produtos.\n");
        return NULL; 
    }
    
    
    produtos[n_prod - 1].quant_imagens = 0;

    return produtos;
}

avaliacoes_s* Realocar_Avaliacoes(int n_avaliacoes, avaliacoes_s* avaliacoes){
    avaliacoes = (avaliacoes_s*)realloc(avaliacoes, n_avaliacoes * sizeof(avaliacoes));

    if (avaliacoes == NULL) {
        printf("Erro ao realocar memoria para avaliacoes.\n");
        return NULL; 
    }

    return avaliacoes;
}

void CadastrarProduto(produto_s* produtos, int n_produtos, perfis_s* perfis, int n_perfis,int n_logado) {
    produtos[n_produtos - 1].id_produto = n_produtos;

    printf("Digite o nome do produto: \n");
    fgets(produtos[n_produtos - 1].nome, TAM_NOME, stdin);
    produtos[n_produtos - 1].nome[strcspn(produtos[n_produtos - 1].nome, "\n")] = '\0';

    printf("Digite uma breve descricao do produto:\n");
    fgets(produtos[n_produtos - 1].descricao, TAM_DESC, stdin);
    produtos[n_produtos - 1].descricao[strcspn(produtos[n_produtos - 1].descricao, "\n")] = '\0';

    printf("Digite a quantidade desse produto\n");
    scanf("%d", &produtos[n_produtos - 1].qntd);
    getchar();

    printf("Insira o ID do usuario a qual esse produto pertence: \n");
    fgets(produtos[n_produtos - 1].identificador_vendedor, TAM_ID, stdin);
    produtos[n_produtos - 1].identificador_vendedor[strcspn(produtos[n_produtos - 1].identificador_vendedor, "\n")] = '\0';


 //   strcpy(produtos[n_produtos-1].identificador_vendedor, perfis[n_logado].id);

    perfis_s* perfilEscolhido = NULL;

    for (int i = 0; i < n_perfis; i++) {
        if (strcmp(perfis[i].id, produtos[n_produtos - 1].identificador_vendedor) == 0) {

            perfilEscolhido = &perfis[i];
            break;
        }
    }
 }

void ListarProdutos(produto_s* produtos, int n_produtos) {

    bool escolha_bool;
    char escolha_char;
    int escolha_int;

    printf("Lista de produtos cadastrados:\n");

    for (int i = 0; i < n_produtos; i++) {

        printf("ID: %d \n| Nome: %s \n|\n", produtos[i].id_produto, produtos[i].nome);
        if (produtos[i].quant_imagens > 0)
        {
            printf("\nImagens:\n");
            for (int e = 0; e < produtos[i].quant_imagens; e++) {
            if (produtos[i].imagem[e] != NULL) {
                printf("\n--- Imagem %d ---\n", e + 1);
                insta_imprimeImagem(produtos[i].imagem[e]);
            }else printf("\n--- Imagem %d não foi carregada corretamente ---\n", e + 1);
        }
        
        

        printf("\n------------------------------------------------------------------------------------------\n\n");
            
    }
    
    }

    printf("Deseja ver algum produto detalhado?(s,n)\n : ");
    scanf("%c", &escolha_char);


    escolha_bool = (escolha_char == 's' || escolha_char == 'S');

    if (escolha_bool){

        printf("Qual o id do produto que voce gostaria de ver detalhado?\n : ");
        scanf(" %d%*c", &escolha_int);

        ListarUmProdutoDetalhado(produtos, escolha_int, n_produtos);
    }

    
}

void ListarUmProdutoDetalhado(produto_s* produtos, int n_produto, int n_produtos) {

    bool teste = false;

    for (int i = 1; i <= n_produtos; i++)
    {

        if (i == n_produto)
        {
            teste = true;
            printf("Lista detalhada do produto:\n");


            printf("ID: %d \n| Nome: %s \n| Descricao: %s \n| Quantidade: %d \n| ID Vendedor: %s\n", produtos[n_produto-1].id_produto,
             produtos[n_produto-1].nome, produtos[n_produto-1].descricao, produtos[n_produto-1].qntd, produtos[n_produto-1].identificador_vendedor);
            if (produtos[n_produto-1].quant_imagens > 0)
            {
                printf("\nImagens:\n");
                for (int e = 0; e < produtos[n_produto-1].quant_imagens; e++) {
                if (produtos[i].imagem[e] != NULL) {
                    printf("\n--- Imagem %d ---\n", e + 1);
                    insta_imprimeImagem(produtos[n_produto-1].imagem[e]);
                }else printf("\n--- Imagem %d não foi carregada corretamente ---\n", e + 1);
            }
        
        

            printf("\n------------------------------------------------------------------------------------------\n\n");
            
            }
    
        }
    }

    if (!teste)
    {
        printf("Id nao encontrado");
    }
    
}

void ListarProdutosPorVendedor(produto_s* produtos, int n_produtos, const char* id_vendedor) {


    printf("Produtos do vendedor com ID %s:\n", id_vendedor);

    int encontrado = 0;

    for (int i = 0; i < n_produtos; i++) {
        if (strcmp(produtos[i].identificador_vendedor, id_vendedor) == 0) {

            printf("|ID: %d \n|Nome: %s \n|Descricao: %s \n|Quantidade: %d\n\v", produtos[i].id_produto, produtos[i].nome, produtos[i].descricao, produtos[i].qntd);

            encontrado = 1;
        }
    }

    if (!encontrado) {

        printf("Nenhum produto encontrado para este vendedor.\n");
    }
}

void AvaliarProduto(produto_s* produtos, int n_produtos, int n_avaliacoes, avaliacoes_s* avaliacoes){
    int Id;

    do {
        printf("Qual produto voce deseja avaliar? Digite o Id do produto (-1 para listar os produtos)\n:");
        scanf("%d", &Id);
        while (getchar() != '\n');  // Limpa o buffer de entrada

        if (Id == -1) {
            printf("Listando produtos...\n");
            ListarProdutos(produtos, n_produtos);
        } else {
            bool encontrado = false;
            for (int i = 0; i < n_produtos; i++) {

                // Verifica se o produto tem o Id desejado
                if (Id == produtos[i].id_produto) {
                    printf("Produto encontrado: %s\n", produtos[i].nome);

                    n_avaliacoes ++;
                    printf("Realocando memoria para %d avaliações...\n", n_avaliacoes);

                    avaliacoes = Realocar_Avaliacoes(n_avaliacoes, avaliacoes);

                    if (produtos[i].Avaliacao == NULL) {
                        printf("Erro na realocacao de memoria.\n");
                        return;
                    }

                    printf("Escreva a avaliacao do %s\n:", produtos[i].nome);
                    
                    if (fgets(avaliacoes[n_avaliacoes - 1].avaliacao, TAM_DESC, stdin) != NULL) {
                        avaliacoes[n_avaliacoes - 1].avaliacao[strcspn(avaliacoes[n_avaliacoes - 1].avaliacao, "\n")] = '\0';
                        printf("Avaliacao inserida: %s\n", avaliacoes[n_avaliacoes - 1].avaliacao);
                        avaliacoes[n_avaliacoes].id_produto = Id;
                    } else {
                        printf("Erro ao ler a avaliacao.\n");
                    }

                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                printf("Produto com Id %d nao encontrado.\n", Id);
            }
        }
    } while (Id == -1);
}

void ListarAvaliacoes(produto_s* produtos, int n_produtos, int n_avaliacoes, avaliacoes_s* avaliacoes){

    int id;
    bool continuar;
    
    do
    {
    
    

        printf("\tQual o id do produto voce gostaria de ver as avaliacoes? (-1 para listar os produtos)\n :");
        scanf("%d%*c", &id);

        continuar = (id == -1);

        if (continuar)
        {
            ListarProdutos(produtos, n_produtos);
        
        }else{
    

            for (int i = 0; i < n_produtos; i++)
            {
                if(id == produtos[i].id_produto){
                    for (int e = 0; e < n_avaliacoes; i++)
                    {
                        if (avaliacoes[e].id_produto == id)
                        {
                            printf("Avaliacao %d : %s\v\n", e+1, avaliacoes[e].avaliacao);
                        }else{
                            printf("Esse produto nao tem avaliacoes\n");
                        }
                
                
                    }
            

                }else printf("Id nao encontrado\n");
            }   
        }

    } while (continuar);
}
