#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

extern int height, width;
extern int numberOfMines;
extern int cellsLeft;
extern point cursor;
extern cell **field;

void initField(void) {
    srand(time(NULL));
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            field[i][j].flag = false;
            field[i][j].isOpen = false;
            field[i][j].isMine = false;
            field[i][j].minesCounter = 0;
        }
    for (int i = 0; i < numberOfMines; ++i) {
        int x = rand() % height, y = rand() % width;
        if (!field[x][y].isMine) field[x][y].isMine = true;
        else --i;
    }
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            for (int x = -1; x < 2; ++x)
                for (int y = -1; y < 2; ++y)
                    if (i + x >= 0 && i + x < height && j + y >= 0 && j + y < width)
                        if (field[i + x][j + y].isMine)
                            field[i][j].minesCounter++;
}

void openEmpty(int i, int j) {
    if (i < 0 || i >= height || j < 0 || j >= width || field[i][j].isOpen) return;
    field[i][j].isOpen = true;
    cellsLeft--;
    if (!field[i][j].minesCounter)
        for (int x = -1; x < 2; ++x)
            for (int y = -1; y < 2; ++y)
                openEmpty(i + x, j + y);
}
