#ifndef ImagemH
#define ImagemH


// ----------------------------------------------------------------------------------------------------------------------------
// In�cio do c�digo fornecido pelo professor
// N�o adicione ou remova nada.

// Se estiver no Windows e n�o conseguir ver a imagem colorida, pode ser que seu terminal n�o suporte Ascii Escape Colors.
// Para habilit�-la, execute o comando abaixo no terminal com permiss�o de Administrador.
// Ap�s executado, o terminado deve ser fechado e aberto novamente para ter o suporte �s cores habilitado.
// Comando:
// reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../include/Logar.h"     // Inclui primeiro Logar.h, que define produto_s e perfis_s
#include "../include/Produtos.h"  // Depois Produtos.h, que depende de produto_s e perfis_s
#include "../include/Menu.h"
#include "../include/Imagens.h"


/// Estrutura que representa uma imagem em Ascii



// Tamanho do buffer para cada linha da imagem
#define BUFFER_TAMANHO  50000

// Tamanho m�ximo da linha de comando
#define LINHA_COMANDO   10000

// Limiar inferior que considera o download com sucesso
#define LIMIAR_INFERIOR_TAMANHO_IMAGEM  500

// Nome do execut�vel da ferramenta de download e convers�o da imagem
#ifdef __unix__ 
#define FERRAMENTA_IMAGEM   "ascii-image-converter.bin"
#else
#define FERRAMENTA_IMAGEM   "ascii-image-converter.exe"
#endif

// Nome do arquivo de sa�da tempor�rio da imagem
#define ARQUIVO_IMAGEM_TMP  "ascii_art.txt"

/**
 *  \brief Fun��o que carrega uma imagem informada na URL.
 *  
 *  \param [in] colorido Define se a imagem ser� colorida.
 *  \param [in] largura Define a largura da imagem gerada.
 *  \return Endere�o da estrutura com a imagem. 
 *          Caso a imagem n�o tenha sido carregada corretamente, a fun��o
 *          retornar� NULL.
 */
asciiImg_t * insta_carregaImagem(char url[], bool colorido, int largura);

/**
 *  \brief Fun��o que imprime uma Imagem ASCII.
 *  
 *  \param [in] img Endere�o da estrutura com os dados da imagem.
 */
void insta_imprimeImagem(asciiImg_t * img);

/**
 *  \brief Fun��o que libera a mem�ria alocada por uma imagem.
 *  
 *  \param [in] img Endere�o da estrutura com os dados da imagem a ser liberada.
 */
void insta_liberaImagem(asciiImg_t * img);

asciiImg_t ** ReallocarImagem(asciiImg_t ** imagem,int quant_imagens);

// ----------------------------------------------------------------------------------------------------------------------------


/* Inclus�es */

/* Erros */

// Constante que associa o c�digo de erro 0 a execu��o esperada.
#define SUCESSO 0

// Falha ao carregar a imagem fornecida
#define ERRO_CARREGAR_IMAGEM 1

/* Constantes */

// N�mero de colunas da imagem
#define IMAGEM_NUMERO_COLUNAS     120

// Defini��o de imagem colorida
#define IMAGEM_COLORIDA           true
// Defini��o de imagem preto/branco
#define IMAGEM_PRETO_BRANCO      false
// Defini��o de imagem utilizada
#define MODO_IMAGEM               IMAGEM_COLORIDA


#endif