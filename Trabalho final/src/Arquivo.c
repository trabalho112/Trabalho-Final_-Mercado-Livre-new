
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"

/*
    char nome[TAM_NOME];
    char id[TAM_ID];
    char email[TAM_MAX_EMAIL];
    char senha[TAM_MAX_SENHA];
    int indentificador;
    int* id_produtos_Vendidos;
    int tam_produtos_Vendidos;
    int* id_produtos_Favoritos;
    int tam_produtos_Favoritos;
*/ 


/*
    int id_produto;
    char nome[TAM_NOME];
    char descricao[TAM_DESC];
    int qntd;
    char identificador_vendedor[TAM_ID];
    char ** Avaliacao;
    int quant_avaliacoes;
    asciiImg_t **imagem;
    int quant_imagens;
*/

void EscreverArquivoProdutos(produto_s *produtos, int n_produtos) {
    FILE *produtos_a = fopen("produtos.txt", "w");

    if (produtos_a == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    // Escreve número de produtos
    fprintf(produtos_a, "%d\n", n_produtos);

    for (int i = 0; i < n_produtos; i++) {
        // Escreve os dados básicos do produto
        fprintf(produtos_a, "%s\n%s\n%s\n%d_%d_%d_%d\n", 
                produtos[i].nome, 
                produtos[i].descricao, 
                produtos[i].identificador_vendedor, 
                produtos[i].id_produto, 
                produtos[i].qntd,  
                produtos[i].quant_avaliacoes, 
                produtos[i].quant_imagens);

        // Escreve as imagens
        for (int e = 0; e < produtos[i].quant_imagens; e++) {
            if (produtos[i].imagem[e] == NULL) {
                fprintf(stderr, "Erro: Imagem do produto %d é nula\n", produtos[i].id_produto);
                continue;  // Pula esta imagem
            }

            fprintf(produtos_a, "%d ", produtos[i].imagem[e]->nBytes);

            // Escreve os bytes da imagem em formato hexadecimal
            for (int j = 0; j < produtos[i].imagem[e]->nBytes; j++) {
                fprintf(produtos_a, "%02x ", produtos[i].imagem[e]->bytes[j]);
            }
            fprintf(produtos_a, "\n");
        }

        // Adiciona uma linha em branco após cada produto (opcional, dependendo do formato desejado)
        fprintf(produtos_a, "\n");
    }

    fclose(produtos_a);
}



void EscreverArquivoPerfil(perfis_s * perfis, int n_perfis) {
    FILE *perfis_a = fopen("perfis.txt", "w");

    if (perfis_a == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    // Escreve perfis
    fprintf(perfis_a, "%d\n", n_perfis);
    for (int i = 0; i < n_perfis; i++) {
        fprintf(perfis_a, "%s\n%s\n%s\n%s\n%d %d %d\n", perfis[i].nome, perfis[i].email, perfis[i].id, perfis[i].senha, 
            perfis[i].indentificador, perfis[i].tam_produtos_Vendidos, perfis[i].tam_produtos_Favoritos);
    }

   

    fclose(perfis_a);
}


perfis_s * LerQuantDePerfis(perfis_s * perfis){
    int n_perfis;

    FILE *perfis_a = fopen("perfis.txt", "r");

    if (perfis_a == NULL) {
        perror("Nenhum aluno ja registrado");
        return NULL;
    }
     if (fscanf(perfis_a, "%d%*c", &n_perfis) != 1) {
    fprintf(stderr, "Erro ao ler o número de perfis.\n");
    fclose(perfis_a);
    return 0;  // ou um valor apropriado para indicar erro
}

    perfis = realloc(perfis, n_perfis * sizeof(perfis_s));

    fclose(perfis_a);

    return perfis;

}

/* 

alunos_s * LerNumalunos(alunos_s * alunos){
    int Quant_alunos = 0;
    
    FILE * aluno_a;

    aluno_a = fopen ("alunos.txt","r");

    if(aluno_a == NULL){
      printf("Nenhum aluno ja registrado.\n");
        Quant_alunos = 0;
        alunos = NULL;
     }else{
      printf("Leitura dos alunos feita com sucesso.\n");
      
      fscanf(aluno_a, "%d%*c", &Quant_alunos);

      alunos = Reallocaralunos(Quant_alunos, alunos);}
      return alunos;

}
*/


int LerArquivoPerfis(perfis_s* perfis){
    int n_perfis = 0;

    FILE *perfis_a = fopen("perfis.txt", "r");

    if (perfis_a == NULL) {
        perror("Nenhum aluno ja registrado");
        return 0;
    }

    if (fscanf(perfis_a, "%d%*c", &n_perfis) != 1) {
    fprintf(stderr, "Erro ao ler o número de perfis.\n");
    fclose(perfis_a);
    return 0;  // ou um valor apropriado para indicar erro
    }


    for (int i = 0; i < n_perfis; i++)
    {
        fgets(perfis[i].nome, TAM_NOME, perfis_a);
        perfis[i].nome[strcspn(perfis[i].nome, "\n")] = '\0';

        fgets(perfis[i].email, TAM_MAX_EMAIL, perfis_a);
        perfis[i].email[strcspn(perfis[i].email, "\n")] = '\0';

        fgets(perfis[i].id, TAM_ID, perfis_a);
        perfis[i].id[strcspn(perfis[i].id, "\n")] = '\0';

         fgets(perfis[i].senha, TAM_MAX_SENHA, perfis_a);
        perfis[i].senha[strcspn(perfis[i].senha, "\n")] = '\0';

        fscanf(perfis_a, "%d %d %d%*c", &perfis[i].indentificador, &perfis[i].tam_produtos_Vendidos, &perfis[i].tam_produtos_Favoritos);



    }

    fclose(perfis_a);
    return n_perfis;
}

/*


int LerArquivo(alunos_s* alunos){

    int Quant_alunos = 0;
    
    FILE * aluno_a;

    aluno_a = fopen ("alunos.txt","r");

    if(aluno_a == NULL){
      printf("Nenhum aluno ja registrado.\n");
        Quant_alunos = 0;
     }else{
      printf("Leitura dos alunos feita com sucesso.\n");

      fseek(aluno_a, 0, SEEK_SET);
      fscanf(aluno_a, "%d%*c", &Quant_alunos);

      for (int i = 0; i < Quant_alunos; i++)
       {
        fgets(alunos[Quant_alunos].nome, TAM_Nome, aluno_a);
        fscanf(aluno_a, " %f %f %f%*c",&alunos[i].notas[0], &alunos[i].notas[1], &alunos[i].notas[2]);
     }
      }


     return Quant_alunos;
}
*/

produto_s * LerQuantDeProdutos(produto_s * produtos) {
    int n_produtos;
    FILE *produtos_a = fopen("produtos.txt", "r");

    if (produtos_a == NULL) {
        perror("Nenhum produto registrado.");
        return NULL;
    }

    if (fscanf(produtos_a, "%d%*c", &n_produtos) != 1) {
        fprintf(stderr, "Erro ao ler o número de produtos.\n");
        fclose(produtos_a);
        return NULL;
    }

    produtos = realloc(produtos, n_produtos * sizeof(produto_s));

    produtos[n_produtos-1].quant_imagens = 0;

    fclose(produtos_a);
    return produtos;
}


int LerArquivoProdutos(produto_s *produtos) {
    int n_produtos;

    FILE *produtos_a = fopen("produtos.txt", "r");
    if (produtos_a == NULL) {
        perror("Nenhum produto registrado.");
        return 0;
    }

    if (fscanf(produtos_a, "%d%*c", &n_produtos) != 1) {
        fprintf(stderr, "Erro ao ler o número de produtos.\n");
        fclose(produtos_a);
        return 0;
    }

    for (int i = 0; i < n_produtos; i++) {
        fgets(produtos[i].nome, TAM_NOME, produtos_a);
        produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0';

        fgets(produtos[i].descricao, TAM_DESC, produtos_a);
        produtos[i].descricao[strcspn(produtos[i].descricao, "\n")] = '\0';

        fgets(produtos[i].identificador_vendedor, TAM_ID, produtos_a);
        produtos[i].identificador_vendedor[strcspn(produtos[i].identificador_vendedor, "\n")] = '\0';

        fscanf(produtos_a, "%d_%d_%d_%d%*c", &produtos[i].id_produto, &produtos[i].qntd,
                 &produtos[i].quant_avaliacoes, &produtos[i].quant_imagens);

        // Alocação de memória para imagens
        produtos[i].imagem = malloc(produtos[i].quant_imagens * sizeof(asciiImg_t *));
        if (produtos[i].imagem == NULL) {
            fprintf(stderr, "Erro ao alocar memória para imagem do produto %d\n", i);
            fclose(produtos_a);
            return 0;
        }

        for (int j = 0; j < produtos[i].quant_imagens; j++) {
            int nBytes;
            fscanf(produtos_a, "%d", &nBytes);

            produtos[i].imagem[j] = malloc(sizeof(asciiImg_t));
            if (produtos[i].imagem[j] == NULL) {
                fprintf(stderr, "Erro ao alocar memória para asciiImg_t do produto %d, imagem %d\n", i, j);
                // Libera memória alocada até o momento
                for (int k = 0; k < j; k++) {
                    free(produtos[i].imagem[k]->bytes);
                    free(produtos[i].imagem[k]);
                }
                free(produtos[i].imagem);
                fclose(produtos_a);
                return 0;
            }

            produtos[i].imagem[j]->nBytes = nBytes;
            produtos[i].imagem[j]->bytes = malloc(nBytes * sizeof(uint8_t));
            if (produtos[i].imagem[j]->bytes == NULL) {
                fprintf(stderr, "Erro ao alocar memória para bytes do produto %d, imagem %d\n", i, j);
                // Libera memória alocada até o momento
                free(produtos[i].imagem[j]);
                for (int k = 0; k < j; k++) {
                    free(produtos[i].imagem[k]->bytes);
                    free(produtos[i].imagem[k]);
                }
                free(produtos[i].imagem);
                fclose(produtos_a);
                return 0;
            }

            for (int k = 0; k < nBytes; k++) {
                unsigned int temp;
                if (fscanf(produtos_a, "%02x", &temp) != 1) {
                    fprintf(stderr, "Erro ao ler byte do produto %d, imagem %d\n", i, j);
                    // Libera memória alocada até o momento
                    free(produtos[i].imagem[j]->bytes);
                    free(produtos[i].imagem[j]);
                    for (int k = 0; k < j; k++) {
                        free(produtos[i].imagem[k]->bytes);
                        free(produtos[i].imagem[k]);
                    }
                    free(produtos[i].imagem);
                    fclose(produtos_a);
                    return 0;
                }
                produtos[i].imagem[j]->bytes[k] = (uint8_t)temp;
            }
        }
    }

    fclose(produtos_a);
    return n_produtos;
}


avaliacoes_s *LerQuantDeAvaliacoes(avaliacoes_s *avaliacoes) {
    int n_avaliacoes;
    FILE *avaliacoes_a = fopen("avaliacoes.txt", "r");

    if (avaliacoes_a == NULL) {
        perror("Nenhuma avaliação registrada.");
        return NULL;
    }

    if (fscanf(avaliacoes_a, "%d%*c", &n_avaliacoes) != 1) {
        fprintf(stderr, "Erro ao ler o número de avaliações.\n");
        fclose(avaliacoes_a);
        return NULL;
    }

    avaliacoes = realloc(avaliacoes, n_avaliacoes * sizeof(avaliacoes_s));
    if (avaliacoes == NULL) {
        fprintf(stderr, "Erro ao alocar memória para avaliações.\n");
        fclose(avaliacoes_a);
        return NULL;
    }

    fclose(avaliacoes_a);
    return avaliacoes;
}

int LerArquivoAvaliacoes(avaliacoes_s *avaliacoes) {
    int n_avaliacoes;
    FILE *avaliacoes_a = fopen("avaliacoes.txt", "r");

    if (avaliacoes_a == NULL) {
        perror("Nenhuma avaliação registrada.");
        return 0;
    }

    if (fscanf(avaliacoes_a, "%d%*c", &n_avaliacoes) != 1) {
        fprintf(stderr, "Erro ao ler o número de avaliações.\n");
        fclose(avaliacoes_a);
        return 0;
    }

    for (int i = 0; i < n_avaliacoes; i++) {
        // Lê a descrição da avaliação
        fgets(avaliacoes[i].avaliacao, TAM_DESC, avaliacoes_a);
        avaliacoes[i].avaliacao[strcspn(avaliacoes[i].avaliacao, "\n")] = '\0';

        // Lê o ID do produto relacionado à avaliação
        if (fscanf(avaliacoes_a, "%d%*c", &avaliacoes[i].id_produto) != 1) {
            fprintf(stderr, "Erro ao ler o ID do produto da avaliação %d\n", i);
            fclose(avaliacoes_a);
            return 0;
        }
    }

    fclose(avaliacoes_a);
    return n_avaliacoes;
}


void EscreverArquivoAvaliacoes(avaliacoes_s *avaliacoes, int n_avaliacoes) {
    FILE* avaliacoes_a = fopen("avaliacoes.txt", "w");

    if (avaliacoes_a == NULL) {
        perror("Erro ao abrir arquivo de avaliações");
        return;
    }

    // Escreve o número de avaliações
    fprintf(avaliacoes_a, "%d\n", n_avaliacoes);

    for (int i = 0; i < n_avaliacoes; i++) {

        fprintf(avaliacoes_a, "%s\n", avaliacoes[i].avaliacao);


        fprintf(avaliacoes_a, "%d\n", avaliacoes[i].id_produto);
    }

    fclose(avaliacoes_a);
}