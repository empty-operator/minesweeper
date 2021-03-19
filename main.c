#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

int cellsLeft = 100;
point cursor = {0, 0};
cell field[10][10];

int main() {
    system("chcp 65001");
    state gameState = DEFAULT;
    initField(10);
    printField(gameState);
    do {
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
    } while (gameState == DEFAULT);
    if (gameState == WIN) printf("You won!");
    getchar(); getchar();
    return 0;
}
