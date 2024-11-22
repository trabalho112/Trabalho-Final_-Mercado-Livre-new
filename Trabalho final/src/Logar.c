#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"


void util_removeQuebraLinhaFinal(char dados[]) {
    int tamanho;
    tamanho = strlen(dados);
    if ((tamanho > 0) && (dados[tamanho - 1] == '\n')) {
        dados[tamanho - 1] = '\0';
    }
}

int* RealocaInt(int tamanho, int* vetor){

    vetor = (int*)realloc(vetor, tamanho*sizeof(int));

    return vetor; 
}

char** RealocaChar(int tamanho, char** vetor) {
    vetor = (char**)realloc(vetor, tamanho * sizeof(char*));
    if (vetor == NULL) {
        printf("Erro na realocação de memória para o vetor de avaliações.\n");
        return NULL;
    }

    vetor[tamanho - 1] = (char*)malloc(TAM_DESC * sizeof(char));
    if (vetor[tamanho - 1] == NULL) {
        printf("Erro na alocação de memória para a avaliação.\n");
        return NULL;
    }

    return vetor;
}

perfis_s* Reallocarperfis(int n_perfis, perfis_s* perfis){
    
    perfis = (perfis_s*)realloc(perfis, n_perfis*sizeof(perfis_s));

    return perfis;
}

void CadastrarPerfil(perfis_s* perfis, int n_perfis) {
    int erro, arroba;

    // Configuração inicial do perfil
    perfis[n_perfis-1].tam_produtos_Vendidos = 0;
    perfis[n_perfis-1].id_produtos_Vendidos = NULL;
    perfis[n_perfis-1].tam_produtos_Favoritos = 0;
    perfis[n_perfis-1].id_produtos_Favoritos = NULL;
    perfis[n_perfis-1].indentificador = n_perfis;

    printf("\n--- Cadastro de Novo Perfil ---\n\n");

    // Obter nome do perfil
    printf("Digite o nome do perfil: ");
    fgets(perfis[n_perfis-1].nome, TAM_NOME, stdin);
    perfis[n_perfis-1].nome[strcspn(perfis[n_perfis-1].nome, "\n")] = '\0';

    // Obter email e verificar se é válido e único
    do {
        erro = 0;
        arroba = 0;

        printf("Digite o email: ");
        fgets(perfis[n_perfis-1].email, TAM_MAX_EMAIL, stdin);
        perfis[n_perfis-1].email[strcspn(perfis[n_perfis-1].email, "\n")] = '\0';

        // Verificar se o email já foi utilizado
        for (int i = 1; i < n_perfis; i++) {
            if (strcmp(perfis[n_perfis-1].email, perfis[i-1].email) == 0) {
                erro = 1;
                printf("-- Este email já está em uso. Tente outro.\n\n");
                break;
            }
        }

        // Verificar se o email contém '@'
        for (int i = 0; i <= TAM_MAX_EMAIL && perfis[n_perfis-1].email[i] != '\0'; i++) {
            if (perfis[n_perfis-1].email[i] == '@') {
                arroba = 1;
                break;
            }
        }

        if (!arroba) {
            printf("-- Email invalido. Certifique-se de incluir '@'.\n\n");
        }

    } while (erro == 1 || arroba != 1);

    // Obter e validar ID
    do {
        erro = 1;

        printf("Digite o ID do perfil: ");
        fgets(perfis[n_perfis-1].id, TAM_ID, stdin);
        perfis[n_perfis-1].id[strcspn(perfis[n_perfis-1].id, "\n")] = '\0';

        // Verificar se o ID já foi utilizado
        for (int i = 1; i < n_perfis; i++) {
            if (strcmp(perfis[n_perfis-1].id, perfis[i-1].id) == 0) {
                erro = 0;
                printf("--Este ID ja esta em uso. Tente um ID diferente.\n\n");
                break;
            }
        }
    } while (erro == 0);

    // Obter senha
    printf("Digite a senha do perfil: ");
    fgets(perfis[n_perfis-1].senha, TAM_MAX_SENHA, stdin);
    perfis[n_perfis-1].senha[strcspn(perfis[n_perfis-1].senha, "\n")] = '\0';

    printf("\n--Perfil cadastrado com sucesso! (Enter para continuar)\n");
    scanf("%*c");

}

void ImprimirDados(perfis_s* perfis, int n_perfis){


    // Cabeçalho da tabela com bordas e colunas nomeadas
    printf("+----------------------------------------------------+----------------------------------------------------+----------------------+\n");
    printf("| %-*s | %-*s | %-*s |\n", TAM_NOME, "Nome_perfil", TAM_MAX_EMAIL, "Email", TAM_ID, "ID");
    printf("+----------------------------------------------------+----------------------------------------------------+----------------------+\n");

    // Exibição dos dados de cada perfil
    for (int i = 0; i < n_perfis; i++) {
        printf("| %-*s | %-*s | %-*s |\n", TAM_NOME, perfis[i].nome, TAM_MAX_EMAIL, perfis[i].email, TAM_ID, perfis[i].id);
    }

    // Linha de fechamento da tabela
    printf("+----------------------------------------------------+----------------------------------------------------+----------------------+\n");


}

int LogarComId(perfis_s* perfis, int n_perfis) {
    char ID[TAM_ID];
    char Senha[TAM_MAX_SENHA];

    while (1) {
        printf("\n--- Login com ID ---\n");
        printf("Digite o ID (digite '0' para sair): ");
        fgets(ID, TAM_ID, stdin);
        ID[strcspn(ID, "\n")] = '\0';

        if (ID[0] == '0') {
            return -1;
        }

        for (int i = 0; i < n_perfis; i++) {
            if (strcmp(ID, perfis[i].id) == 0) {
                printf("Digite a senha: ");
                fgets(Senha, TAM_MAX_SENHA, stdin);
                Senha[strcspn(Senha, "\n")] = '\0';

                if (strcmp(Senha, perfis[i].senha) == 0) {
                    return i;
                } else {
                    printf("--Senha incorreta. Tente novamente.\n");
                    break;
                }
            }
        }

        printf("--ID não encontrado ou inválido. Tente novamente.\n");
    }
}

int LogarComEmail(perfis_s* perfis, int n_perfis) {
    char Email[TAM_MAX_EMAIL], Senha[TAM_MAX_SENHA];

    while (1) {
        printf("\n--- Login com Email ---\n");
        printf("Digite o Email (digite '0' para sair): ");
        fgets(Email, TAM_MAX_EMAIL, stdin);
        Email[strcspn(Email, "\n")] = '\0';

        if (Email[0] == '0') {
            return -1;
        }

        for (int i = 0; i < n_perfis; i++) {
            if (strcmp(Email, perfis[i].email) == 0) {
                printf("Digite a senha: ");
                fgets(Senha, TAM_MAX_SENHA, stdin);
                Senha[strcspn(Senha, "\n")] = '\0';

                if (strcmp(Senha, perfis[i].senha) == 0) {
                    return i;
                } else {
                    printf("--Senha incorreta. Tente novamente.\n");
                    break;
                }
            }
        }

        printf("--Email não encontrado ou invalido. Tente novamente.\n");
    }
}

produto_s* Logar(perfis_s *perfis, int n_perfis, int n_produtos, produto_s *produtos, int n_avaliacoes, avaliacoes_s * avaliacoes ) {
    int opcao = 1;
    int n_logado;

    do {
        printf("\n--- Menu de Login ---\n");
        printf("Escolha uma opcao:\n");
        printf("\t1 - Logar com ID\n");
        printf("\t2 - Logar com Email\n");
        printf("\t0 - Nao cadastrar (Sair)\n");
        printf("Digite a opção desejada: ");
        scanf("%d%*c", &opcao);

        switch (opcao) {
            case 1:
                n_logado = LogarComId(perfis, n_perfis);
                if (n_logado == -1) {
                    printf("Ate logo! Volte sempre!\n");
                    return produtos;
                }
                produtos = MenuLogado(perfis, n_perfis, n_logado, n_produtos, produtos, n_avaliacoes, avaliacoes);
                opcao = 0;
                break;

            case 2:
                n_logado = LogarComEmail(perfis, n_perfis);
                if (n_logado == -1) {
                    printf("Ate logo! Volte sempre!\n");
                    return produtos;
                }
                produtos = MenuLogado(perfis, n_perfis, n_logado, n_produtos, produtos, n_avaliacoes, avaliacoes);
                opcao = 0;  
                break;

            case 0:
                printf("Saindo... Ate logo!\n");
                return produtos;

            default:
                printf("--Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return produtos;
}