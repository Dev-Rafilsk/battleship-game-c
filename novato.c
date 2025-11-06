#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main(void) {

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    printf("Inicializando tabuleiro 10x10 com (0)...\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    printf("Tabuleiro inicializado.\n\n");

    int navio1_linha = 2;
    int navio1_coluna = 3;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio1_linha][navio1_coluna + i] = NAVIO;
    }
    
    int navio2_linha = 5;
    int navio2_coluna = 7;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[navio2_linha + i][navio2_coluna] = NAVIO;
    }

    printf("Tabuleiro com os navios posicionados:\n");

    printf("\n### TABULEIRO FINAL DA BATALHA NAVAL ###\n\n");

    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("--");
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {

        printf("%2d |", i);

        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {

            printf(" %d", tabuleiro[i][j]);

        }

        printf("\n");
    }

    return 0;
}