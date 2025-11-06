#include <stdio.h>
#include <string.h>
#define TAMANHO_TABULEIRO 10

#define TAMANHO_NAVIO 3

#define AGUA 0
#define NAVIO 3

typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAG_DESC_DIR,
    DIAG_DESC_ESQ  
} Direcao;

void inicializarTabuleiro(int tab[][TAMANHO_TABULEIRO]);

void exibirTabuleiro(int tab[][TAMANHO_TABULEIRO]);
int tentarPosicionarNavio(int tab[][TAMANHO_TABULEIRO], int lin, int col, int tamanho, Direcao dir);



int main() {
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    inicializarTabuleiro(tabuleiro);

    printf("Iniciando Batalha Naval (Nivel Intermediario)\n");
    printf("Posicionando 4 navios de tamanho %d...\n\n", TAMANHO_NAVIO);

    tentarPosicionarNavio(tabuleiro, 1, 4, TAMANHO_NAVIO, HORIZONTAL);

    tentarPosicionarNavio(tabuleiro, 3, 8, TAMANHO_NAVIO, VERTICAL);

    tentarPosicionarNavio(tabuleiro, 0, 0, TAMANHO_NAVIO, DIAG_DESC_DIR);

   tentarPosicionarNavio(tabuleiro, 0, 9, TAMANHO_NAVIO, DIAG_DESC_ESQ);

    
    printf("\n--- Tabuleiro Final Gerado ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

void inicializarTabuleiro(int tab[][TAMANHO_TABULEIRO]) {
    
    memset(tab, AGUA, sizeof(int) * TAMANHO_TABULEIRO * TAMANHO_TABULEIRO);
}

void exibirTabuleiro(int tab[][TAMANHO_TABULEIRO]) {



    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
    
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {

            printf("%d ", tab[i][j]);
        }

        printf("\n");
    }
}

int tentarPosicionarNavio(int tab[][TAMANHO_TABULEIRO], int lin, int col, int tamanho, Direcao dir) {
    for (int k = 0; k < tamanho; k++) {
        int novaLin = lin;
        int novaCol = col;
        switch (dir) {
            case HORIZONTAL:
                novaCol = col + k;
                break;
            case VERTICAL:
                novaLin = lin + k;
                break;
            case DIAG_DESC_DIR:
                novaLin = lin + k;
                novaCol = col + k;
                break;
            case DIAG_DESC_ESQ:
                novaLin = lin + k;
                novaCol = col - k;
                break;
        }

        if (novaLin < 0 || novaLin >= TAMANHO_TABULEIRO ||
            novaCol < 0 || novaCol >= TAMANHO_TABULEIRO)
        {
            printf("FALHA (Limites): Navio em (%d, %d) direcao %d sairia dos limites em (%d, %d).\n",
                   lin, col, dir, novaLin, novaCol);
            return 0;
        }

        if (tab[novaLin][novaCol] == NAVIO) {
            
            printf("FALHA (Sobreposicao): Navio em (%d, %d) direcao %d sobrepoe outro em (%d, %d).\n",
                   lin, col, dir, novaLin, novaCol);
            return 0;
        }
    }

    for (int k = 0; k < tamanho; k++) {
        int novaLin = lin;
        int novaCol = col;

        switch (dir) {
            case HORIZONTAL:
                novaCol = col + k;
                break;
            case VERTICAL:
                novaLin = lin + k;
                break;
            case DIAG_DESC_DIR:
                novaLin = lin + k;
                novaCol = col + k;
                break;
            case DIAG_DESC_ESQ:
                novaLin = lin + k;
                novaCol = col - k;
                break;
        }
        tab[novaLin][novaCol] = NAVIO;
    }

    printf("SUCESSO: Navio de tamanho %d posicionado em (%d, %d) na direcao %d.\n",
           tamanho, lin, col, dir);

    return 1;
}