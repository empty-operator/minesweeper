#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

extern int height, width;
extern int numberOfMines;
extern int cellsLeft;
extern point cursor;
extern cell **field;

void printField(state gameState) {
    system("cls");
    printf(" ╔");
    for (int i = 0; i < width; ++i) printf("═");
    printf("╗\n");
    for (int i = 0; i < height; ++i) {
        printf(" ║");
        for (int j = 0; j < width; ++j) {
            if (i == cursor.y && j == cursor.x) {
                if (!field[i][j].isMine && field[i][j].isOpen) {
                    if (field[i][j].minesCounter) printf(WHITE_BLACK "%d" RESET, field[i][j].minesCounter);
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
                        case 5:
                            printf(BG_GRAY CYAN "%d" RESET, field[i][j].minesCounter);
                            break;
                        default:
                            printf(GRAY_BLACK "%d" RESET, field[i][j].minesCounter);
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
    printf(" ╚");
    for (int i = 0; i < width; ++i) printf("═");
    printf("╝\n");
    printf("%d", cellsLeft);
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
                        if (cursor.x + 1 < width) {
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
                        if (cursor.y + 1 < height) {
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
