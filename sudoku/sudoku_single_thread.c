#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define ROW 9
#define COL ROW

void printTable(int table[ROW][COL]){
    printf("Your Sudoku table is: \n");
    for(int i=0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}

bool row_checker(int table[ROW][COL]){
    int n, m, r;
    
    r = 0;

    while (r < ROW)
    {
        printf("Checking Row %d ... \n", r + 1);
        for(int i = 0; i < ROW; i ++){
            n = table[r][i];
            for (int j = i + 1; j < ROW; j++){
                m = table[r][j];
                if(n == m) return false;
                //printf("i:%d j:%d, n=%d m=%d | ", i, j, n, m);
            }
            //puts("\n");
        }
        r++;
    }

    return true;
}

bool col_checker(int table[ROW][COL]){
    int n, m, c;
    
    c = 0;

    while (c < COL)
    {
        printf("Checking Col %d ... \n", c + 1);
        for(int i = 0; i < COL; i ++){
            n = table[i][c];
            for (int j = i + 1; j < ROW; j++){
                m = table[j][c];
                if(n == m) return false;
                //printf("i:%d j:%d, n=%d m=%d | ", i, j, n, m);
            }
            //puts("\n");
        }
        c++;
    }

    return true;
}


bool check_blocks(int sudoku[ROW][COL]) {
    // Array per memorizzare se un numero è già apparso in un blocco
    bool block_check[9];

    // Controllo per ciascuno dei 9 blocchi
    for (int block_row = 0; block_row < 9; block_row += 3) {
        for (int block_col = 0; block_col < 9; block_col += 3) {
            // Inizializza l'array di controllo del blocco
            for (int i = 0; i < 9; i++)
                block_check[i] = false;

            // Scansiona il blocco
            for (int i = block_row; i < block_row + 3; i++) {
                for (int j = block_col; j < block_col + 3; j++) {
                    int num = sudoku[i][j];

                    // Se il numero è già apparso, restituisci falso
                    if (block_check[num - 1])
                        return false;
                    else
                        block_check[num - 1] = true;
                }
            }
        }
    }

    // Se tutti i blocchi sono validi, restituisci vero
    return true;
}

int main(void){

    int valid_sudoku[ROW][COL] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    int invalid_sudoku[ROW][COL] = {
        {2, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {2, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    printTable(valid_sudoku);

    bool row_check = row_checker(valid_sudoku);
    
    if(row_check != true){
        printf("Not all rows are valid! \n");
        return -1;
    }
    else {
        printf("All rows are valid! \n");
    }

    bool col_check = col_checker(valid_sudoku);
    
    if(col_check != true){
        printf("Not all cols are valid! \n");
        return -1;
    }
    else {
        printf("All cols are valid! \n");
    }

    if (check_blocks(valid_sudoku)){
        printf("I blocchi del Sudoku sono validi.\n");
    }
    else{
        printf("I blocchi del Sudoku non sono validi.\n");
    }

    return 0;
}