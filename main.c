#include <stdio.h>

int verificar_preenchimento(int casas[]) {
    for(int i = 0; i < 4; i++) {
        if(casas[i] == -1) {
            return 0;
        }
    }
    return 1;
}


int verificar_quarto (int arrinp[], int returndirector) {
    int vecmasks[3];
    for (int i = 0; i < 3; i++) {
        vecmasks[i] = (arrinp[i] ^ arrinp[i+1]);
    }
    int maskfinal = 15 - (vecmasks[0] | vecmasks[1] | vecmasks[2]);

    if (returndirector == 0) {
        if (maskfinal) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return maskfinal;
    }
}


void imprimir_caracteristica_vencedora(int arrinp[]) {
    int maskfinal = verificar_quarto(arrinp, 1);
    int binario[4];
    int copia = arrinp[0];
    for (int i = 3; i >= 0; i--) {
        binario[i] = copia % 2; 
        copia = copia / 2;       
    }
    if (maskfinal >> 3 == 1) {
        // COR
        if (binario[0] == 0) {
            printf("branca\n");
        } else {
            printf("escura\n");
        }
        return;
    } else if (maskfinal >> 2 == 1) {
        // ALTURA
        if (binario[1] == 0) {
            printf("grande\n");
        } else {
            printf("pequena\n");
        }
        return;
    } else if (maskfinal >> 1 == 1) {
        // FORMA
        if (binario[2] == 0) {
            printf("circular\n");
        } else {
            printf("quadrada\n");
        }
        return;
    } else if ((maskfinal & 1) == 1) {
        // OCO
        if (binario[3] == 0) {
            printf("solida\n");
        } else {
            printf("oca\n");
        }
        return;
    }
}

void copiar_array(int arr1[], int arr2[], int size) {
    for(int i = 0; i < size; i++) {
        arr2[i] = arr1[i];
    }
}

int varre_tabuleiro(int tabuleiro[][4], int coordenadas[], int pecas_vencedoras[]) {
        int matriz_coordenadas[4][4];
        int i = 0;
        for(int linha = 0; linha < 4 ; linha++) {
            for(int coluna = 0; coluna < 4; coluna++) {
                matriz_coordenadas[linha][coluna] = i;
                i++;
            }
        }

        //para cada linha
        for(int linha = 0; linha < 4; linha++) {
            int quadra[] = {tabuleiro[linha][0], tabuleiro[linha][1], tabuleiro[linha][2], tabuleiro[linha][3]};
            int coords[] = {matriz_coordenadas[linha][0], matriz_coordenadas[linha][1], matriz_coordenadas[linha][2], matriz_coordenadas[linha][3]};
            if(verificar_preenchimento(quadra) && verificar_quarto(quadra, 0)) {
                copiar_array(quadra, pecas_vencedoras, 4);
                copiar_array(coords, coordenadas, 4);
                return 1;
            }
        }
        //para cada coluna
        for(int coluna = 0; coluna < 4; coluna++) {
            int quadra[] = {tabuleiro[0][coluna], tabuleiro[1][coluna], tabuleiro[2][coluna], tabuleiro[3][coluna]};
            int coords[] = {matriz_coordenadas[0][coluna], matriz_coordenadas[1][coluna], matriz_coordenadas[2][coluna], matriz_coordenadas[3][coluna]};
            if(verificar_preenchimento(quadra) && verificar_quarto(quadra, 0)) {
                copiar_array(quadra, pecas_vencedoras, 4);
                copiar_array(coords, coordenadas, 4);
                return 1;
            }
        }
        //para a diagonal principal
        int diagonal_principal[] = {tabuleiro[0][0], tabuleiro[1][1], tabuleiro[2][2], tabuleiro[3][3]};
        int coords_principal[] = {matriz_coordenadas[0][0], matriz_coordenadas[1][1], matriz_coordenadas[2][2], matriz_coordenadas[3][3]};
            if(verificar_preenchimento(diagonal_principal) && verificar_quarto(diagonal_principal, 0)) {
                copiar_array(diagonal_principal, pecas_vencedoras, 4);
                copiar_array(coords_principal, coordenadas, 4);
                return 1;
            }
        // para a diagonal secundaria
        int diagonal_secundaria[] = {tabuleiro[3][0], tabuleiro[2][1], tabuleiro[1][2], tabuleiro[0][3]};
        int coords_secundaria[] = {matriz_coordenadas[0][3], matriz_coordenadas[1][2], matriz_coordenadas[2][1], matriz_coordenadas[3][0]};
            if(verificar_preenchimento(diagonal_secundaria) && verificar_quarto(diagonal_secundaria, 0)) {
                copiar_array(diagonal_secundaria, pecas_vencedoras, 4);
                copiar_array(coords_secundaria, coordenadas, 4);
                return 1;
            }
            
        return 0;
}


int main(int argc, char *argv[]) {
    // Declaracao e inicializacao do tabuleiro
    int tabuleiro[4][4];
    for(int linha = 0; linha < 4; linha++) {
        for(int coluna = 0; coluna < 4; coluna++) {
            tabuleiro[linha][coluna] = -1;
        }
    }
    // Contador de rodadas
    int semi_rodada = 0;
    // Parametros do Jogo
    int pecas_sequencia[4];
    int coord_sequencia[4];
    // Jogo
    int houver_vencedor = 0;
    while(!houver_vencedor && semi_rodada < 16) {
        unsigned int peca;
        scanf("%X", &peca);
        unsigned int posicao;
        scanf("%X", &posicao);
        // Adequacao no tabuleiro
        tabuleiro[posicao / 4][posicao % 4] = peca;

        // Verificacao de se ha um vencedor
        houver_vencedor = varre_tabuleiro(tabuleiro, coord_sequencia, pecas_sequencia);
        semi_rodada++;
    }
    // Saida do Tabuleiro
    for(int linha = 0; linha < 4; linha++) {
        for(int coluna = 0; coluna < 4; coluna++) {
            (tabuleiro[linha][coluna] == -1) ? printf("-") : printf("%X", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
    // Saida dos outros atributos
    if(houver_vencedor) {
        printf("%d\n", (semi_rodada % 2 == 0) ? 1 : 2);
        for(int i = 0; i < 4; i++) {
            printf("%X", coord_sequencia[i]);
        }
        printf("\n");
        imprimir_caracteristica_vencedora(pecas_sequencia);
    }
    else {
        printf("0");
    }
}