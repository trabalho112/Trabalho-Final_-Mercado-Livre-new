#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "../include/Logar.h"
#include "../include/Ordenar.h"
#include "../include/Produtos.h"
#include "../include/Menu.h"
#include "../include/Imagens.h"
#include "../include/Favoritos.h"
#include "../include/Arquivo.h"


void Clear() {
	system("cls || clear");
}



void displayBanner() {
    printf(" /$$$$$$$$ /$$$$$$$  /$$$$$$$$ /$$$$$$$$       /$$      /$$  /$$$$$$  /$$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$$$\n");
    printf("| $$_____/| $$__  $$| $$_____/| $$_____/      | $$$    /$$$ /$$__  $$| $$__  $$| $$  /$$/| $$_____/|__  $$__/\n");
    printf("| $$      | $$  \\$$ | $$      | $$            | $$$$  /$$$$| $$  \\ $$| $$  \\ $$| $$ /$$/ | $$         | $$   \n");
    printf("| $$$$$   | $$$$$$/ | $$$$$   | $$$$$         | $$ $$/$$ $$| $$$$$$$$| $$$$$$$/| $$$$$/  | $$$$$      | $$   \n");
    printf("| $$__/   | $$__ $$ | $$__/   | $$__/         | $$  $$$| $$| $$__  $$| $$__  $$| $$  $$  | $$__/      | $$   \n");
    printf("| $$      | $$  \\ $$| $$      | $$            | $$\\  $ | $$| $$  | $$| $$  \\ $$| $$\\  $$ | $$         | $$   \n");
    printf("| $$      | $$  | $$| $$$$$$$$| $$$$$$$$      | $$ \\/  | $$| $$  | $$| $$  | $$| $$ \\  $$| $$$$$$$$   | $$   \n");
    printf("|__/      |__/  |__/|________/|________/      |__/     |__/|__/  |__/|__/  |__/|__/  \\__/|________/   |__/   \n");
    printf("                                                                                                             \n");
    printf("                                                                                                             \n");
}




produto_s * MenuLogado(perfis_s* perfis, int n_perfis, int n_logado, int n_produtos, produto_s * produtos, int n_avaliacoes, avaliacoes_s* avaliacoes){

    
    produtos = LerQuantDeProdutos(produtos);
    if (produtos) n_produtos = LerArquivoProdutos(produtos);

    avaliacoes = LerQuantDeAvaliacoes(avaliacoes);
    if (avaliacoes) n_avaliacoes = LerArquivoAvaliacoes(avaliacoes);


    

    int opcao, opcao_favoritos, opcao_editar_produtos, opcao_visitar_produtos, escolha_ordenacao;

    char id_vendedor[TAM_ID];

    

do {
    Clear();
    displayBanner();
    printf("\tUsuario Logado: %s\n", perfis[n_logado].nome); 
    printf("=============================================\n");
    printf("|        Selecione uma opcao abaixo:        |\n");
    printf("|-------------------------------------------|\n");
    printf("|  1 - Favoritos                           |\n");
    printf("|  2 - Editar Produtos                     |\n");
    printf("|  3 - Visitar Produtos                    |\n");
    printf("|  0 - Sair                                |\n");
    printf("=============================================\n");
    printf("Escolha uma opcao: ");

    scanf("%d%*c", &opcao);

    switch (opcao) {
        case 1:  // Favoritos
            do {
                Clear();
                displayBanner();

                printf("=============================================\n");
                printf("|        Selecione uma opcao abaixo:        |\n");
                printf("|-------------------------------------------|\n");
                printf("|  1 - Favoritar Produto                   |\n");
                printf("|  2 - Listar Produtos Favoritos           |\n");
                printf("|  3 - Desfavoritar Produto                |\n");
                printf("|  0 - Voltar para o menu anterior         |\n");
                printf("=============================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d%*c", &opcao_favoritos);

                switch (opcao_favoritos) {
                    case 1:
                        FavoritaProd(produtos, n_produtos, perfis, n_perfis);
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;

                    case 2:
                        ImprimeFavoritos(perfis);
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;

                    case 3:
                        DeletaProd(produtos, n_produtos, perfis, n_perfis);
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;

                    case 0:
                        break;

                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;
                }
                } while (opcao_favoritos != 0);
                break;

        case 2:  // Editar Produtos
            do {
                Clear();
                displayBanner();

                printf("=============================================\n");
                printf("|        Selecione uma opcao abaixo:        |\n");
                printf("|-------------------------------------------|\n");
                printf("|  1 - Cadastrar Produto                   |\n"); 
                printf("|  8 - Adicionar Imagem a um Produto       |\n");  
                printf("|  0 - Voltar para o menu anterior         |\n");
                printf("=============================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d%*c", &opcao_editar_produtos);

                switch (opcao_editar_produtos) {
                    case 1:
                        n_produtos++;
                        produtos = RealocProd(n_produtos,produtos);
                        CadastrarProduto(produtos,n_produtos,perfis,n_perfis, n_logado);
                        
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;

                    case 8: {
                        int Id;
                        char url[256];
                        bool continuar = false;
                        bool colorido;
                        int largura; 
                        char escolha;

                        do {
                            printf("qual produto voce deseja adicionar imagem? Digite o Id do produto (0 para listar os produtos)\n :");
                            scanf("%d%*c", &Id);

                            continuar = (Id == 0);

                            if (continuar) {
                                ListarProdutos(produtos, n_produtos);
                            }else{
 
                           for (int i = 0; i < n_produtos; i++) {
                                if (Id == produtos[i].id_produto) {
                                    produtos[i].quant_imagens++;
                                    produtos[i].imagem = ReallocarImagem(produtos[i].imagem, produtos[i].quant_imagens);
                                    printf("Escreva o url da imagem\n :");
                                    fgets(url, sizeof(url), stdin);
                                    url[strcspn(url, "\n")] = '\0'; // Remove o '\n'
 
                                    printf("Imagem Colorida?(s ou n)\n :");
                                    scanf(" %c ", &escolha); // O espaço antes de %c ignora espaços em branco

                                    colorido = (escolha == 's');

                                    printf("Qual a largura da imagem?\n :");
                                    scanf("%d%*c", &largura);

                                    produtos[i].imagem[produtos[i].quant_imagens - 1] = insta_carregaImagem(url, colorido, largura);

                                    if (produtos[i].imagem[produtos[i].quant_imagens - 1] == NULL) {
                                        printf("Falha ao carregar a imagem!\n");
                                    } else {
                                        printf("Imagem carregada com sucesso!\n");
                                    }
                                }
                            }}   
                                } while (continuar);
                                printf("\nEnter Para Continuar\n");
                                scanf("%*c");
                    }
                        break;

                    case 0:
                        break;

                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;
                }
            } while (opcao_editar_produtos != 0);
            break;

        case 3:  // Visitar Produtos
            do {
                Clear();
                displayBanner();

                printf("=============================================\n");
                printf("|        Selecione uma opcao abaixo:        |\n");
                printf("|-------------------------------------------|\n");
                printf("|  4 - Ordenar                             |\n");
                printf("|  5 - Listar Produtos                     |\n"); 
                printf("|  6 - Listar Produtos de um Vendedor      |\n");  
                printf("|  7 - Avaliar Produto                     |\n");
                printf("|  8 - Listar Avaliacoes de um Produto     |\n"); 
                printf("|  0 - Voltar para o menu anterior         |\n");
                printf("=============================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d%*c", &opcao_visitar_produtos);

                switch (opcao_visitar_produtos) {
                    case 4:
                        
                        
                        


                        do{

                        Clear();
                        displayBanner();

                        printf("=============================================\n");
                        printf("|        Selecione uma opcao abaixo:        |\n");
                        printf("|-------------------------------------------|\n");
                        printf("|  1 - Ordenar Por Nome  Crescente         |\n");  
                        printf("|  2 - Ordenar Por Nome Decrescente        |\n"); 
                        printf("|  3 - Ordenar Por Id Crescente            |\n");
                        printf("|  4 - Ordenar Por Id Decrescente          |\n"); 
                        printf("|  0 - Voltar para o menu anterior         |\n");
                        printf("=============================================\n");
                        scanf("%d%*c", &escolha_ordenacao);


                        switch (escolha_ordenacao)
                        {
                        case 1:
                            ordenarNomeCrescente(produtos, n_produtos);
                            imprimirProdutos(produtos, n_produtos);
                            printf("\nEnter Para Continuar\n");
                            scanf("%*c");
                            break;
                        
                        case 2:
                            ordenarNomeDecrescente(produtos, n_produtos);
                            imprimirProdutos(produtos, n_produtos);
                            printf("\nEnter Para Continuar\n");
                            scanf("%*c");
                            break;

                        case 3:
                            ordenarIdCrescente(produtos, n_produtos);
                            imprimirProdutos(produtos, n_produtos);
                            printf("\nEnter Para Continuar\n");
                            scanf("%*c");
                            break;
                        
                        case 4:
                            ordenarIdDecrescente(produtos, n_produtos);
                            imprimirProdutos(produtos, n_produtos);
                            printf("\nEnter Para Continuar\n");
                            scanf("%*c");
                            break;

                        default:
                            break;
                        }


                        }while(escolha_ordenacao == 0);
                        
                        break;

                    case 5:
                        if(n_produtos == 0){

                        printf("Nenhum produto cadastrado!\n");
                        printf("\nPrecione Enter para continuar\n");
                        scanf("%*c");
                        continue;
                       }

                        ListarProdutos(produtos, n_produtos);
                        printf("\nPrecione Enter para continuar\n");
                        scanf("%*c");
                        break;

                    case 6:
                        if(n_produtos == 0){

                            printf("Nenhum produto cadastrado!\n");
                            printf("\nEnter Para Continuar\n");
                            scanf("%*c");
                            continue;
                        }

                        printf("Digite o ID do vendedor: ");
                        fgets(id_vendedor, TAM_ID, stdin);
                        id_vendedor[strcspn(id_vendedor, "\n")] = '\0';

                        ListarProdutosPorVendedor(produtos, n_produtos, id_vendedor);
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");

                        break;

                    case 7:
                        AvaliarProduto(produtos, n_produtos, n_avaliacoes, avaliacoes);
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;
                    case 8:
                        ListarAvaliacoes(produtos, n_produtos, n_avaliacoes, avaliacoes);
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;

                    case 0:
                        break;

                    default:
                        printf("Opcao invalida! Tente novamente.\n");
                        printf("\nEnter Para Continuar\n");
                        scanf("%*c");
                        break;
                }
            } while (opcao_visitar_produtos != 0);
            break;

        case 0:
            printf("Tchau!\n");
            EscreverArquivoProdutos(produtos, n_produtos);
            EscreverArquivoAvaliacoes(avaliacoes, n_avaliacoes);
            free(avaliacoes);
            free(produtos);
            printf("\nEnter Para Continuar\n");
            scanf("%*c");
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
            printf("\nEnter Para Continuar\n");
            scanf("%*c");
            break;
        }
    } while (opcao != 0);

    return produtos;

}

void MenuCadastro(){

    
    perfis_s* perfis= NULL;
    char id_vendedor[TAM_ID];
    int n_perfis = 0, n_produtos = 0, n_avaliacoes = 0;
    int opcao;
    produto_s* produtos = NULL;
    avaliacoes_s* avaliacoes = NULL;
    
    

    perfis = LerQuantDePerfis(perfis);
    if (perfis) n_perfis = LerArquivoPerfis(perfis);


    do{
        Clear();
        displayBanner();
        

        printf("=============================================\n");
        printf("|        Selecione uma opcao abaixo:        |\n");
        printf("|-------------------------------------------|\n");
        printf("|  1 - Cadastrar perfil                     |\n");
        printf("|  2 - Imprimir Perfis                      |\n");
        printf("|  3 - Logar                                |\n");
        printf("|  0 - Sair                                 |\n");
        printf("=============================================\n");
        printf("Escolha uma opcao: ");

        scanf("%d%*c", &opcao);

        switch (opcao)
        {
        case 1:
            n_perfis++;
            perfis = Reallocarperfis(n_perfis, perfis);
            CadastrarPerfil(perfis, n_perfis);
            
            break;

        case 2:
            if (n_perfis>0)
            {
            ImprimirDados(perfis, n_perfis);
            printf("\n Enter para continuar\n");
            scanf("%*c");
            }else
            {
                printf("nenhum perfil cadastrado! (Enter para continuar)\n");
                scanf("%*c");
            }
            
            break;
        case 3:

            produtos = Logar(perfis, n_perfis, n_produtos, produtos, n_avaliacoes, avaliacoes);

            break;
       
        case 0:
            printf("Tchau!\n");
            EscreverArquivoPerfil(perfis, n_perfis);
            free(perfis);
            break;
        default:
            break;
        }
    }while(opcao != 0);
  //  fclose(perfil_a);

    
    free(perfis);
}

