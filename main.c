#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

int height = 0, width = 0;
int numberOfMines = 0;
int cellsLeft = 0;
state gameState = DEFAULT;
point cursor = {0, 0};
cell **field = NULL;

int main() {
    startGame();
    while (gameState == DEFAULT)
        switch (readKey()) {
            case OPEN_CELL:
                if (field[cursor.y][cursor.x].flag) break;
                if (field[cursor.y][cursor.x].isMine) gameState = DEFEAT;
                else openEmpty(cursor.y, cursor.x);
                if (cellsLeft == numberOfMines) gameState = WIN;
                printField(gameState);
                break;
            case SET_FLAG:
                if (field[cursor.y][cursor.x].flag) field[cursor.y][cursor.x].flag = false;
                else field[cursor.y][cursor.x].flag = true;
                printField(gameState);
                break;
        }
    if (gameState == WIN) printf("Ви виграли!\n");
    else printf("Шкода, але ви програли. Успіхів наступного разу!\n");
    for (int i = 0; i < height; i++) free(*(field + i));
    free(field);
    getchar(); getchar();
    return 0;
}
