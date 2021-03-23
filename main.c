#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

state gameState = DEFAULT;
int height = 0, width = 0;
int numberOfMines = 0;
int cellsLeft = HEIGHT * WIDTH;
point cursor = {0, 0};
cell **field = NULL;

int main() {
    system("chcp 65001");
    startGame();
    while (gameState == DEFAULT)
        switch (readKey()) {
            case OPEN_CELL:
                if (field[cursor.y][cursor.x].flag) break;
                if (field[cursor.y][cursor.x].isMine) gameState = DEFEAT;
                else openEmpty(cursor.y, cursor.x);
                if (cellsLeft == 10) gameState = WIN;
                printField(gameState);
                break;
            case SET_FLAG:
                if (field[cursor.y][cursor.x].flag) field[cursor.y][cursor.x].flag = false;
                else field[cursor.y][cursor.x].flag = true;
                printField(gameState);
                break;
        }
    if (gameState == WIN) printf("Ви виграли!");
    getchar(); getchar();
    return 0;
}
