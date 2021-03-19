#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

extern int cellsLeft;
extern point cursor;
extern cell field[10][10];

void printField(state gameState) {
    system("cls");
    puts(" ╔══════════╗");
    for (int i = 0; i < 10; ++i) {
        printf(" ║");
        for (int j = 0; j < 10; ++j) {
            if (i == cursor.y && j == cursor.x) {
                if (!field[i][j].isMine && field[i][j].isOpen) {
                    if (field[i][j].minesCounter) printf(BLACK "%d" RESET, field[i][j].minesCounter);
                    else printf(BG_WHITE "%c" RESET, OPEN);
                } else {
                    switch (gameState) {
                        case DEFEAT:
                            if (field[i][j].flag) printf(BG_WHITE RED "%c" RESET, FLAG);
                            else if (field[i][j].isMine) printf(BG_RED "%c" RESET, MINE);
                            else printf(BG_WHITE "%c" RESET, EMPTY);
                            break;
                        case DEFAULT:
                            if (field[i][j].flag) printf(BG_WHITE RED "%c" RESET, FLAG);
                            else printf(BG_WHITE "%c" RESET, EMPTY);
                            break;
                        case WIN:
                            break;
                    }
                }
            } else {
                if (!field[i][j].isMine && field[i][j].isOpen) {
                    switch (field[i][j].minesCounter) {
                        case 0:
                            printf(BG_GRAY "%c" RESET, OPEN);
                            break;
                        case 1:
                            printf(BG_GRAY BLUE "%d" RESET, field[i][j].minesCounter);
                            break;
                        case 2:
                            printf(BG_GRAY GREEN "%d" RESET, field[i][j].minesCounter);
                            break;
                        case 3:
                            printf(BG_GRAY RED "%d" RESET, field[i][j].minesCounter);
                            break;
                        case 4:
                            printf(BG_GRAY PURPLE "%d" RESET, field[i][j].minesCounter);
                            break;
                        default:
                            printf(BG_GRAY "%d", field[i][j].minesCounter);
                    }
                } else {
                    switch (gameState) {
                        case DEFEAT:
                            if (field[i][j].flag) printf(RED "%c" RESET, FLAG);
                            else if (field[i][j].isMine) printf("%c", MINE);
                            else printf("%c", EMPTY);
                            break;
                        case DEFAULT:
                            if (field[i][j].flag) printf(RED "%c" RESET, FLAG);
                            else printf("%c", EMPTY);
                            break;
                        case WIN:
                            if (field[i][j].isMine || field[i][j].flag) printf(RED "%c" RESET, FLAG);
                            else printf("%c", EMPTY);
                            break;
                    }
                }
            }
        }
        puts("║");
    }
    puts(" ╚══════════╝");
    printf("%d", cellsLeft);
}

void initField(int minesNumber) {
    srand(time(NULL));
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            field[i][j].flag = false;
            field[i][j].isOpen = false;
            field[i][j].isMine = false;
            field[i][j].minesCounter = 0;
        }
    for (int i = 0; i < minesNumber; ++i) {
        int x = rand() % 10, y = rand() % 10;
        if (!field[x][y].isMine) field[x][y].isMine = true;
        else i--;
    }
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            for (int x = -1; x < 2; ++x)
                for (int y = -1; y < 2; ++y)
                    if (i + x >= 0 && i + x < 10 && j + y >= 0 && j + y < 10)
                        if (field[i + x][j + y].isMine)
                            field[i][j].minesCounter++;
}

void openEmpty(int i, int j) {
    if (field[i][j].isOpen || i < 0 || i >= 10 || j < 0 || j >= 10) return;
    field[i][j].isOpen = true;
    cellsLeft--;
    if (!field[i][j].minesCounter)
        for (int x = -1; x < 2; ++x)
            for (int y = -1; y < 2; ++y)
                openEmpty(i + x, j + y);
}

int readKey(void) {
    while (true) {
        int key = _getch();
        switch (key) {
            case ESCAPE:
                exit(0);
            case ENTER:
                return OPEN_CELL;
            case SLASH:
                return SET_FLAG;
            case 0xE0:
                switch (_getch()) {
                    case LEFT:
                        if (cursor.x - 1 >= 0) {
                            cursor.x--;
                            printField(DEFAULT);
                        }
                        break;
                    case RIGHT:
                        if (cursor.x + 1 < 10) {
                            cursor.x++;
                            printField(DEFAULT);
                        }
                        break;
                    case UP:
                        if (cursor.y - 1 >= 0) {
                            cursor.y--;
                            printField(DEFAULT);
                        }
                        break;
                    case DOWN:
                        if (cursor.y + 1 < 10) {
                            cursor.y++;
                            printField(DEFAULT);
                        }
                        break;
                }
            default:
                break;
        }
    }
}