#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 7

#define AGUA 0
#define NAVIO 3
#define AREA_DE_EFEITO 5

#define HABILIDADE_DISPARO 1
#define HABILIDADE_MISSIL 2

typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAG_DESC_DIR,
    DIAG_DESC_ESQ  
} Direcao;

void inicializarTabuleiro(int tab[][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tab[][TAMANHO_TABULEIRO]);
int tentarPosicionarNavio(int tab[][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, Direcao dir);

void criarMatrizCone(int matriz[][TAMANHO_HABILIDADE], int tamanho);

void criarMatrizCruz(int matriz[][TAMANHO_HABILIDADE], int tamanho);

void criarMatrizOctaedro(int matriz[][TAMANHO_HABILIDADE], int tamanho);

void aplicarHabilidade(int tab[][TAMANHO_TABULEIRO], int matrizHabilidade[][TAMANHO_HABILIDADE], int origem_linha, int origem_coluna);

int main() {

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    inicializarTabuleiro(tabuleiro);

    printf("Iniciando Batalha Naval (Nivel Avancado)\n");
    printf("Posicionando 4 navios de tamanho %d...\n\n", TAMANHO_NAVIO);

    tentarPosicionarNavio(tabuleiro, 2, 2, TAMANHO_NAVIO, HORIZONTAL);
    tentarPosicionarNavio(tabuleiro, 5, 5, TAMANHO_NAVIO, VERTICAL);
    tentarPosicionarNavio(tabuleiro, 0, 7, TAMANHO_NAVIO, DIAG_DESC_DIR);
    tentarPosicionarNavio(tabuleiro, 7, 9, TAMANHO_NAVIO, DIAG_DESC_ESQ);

    printf("\n === Tabuleiro Final Gerado ===\n");
    exibirTabuleiro(tabuleiro);

    int matrizCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matrizOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarMatrizCone(matrizCone, TAMANHO_HABILIDADE);
    criarMatrizCruz(matrizCruz, TAMANHO_HABILIDADE);
    criarMatrizOctaedro(matrizOctaedro, TAMANHO_HABILIDADE);

    printf("\nAplicando Habilidade no Tabuleiro...\n");

    aplicarHabilidade(tabuleiro, matrizCone, 2, 2);
    aplicarHabilidade(tabuleiro, matrizCruz, 5, 5);
    aplicarHabilidade(tabuleiro, matrizOctaedro, 0, 7);

    printf("\n=== Tabuleiro apos Aplicacao das Habilidades ===\n");
    printf("Legenda: 0=Agua, 5=Area de Efeito, 3=Navio\n");
    exibirTabuleiro(tabuleiro);

    return 0;

}

void inicializarTabuleiro(int tab[][TAMANHO_TABULEIRO]) {
    /* Inicializa todo o tabuleiro com AGUA (0) */
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tab[i][j] = AGUA;
        }
    }
}

void criarMatrizCone(int matriz[][TAMANHO_HABILIDADE], int tamanho) {
    /* Desenha um "cone" apontando para baixo com HABILIDADE_DISPARO, resto MISSIL */
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i >= centro && abs(j - centro) <= (i - centro)) {
                matriz[i][j] = HABILIDADE_DISPARO;
            } else {
                matriz[i][j] = HABILIDADE_MISSIL;
            }
        }
    }
}

void criarMatrizCruz(int matriz[][TAMANHO_HABILIDADE], int tamanho) {
    /* Desenha uma cruz (linha e coluna central) como HABILIDADE_DISPARO */
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = HABILIDADE_DISPARO;
            } else {
                matriz[i][j] = HABILIDADE_MISSIL;
            }
        }
    }
}

void criarMatrizOctaedro(int matriz[][TAMANHO_HABILIDADE], int tamanho) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = HABILIDADE_DISPARO;
            } else {
                matriz[i][j] = HABILIDADE_MISSIL;
            }
        }
    }
}

void aplicarHabilidade(int tab_principal[][TAMANHO_TABULEIRO],
                       int matrizHabilidade[][TAMANHO_HABILIDADE],
                       int origem_linha,
                       int origem_coluna) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (matrizHabilidade[i][j] == HABILIDADE_DISPARO) {
                int offset_linha = i - centro;
                int offset_coluna = j - centro;

                int target_linha = origem_linha + offset_linha;
                int target_coluna = origem_coluna + offset_coluna;

                if (target_linha >= 0 && target_linha < TAMANHO_TABULEIRO &&
                    target_coluna >= 0 && target_coluna < TAMANHO_TABULEIRO) {

                    tab_principal[target_linha][target_coluna] = AREA_DE_EFEITO;
                }
            }
        }
    }
}

void exibirTabuleiro(int tab[][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int tentarPosicionarNavio(int tab[][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, Direcao dir) {
    /* Verifica limites e sobreposicao */
    for (int k = 0; k < tamanho; k++) {
        int nova_linha = linha;
        int nova_coluna = coluna;

        switch (dir) {
        case HORIZONTAL:
            nova_coluna = coluna + k;
            break;
        case VERTICAL:
            nova_linha = linha + k;
            break;
        case DIAG_DESC_DIR:
            nova_linha = linha + k;
            nova_coluna = coluna + k;
            break;
        case DIAG_DESC_ESQ:
            nova_linha = linha + k;
            nova_coluna = coluna - k;
            break;
        }

        if (nova_linha < 0 || nova_linha >= TAMANHO_TABULEIRO ||
            nova_coluna < 0 || nova_coluna >= TAMANHO_TABULEIRO) {
            printf("FALHA (Limites Navio): Navio em (%d, %d) direcao %d sairia dos limites.\n",
                   linha, coluna, dir);
            return 0;
        }

        if (tab[nova_linha][nova_coluna] == NAVIO) {
            printf("FALHA (Sobreposicao Navio): Navio em (%d, %d) direcao %d sobrepoe outro em (%d, %d).\n",
                   linha, coluna, dir, nova_linha, nova_coluna);
            return 0;
        }
    }

    /* Posiciona o navio */
    for (int k = 0; k < tamanho; k++) {
        int nova_linha = linha;
        int nova_coluna = coluna;

        switch (dir) {
        case HORIZONTAL:
            nova_coluna = coluna + k;
            break;
        case VERTICAL:
            nova_linha = linha + k;
            break;
        case DIAG_DESC_DIR:
            nova_linha = linha + k;
            nova_coluna = coluna + k;
            break;
        case DIAG_DESC_ESQ:
            nova_linha = linha + k;
            nova_coluna = coluna - k;
            break;
        }

        tab[nova_linha][nova_coluna] = NAVIO;
    }

    printf("SUCESSO: Navio posicionado em (%d, %d) direcao %d.\n", linha, coluna, dir);
    return 1;
}
    