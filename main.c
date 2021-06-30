#include <stdio.h>


int verificar_preenchimento(int casas[]) {
    for(int i = 0; i < 4; i++) {
        if(casas[i] == '-') {
            return 0;
        }
    }
    return 1;
}


int verificar_quarto(int quadra);



int caracteristica_vencedora(int quadra);



int varre_tabuleiro(int *venceu, int *coordenadas, int tabuleiro[][]) {
        //para cada linha
        for(int linha = 0; linha < 4; linha++) {
            int quadra[] = {tabuleiro[linha][0], tabuleiro[linha][1], tabuleiro[linha][2], tabuleiro[linha][3]};
            unsigned int quadra_preenchida = verificar_preenchimento(quadra);
            if(quadra_preenchida) {
                //AQUI FAZER A VERIFICAÇÃO DE SE A QUADRA É UM QUARTO
            }
        }
        //para cada coluna
        for (int coluna = 0; coluna < 4; coluna++) {
            int quadra[] = {[0][coluna], [1][coluna], [2][coluna], [3][coluna]};
            unsigned int quadra_preenchida = verificar_preenchimento(quadra);
            if(quadra_preenchida) {
                //AQUI FAZER A VERIFICAÇÃO DE SE A QUADRA É UM QUARTO]
            }
        }
        //para a diagonal principal
        int diagonal_principal[] = {tabuleiro[0][0], tabuleiro[1][1], tabuleiro[2][2], tabuleiro[3][3]};
            unsigned int diag_p_preechida = verificar_preenchimento(diagonal_principal);
            if(diag_p_preechida) {
                //AQUI FAZER A VERIFICAÇÃO DE SE A QUADRA É UM QUARTO
            }
        // para a diagonal secundaria
        int diagonal_secundaria[] = {tabuleiro[3][0], tabuleiro[2][1], tabuleiro[1][2], tabuleiro[0][3]};
            unsigned int diag_s_preechida = verificar_preenchimento(diagonal_secundaria);
            if(diag_s_preechida) {
                //AQUI FAZER A VERIFICAÇÃO DE SE A QUADRA É UM QUARTO
            }
        return {-1, -1, -1, -1};
}


int main(int argc, char *argv[]) {
    // Declaração e inicialização do tabuleiro
    int tabuleiro[4][4];
    for(int linha = 0; linha < 4; linha++) {
        for(int coluna = 0; coluna < 4; coluna++) {
            tabuleiro[linha][coluna] = -1;
        }
    }
    // Contador de rodadas
    int semi_rodada = 0;
    // Parametros do Jogo
    int pecas_sequencia[3];
    int coord_sequencia[3];
    char caracteristica[10];
    // Jogo
    int *houver_vencedor = 0;
    while(!houver_vencedor && semi_rodada < 16) {
        semi_rodada++;
        unsigned int peca;
        scanf("%X", &peca);
        unsigned int posicao;
        scanf("%X", &posicao);
        // Adequação no tabuleiro
        tabuleiro[posicao / 4][posicao % 4] = peca;

        // Verificação de se há um vencedor
        pecas_sequencia = varre_tabuleiro(&houver_vencedor, &coord_sequencia, tabuleiro);

        if(houver_vencedor) {
            // Identifica a caracteristica
            caracteristica = caracteristica_vencedora(pecas_sequencia);
        }
    }
    // Saída do Tabuleiro
    for(int linha = 0; linha < 4; linha++) {
        for(int coluna = 0; coluna < 4; coluna++) {
            char vazio = '\0';
            vazio = (tabuleiro[linha][coluna] != -1)? '\0': '-';
            (vazio)? printf("%c", vazio) : printf("%X", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
    // Saída dos outros atributos
    if(*houver_vencedor) {
        printf("%s\n", (semi_rodada % 2 == 0) ? "1" : "2");
        for(int i = 0; i < 4; i++) {
            printf("%X", coord_sequencia[i]);
        }
        printf("\n");
        printf("%s", caracteristica);
    }
    else {
        printf("0");
    }
}
