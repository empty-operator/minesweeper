#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

extern int height, width;
extern int numberOfMines;
extern int cellsLeft;
extern state gameState;
extern cell **field;

void startGame(void) {
    system("chcp 65001");
    printf("Виберіть рівень складності:\n"
           "\t1 - Початківець (10 мін, сітка 9 х 9)\n"
           "\t2 - Аматор (40 мін, сітка 16 х 16)\n"
           "\t3 - Експерт (99 мін, сітка 16 х 30)\n");
    switch (_getch()) {
        case ESCAPE:
            exit(0);
        case ONE:
            height = 9, width = 9, numberOfMines = 10;
            field = (cell **) malloc(height * sizeof(cell *));
            for (int i = 0; i < height; i++) *(field + i) = (cell *) malloc(width * sizeof(cell));
            break;
        case TWO:
            height = 16, width = 16, numberOfMines = 40;
            field = (cell **) malloc(height * sizeof(cell *));
            for (int i = 0; i < height; i++) *(field + i) = (cell *) malloc(width * sizeof(cell));
            break;
        case THREE:
            height = 16, width = 30, numberOfMines = 99;
            field = (cell **) malloc(height * sizeof(cell *));
            for (int i = 0; i < height; i++) *(field + i) = (cell *) malloc(width * sizeof(cell));
            break;
        default:
            break;
    }
    if (field == NULL) exit(0);
    cellsLeft = height * width;
    initField();
    printField(gameState);
}
