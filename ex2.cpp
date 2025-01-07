#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 9  // Mida de la graella Sudoku (9x9)

// Funció per llegir la graella Sudoku des de l'entrada
void llegir_sudoku(int graella[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &graella[i][j]);
        }
    }
}

// Funció per comprovar si una fila és vàlida
int comprovar_fila(int graella[N][N], int fila) {
    int vist[10] = {0};  // Taula per marcar els digits de l'1 al 9
    for (int columna = 0; columna < N; ++columna) {
        int num = graella[fila][columna];
        if (num < 1 || num > 9 || vist[num] == 1) {
            printf("Error a la fila %d\n", fila + 1);
            return 0;
        }
        vist[num] = 1;
    }
    return 1;
}

// Funció per comprovar si una columna és vàlida
int comprovar_columna(int graella[N][N], int columna) {
    int vist[10] = {0};  // Taula per marcar els digits de l'1 al 9
    for (int fila = 0; fila < N; ++fila) {
        int num = graella[fila][columna];
        if (num < 1 || num > 9 || vist[num] == 1) {
            printf("Error a la columna %d\n", columna + 1);
            return 0;
        }
        vist[num] = 1;
    }
    return 1;
}

// Funció per comprovar si una regió 3x3 és vàlida
int comprovar_regio(int graella[N][N], int inici_fila, int inici_columna) {
    int vist[10] = {0};  // Taula per marcar els digits de l'1 al 9
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num = graella[inici_fila + i][inici_columna + j];
            if (num < 1 || num > 9 || vist[num] == 1) {
                printf("Error a la regió que comença a (%d, %d)\n", inici_fila + 1, inici_columna + 1);
                return 0;
            }
            vist[num] = 1;
        }
    }
    return 1;
}

// Funció per comprovar si la graella Sudoku és vàlida
int comprovar_sudoku(int graella[N][N]) {
    int es_valid = 1;  // Assume que el sudoku és vàlid per defecte

    // Comprovem les files
    for (int i = 0; i < N; ++i) {
        if (!comprovar_fila(graella, i)) {
            es_valid = 0;
        }
    }

    // Comprovem les columnes
    for (int i = 0; i < N; ++i) {
        if (!comprovar_columna(graella, i)) {
            es_valid = 0;
        }
    }

    // Comprovem les regions 3x3
    for (int i = 0; i < N; i += 3) {
        for (int j = 0; j < N; j += 3) {
            if (!comprovar_regio(graella, i, j)) {
                es_valid = 0;
            }
        }
    }
    // Retorna el resultat final
    return es_valid;
}


int main() {
    int graella[N][N];  // La graella Sudoku

    printf("Introdueix la graella Sudoku (81 nombres, separats per espais o salts de línia):\n");
    
    // Llegim la graella Sudoku des de l'entrada estàndard
    llegir_sudoku(graella);

    //Imprimir la graella Sudoku
    for(int i = 0; i < N; i++){
        printf("|---|---|---|---|---|---|---|---|---|\n");
        for (int j = 0; j < N; ++j) {
            printf("| %d ", graella[i][j]);
        }
        printf("|\n");
    }
    printf("|---|---|---|---|---|---|---|---|---|\n");

    // Comprovem si el Sudoku és vàlid
    if (comprovar_sudoku(graella)) {
        printf("El Sudoku és correcte.\n");
    } else {
        printf("El Sudoku és incorrecte.\n");
    }

    return 0;
}
