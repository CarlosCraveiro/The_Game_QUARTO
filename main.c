#include <stdio.h>
//Configurações de administrador
#define ADMIN 1
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
    // Jogo
    int houver_vencedor = 0;
    while(!houver_vencedor) {
        semi_rodada++;
        unsigned int peca = 0;
        scanf("%x", &peca);
        unsigned int posicao = 0;
        scanf("%x", &posicao);
        // Adequação no tabuleiro
        tabuleiro[posicao / 4][posicao % 4] = peca;

        //Verificação de se há um vencedor
        int vitoria = 0;
        //para cada linha
        for(int linha = 0; linha < 4; linha++) {
            int quarto = -1;
            for(int coluna = 0; coluna < 4; coluna++) {
                if(tabuleiro[linha][coluna] != -1) {
                    if(quarto == -1) {
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
        for(int coluna = 0; coluna < 4; coluna++) {
            int quarto = 0;
            for(int linha = 0; linha < 4; linha++) {
                if(tabuleiro[linha][coluna] != -1) {
                    if(quarto == -1) {
                       quarto = tabuleiro[linha][coluna];
                    }
                    else{
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
            houver_vencedor = 1;
        }
    }
    // Saída do Tabuleiro
    for(int linha = 0; linha < 4; linha++) {
        for(int coluna = 0; coluna < 4; coluna++) {
            char vazio = '\0';
            vazio = (tabuleiro[linha][coluna] != -1)? '\0':'-';
            (vazio)? printf("%c", vazio):printf("%x", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
    // Exibição de vencedor caso o modo de ADMIN esteja ligado
    if(ADMIN == 1) {
        printf("O %s VENCEU!!", (semi_rodada % 2 == 0)? "Jogador 1":"Jogador 2");
    }
}
