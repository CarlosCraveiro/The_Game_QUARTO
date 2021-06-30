#include<stdio.h>

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

int caracteristica_vencedora(int arrinp[]) {
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
            printf("branca");
        } else {
            printf("escura");
        }
        return;
    } else if (maskfinal >> 2 == 1) {
        // ALTURA
        if (binario[1] == 0) {
            printf("grande");
        } else {
            printf("pequena");
        }
        return;
    } else if (maskfinal >> 1 == 1) {
        // FORMA
        if (binario[2] == 0) {
            printf("circular");
        } else {
            printf("quadrada");
        }
        return;
    } else if (maskfinal & 1 == 1) {
        // OCO
        if (binario[3] == 0) {
            printf("solida");
        } else {
            printf("oca");
        }
        return;
    }
}

int main (void) {
    int arrayinput[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d", &arrayinput[i]);
    }
    printf("%d\n", verificar_quarto(arrayinput, 0));
    caracteristica_vencedora(arrayinput);
}