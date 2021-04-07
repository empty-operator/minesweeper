#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

int height = 0, width = 0;
int numberOfMines = 0;
int cellsLeft = 0;
int minesLeft = 0;
state gameState = DEFAULT;
difficulty gameDifficulty;
point cursor = {0, 0};
cell **field = NULL;

int main() {
    startGame();
    clock_t begin = clock();
    while (gameState == DEFAULT) {
        switch (readKey()) {
            case OPEN_CELL:
                if (field[cursor.y][cursor.x].flag)
                    break;
                if (field[cursor.y][cursor.x].isMine)
                    gameState = DEFEAT;
                else
                    openEmpty(cursor.y, cursor.x);
                if (cellsLeft == numberOfMines)
                    gameState = WIN;
                break;
            case SET_FLAG:
                if (field[cursor.y][cursor.x].flag) {
                    field[cursor.y][cursor.x].flag = false;
                    minesLeft++;
                } else {
                    field[cursor.y][cursor.x].flag = true;
                    minesLeft--;
                }
                break;
        }
        printField(gameState);
    }
    if (gameState == WIN) {
        clock_t end = clock();
        printf("Ви виграли!\n");
        printf("Час: %ld сек\n", (end - begin) / CLOCKS_PER_SEC);
        updateStats((end - begin) / CLOCKS_PER_SEC);
    } else
        printf("Шкода, але ви програли. Успіхів наступного разу!\n");
    for (int i = 0; i < height; i++) free(*(field + i));
    free(field);
    printf("\nНатисніть будь-яку клавішу, щоб вийти...");
    _getch();
    return 0;
}
