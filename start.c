#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

extern int height, width;
extern int numberOfMines;
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
            field = malloc(9 * sizeof(cell *));
            for (int i = 0; i < 9; i++) *(field + i) = malloc(9 * sizeof(cell));
            height = 9, width = 9, numberOfMines = 10;
            break;
        case TWO:
            field = malloc(16 * sizeof(cell *));
            for (int i = 0; i < 16; i++) *(field + i) = malloc(9 * sizeof(cell));
            height = 16, width = 16, numberOfMines = 40;
            break;
        case THREE:
            field = malloc(16 * sizeof(cell *));
            for (int i = 0; i < 30; i++) *(field + i) = malloc(9 * sizeof(cell));
            height = 16, width = 30, numberOfMines = 99;
            break;
        default:
            break;
    }
    if (field == NULL) exit(0);
    initField();
    printField(gameState);
};