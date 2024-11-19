#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"








void FavoritaProd(produto_s *produtos, int n_produtos, perfis_s *perfis, int n_perfis){
    int id_produto_escolhido = 0;
    int id_perfil_escolhido = 0;

    printf("digite o id do produto que deseja favoritar: ");
    if (scanf("%d", &id_produto_escolhido) != 1 || id_produto_escolhido < 1 || id_produto_escolhido > n_produtos)
    {
        printf("id de produto inválido.\n");
        return;
    }

    printf("digite o id do perfil: ");
    if (scanf("%d", &id_perfil_escolhido) != 1 || id_perfil_escolhido < 1 || id_perfil_escolhido > n_perfis)
    {
        printf("id de perfil inválido.\n");
        return;
    }

    perfis_s *usuario = &perfis[id_perfil_escolhido - 1];

    for (int i = 0; i < usuario->tam_produtos_Favoritos; i++)
    {
        if (usuario->id_produtos_Favoritos[i] == id_produto_escolhido)
        {
            printf("produto já esta nos favoritos.\n");
            return;
        }
    }

    usuario->tam_produtos_Favoritos++;
    int *nova_lista = RealocaInt(usuario->tam_produtos_Favoritos, usuario->id_produtos_Favoritos);

    if (nova_lista == NULL)
    {
        printf("erro ao realocar memoria.\n");
        return;
    }

    usuario->id_produtos_Favoritos = nova_lista;
    usuario->id_produtos_Favoritos[usuario->tam_produtos_Favoritos - 1] = id_produto_escolhido;

    printf("produto adicionado aos favoritos com sucesso.\n");
}


void ImprimeFavoritos(perfis_s *usuario){
    if (usuario->tam_produtos_Favoritos == 0)
    {
        printf("a lista de favoritos esta vazia.\n");
    }
    else
    {
        printf("produtos favoritos do perfil:\n");
        for (int i = 0; i < usuario->tam_produtos_Favoritos; i++)
        {
            printf("produto id: %d\n", usuario->id_produtos_Favoritos[i]);
        }
    }
}



void DeletaProd(produto_s *produtos, int n_produtos, perfis_s *perfis, int n_perfis){
    int id_perfil_escolhido = 0;
    int id_produto_escolhido = 0;

    printf("digite o id do perfil: ");
    if (scanf("%d", &id_perfil_escolhido) != 1 || id_perfil_escolhido < 1 || id_perfil_escolhido > n_perfis)
    {
        printf("id de perfil inválido.\n");
        return;
    }

    printf("digite o id do produto para ser desfavoritado:  ");
    if (scanf("%d", &id_produto_escolhido) != 1 || id_produto_escolhido < 1 || id_produto_escolhido > n_produtos)
    {
        printf("id de produto invalido.\n");
        return;
    }

    perfis_s *usuario = &perfis[id_perfil_escolhido - 1];

    if (usuario->tam_produtos_Favoritos == 0)
    {
        printf("a lista de favoritos esta vazia.\n");
        return;
    }

    for (int i = 0; i < usuario->tam_produtos_Favoritos; i++)
    {
        if (usuario->id_produtos_Favoritos[i] == id_produto_escolhido)
        {

            for (int j = i + 1; j < usuario->tam_produtos_Favoritos; j++)
            {
                usuario->id_produtos_Favoritos[j - 1] = usuario->id_produtos_Favoritos[j];
            }

            usuario->tam_produtos_Favoritos--;

            if (usuario->tam_produtos_Favoritos == 0)
            {
                free(usuario->id_produtos_Favoritos);
                usuario->id_produtos_Favoritos = NULL;
            }
            else
            {

                int *nova_lista = RealocaInt(usuario->tam_produtos_Favoritos, usuario->id_produtos_Favoritos);

                if (nova_lista == NULL)
                {
                    printf("erro ao realocar memoria.\n");
                    return;
                }

                usuario->id_produtos_Favoritos = nova_lista;
            }

            printf("produto removido dos favoritos com sucesso.\n");

            ImprimeFavoritos(usuario);

            return;
        }
    }

    printf("produto nao encontrado nos favoritos.\n");
}

