#include <stdio.h>
#include <stdbool.h>

// Constantes do jogo
#define TAMANHO 10       // Tamanho do tabuleiro (10x10)
#define TAMANHO_NAVIO 3  // Tamanho fixo dos navios
#define AGUA 0           // Valor que representa água
#define NAVIO 3          // Valor que representa parte de um navio
#define HABILIDADE 5     // Valor que representa a área de efeito das habilidades

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;  // Preenche todas as posições com água
        }
    }
}

// Função para verificar se uma posição está dentro do tabuleiro
bool posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO);
}

// Função para posicionar um navio horizontalmente
bool posicionarHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (!posicaoValida(linha, coluna) || !posicaoValida(linha, coluna + TAMANHO_NAVIO - 1)) {
        return false;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA) {
            return false;
        }
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
    }

    return true;
}

// Função para posicionar um navio verticalmente
bool posicionarVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (!posicaoValida(linha, coluna) || !posicaoValida(linha + TAMANHO_NAVIO - 1, coluna)) {
        return false;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA) {
            return false;
        }
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
    }

    return true;
}

// Função para posicionar um navio diagonalmente na diagonal principal
bool posicionarDiagonalPrincipal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (!posicaoValida(linha, coluna) || !posicaoValida(linha + TAMANHO_NAVIO - 1, coluna + TAMANHO_NAVIO - 1)) {
        return false;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != AGUA) {
            return false;
        }
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
    }

    return true;
}

// Função para posicionar um navio diagonalmente na diagonal secundária
bool posicionarDiagonalSecundaria(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (!posicaoValida(linha, coluna) || !posicaoValida(linha + TAMANHO_NAVIO - 1, coluna - TAMANHO_NAVIO + 1)) {
        return false;
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != AGUA) {
            return false;
        }
    }

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
    }

    return true;
}

// Função para aplicar habilidade Cone no tabuleiro
void aplicarHabilidadeCone(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    int cone[5][5] = {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1}
    };
    
    // Sobrepor a área de efeito do Cone no tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (cone[i][j] == 1) {
                int novaLinha = linha + i - 2;
                int novaColuna = coluna + j - 2;
                if (posicaoValida(novaLinha, novaColuna)) {
                    tabuleiro[novaLinha][novaColuna] = HABILIDADE;
                }
            }
        }
    }
}

// Função para aplicar habilidade Cruz no tabuleiro
void aplicarHabilidadeCruz(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    int cruz[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    // Sobrepor a área de efeito da Cruz no tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (cruz[i][j] == 1) {
                int novaLinha = linha + i - 2;
                int novaColuna = coluna + j - 2;
                if (posicaoValida(novaLinha, novaColuna)) {
                    tabuleiro[novaLinha][novaColuna] = HABILIDADE;
                }
            }
        }
    }
}

// Função para aplicar habilidade Octaedro no tabuleiro
void aplicarHabilidadeOctaedro(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    int octaedro[5][5] = {
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0}
    };

    // Sobrepor a área de efeito do Octaedro no tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (octaedro[i][j] == 1) {
                int novaLinha = linha + i - 2;
                int novaColuna = coluna + j - 2;
                if (posicaoValida(novaLinha, novaColuna)) {
                    tabuleiro[novaLinha][novaColuna] = HABILIDADE;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf(" %d", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" 0");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" 3");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf(" 5");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios (coordenadas fixas)
    bool navio1OK = posicionarHorizontal(tabuleiro, 2, 3);   // Navio horizontal na linha 2, coluna 3
    bool navio2OK = posicionarVertical(tabuleiro, 5, 7);     // Navio vertical na linha 5, coluna 7
    bool navio3OK = posicionarDiagonalPrincipal(tabuleiro, 0, 0);  // Navio diagonal na diagonal principal
    bool navio4OK = posicionarDiagonalSecundaria(tabuleiro, 0, 9); // Navio diagonal na diagonal secundária

    // Verifica se os navios foram posicionados corretamente
    if (!navio1OK || !navio2OK || !navio3OK || !navio4OK) {
        printf("Erro ao posicionar navios! Verifique as coordenadas.\n");
        return 1;
    }

    // Aplica as habilidades no tabuleiro (definir origem de cada habilidade)
    aplicarHabilidadeCone(tabuleiro, 5, 5);    // Habilidade Cone em (5,5)
    aplicarHabilidadeCruz(tabuleiro, 4, 4);    // Habilidade Cruz em (4,4)
    aplicarHabilidadeOctaedro(tabuleiro, 3, 3); // Habilidade Octaedro em (3,3)

    // Exibe o tabuleiro com habilidades
    printf("Tabuleiro de Batalha Naval:\n");
    printf("0 = Agua | 3 = Navio | 5 = Habilidade\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
