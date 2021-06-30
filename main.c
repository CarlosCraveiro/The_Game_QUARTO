#include <stdio.h>

int verificar_quarto(int quad);

int caracteristica_vencedora(int quadra);

int varre_tabuleiro(int *venceu, int *coordenadas, int tabuleiro) {
    int vitoria = 0;
    int quarto;
        //para cada linha
        for(int linha = 0; linha < 4; linha++) {
            quarto += verificar_quarto(tabuleiro[linha]);
            int quarto = -1;
            for (int coluna = 0; coluna < 4; coluna++) {
                if (tabuleiro[linha][coluna] != -1) {
                    if (quarto == -1) {
                       quarto = tabuleiro[linha][coluna];
                    }
                    else {
                        quarto = ~(quarto ^ tabuleiro[linha][coluna]);
                    }
                }
            }
            if(quarto != 0) {
                vitoria++;
            }
        }
        //para cada coluna
        for (int coluna = 0; coluna < 4; coluna++) {
            int quarto = 0;
            for (int linha = 0; linha < 4; linha++) {
                if(tabuleiro[linha][coluna] != -1) {
                    if (quarto == -1) {
                       quarto = tabuleiro[linha][coluna];
                    }
                    else {
                        quarto = ~(quarto ^ tabuleiro[linha][coluna]);
                    }
                }
                if(quarto != 0) {
                vitoria++;
                }
            }
        }
        //para a diagonal principal
        int quarto = -1;
        for(int i = 0; i < 4; i++) {
            if(tabuleiro[i][i] != -1){
                if(quarto == -1){
                    quarto = tabuleiro[i][i];
                }
                else{
                    quarto = ~(quarto ^ tabuleiro[i][i]);
                }
            }
        }
        if(quarto != 0) {
            vitoria++;
        }
        // para a diagonal secundaria
        quarto = -1;
        for(int i = 0; i > -4; i--) {
            if(quarto == -1) {
                quarto = tabuleiro[i + 3][-i];
            }
            else{
                quarto = ~(quarto ^ tabuleiro[i + 3][-i]);
            }
        }
        if(quarto != 0) {
            vitoria++;
        }
        if(vitoria > 0) {
            venceu = 1;
        }
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
