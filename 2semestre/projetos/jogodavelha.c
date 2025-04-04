#include <stdio.h>
#include <string.h>

// função para imprimir o tabuleiro
void printtab(char tab[3][3][3], int rodada) {
    printf("\n=== Rodada %d ===\n", rodada + 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tab[rodada][i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// função para verificar vitórias em uma rodada específica
int venceu(char tab[3][3][3], int rodada) {
    // Verifica diagonais
    if (tab[rodada][0][0] == tab[rodada][1][1] && tab[rodada][1][1] == tab[rodada][2][2] && tab[rodada][0][0] != ' ') return 1;
    if (tab[rodada][0][2] == tab[rodada][1][1] && tab[rodada][1][1] == tab[rodada][2][0] && tab[rodada][0][2] != ' ') return 1;

    // Verifica linhas
    for (int i = 0; i < 3; i++) {
        if (tab[rodada][i][0] == tab[rodada][i][1] && tab[rodada][i][1] == tab[rodada][i][2] && tab[rodada][i][0] != ' ') return 1;
    }

    // Verifica colunas
    for (int j = 0; j < 3; j++) {
        if (tab[rodada][0][j] == tab[rodada][1][j] && tab[rodada][1][j] == tab[rodada][2][j] && tab[rodada][0][j] != ' ') return 1;
    }

    return 0; // Sem vencedor
}

// função para verificar empate em uma rodada específica
int deuVelha(char tab[3][3][3], int rodada) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tab[rodada][i][j] == ' ') return 0;
        }
    }
    return 1; // Deu velha
}

// função para verificar se a jogada é válida
int jogadaValida(int jogada, char tab[3][3][3], int rodada, int *linha, int *coluna) {
    *linha = (jogada - 1) / 3;
    *coluna = (jogada - 1) % 3;

    if (jogada < 1 || jogada > 9 || tab[rodada][*linha][*coluna] != ' ') {
        printf("Posição inválida! Tente novamente.\n");
        return 0; // Jogada inválida
    }
    return 1; // Jogada válida
}

// função para esvaziar o tabuleiro
void zerartab(char tab[3][3][3],int rodada){
    for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                tab[rodada][i][j] = ' ';
            }
        }
}
//função oara verificar como o jogador ganhou
int comoganhei(char tab[3][3][3], int rodada){
    // Verifica diagonais
    if (tab[rodada][0][0] == tab[rodada][1][1] && tab[rodada][1][1] == tab[rodada][2][2] && tab[rodada][0][0] != ' ') return 1;
    if (tab[rodada][0][2] == tab[rodada][1][1] && tab[rodada][1][1] == tab[rodada][2][0] && tab[rodada][0][2] != ' ') return 2;
    
    // Verifica linhas
    for (int i = 0; i < 3; i++) {
        if (tab[rodada][i][0] == tab[rodada][i][1] && tab[rodada][i][1] == tab[rodada][i][2] && tab[rodada][i][0] != ' ') return 3;
    }

    // Verifica colunas
    for (int j = 0; j < 3; j++) {
        if (tab[rodada][0][j] == tab[rodada][1][j] && tab[rodada][1][j] == tab[rodada][2][j] && tab[rodada][0][j] != ' ') return 4;
    }
    
}
//-----------------Função principal-----------------

int main() {
    char tab[3][3][3];
    char p1[30], p2[30];
    int vez, jogada, linha, coluna, ganhou, comoganhou;
    int placar_p1 = 0, placar_p2 = 0;

    printf("\n");
    printf("==========================\n");
    printf("      JOGO DA VELHA       \n");
    printf("==========================\n");
    printf("Nome do jogador (X): ");
    scanf("%s", p1);
    printf("Nome do jogador (O): ");
    scanf(" %s", p2);
    printf("Boa sorte, %s (X) e %s (O)!\n", p1, p2);

    // Loop de rodadas
    for (int r = 0; r < 3; r++) {
     
        zerartab(tab,r);

        vez = 0;
        ganhou = 0;

        while (ganhou == 0) {
            printtab(tab, r);

            if (vez == 0) {
                printf("%s (X), escolha uma posicao (1-9): ", p1);
            } else {
                printf("%s (O), escolha uma posicao (1-9): ", p2);
            }
            scanf("%d", &jogada);

            if (!jogadaValida(jogada, tab, r, &linha, &coluna)) {
                continue;
            }

            if (vez == 0) {
                tab[r][linha][coluna] = 'X';
            } else {
                tab[r][linha][coluna] = 'O';
            }

            vez = 1 - vez;
            ganhou = venceu(tab, r);

            if (ganhou == 0 && deuVelha(tab, r)) {
                printtab(tab, r);
                printf("Deu velha! A rodada terminou em empate.\n");
                break;
            }

            if (ganhou != 0) {
                printtab(tab, r);
                if (vez == 1) {
                    printf("JOGADOR %s ganhou a rodada!\n", p1);
                    comoganhou = comoganhei(tab, r);
                    if (comoganhou==1) printf("Ganhou com diagonal primaria\n");
                    if (comoganhou==2) printf("Ganhou com diagonal secundaria\n");
                    if (comoganhou==3) printf("Ganhou com Linha\n");
                    if (comoganhou==4) printf("Ganhou com Coluna\n");
                    placar_p1++;
                } else {
                    printf("JOGADOR %s ganhou a rodada!\n", p2);
                    comoganhou = comoganhei(tab, r);
                    if (comoganhou==1) printf("Ganhou com diagonal primaria\n");
                    if (comoganhou==2) printf("Ganhou com diagonal secundaria\n");
                    if (comoganhou==3) printf("Ganhou com Linha\n");
                    if (comoganhou==4) printf("Ganhou com Coluna\n");
                    placar_p2++;
                }
            }
        }
    }

    printf("\n=== PLACAR FINAL ===\n");
    printf("%s (X): %d vitorias\n", p1, placar_p1);
    printf("%s (O): %d vitorias\n", p2, placar_p2);

    if (placar_p1 > placar_p2) {
        printf("%s venceu o jogo!\n", p1);
    } else if (placar_p2 > placar_p1) {
        printf("%s venceu o jogo!\n", p2);
    } else {
        printf("O jogo terminou em empate!\n");
    }

    return 0;
}