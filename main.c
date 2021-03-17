#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BG_WHITE "\x1b[30;47m"
#define BG_GRAY "\x1b[90;100m"
#define RESET "\x1b[0m"
#define EMPTY ' '
#define OPEN ' '
#define MINE '*'
#define ESCAPE  0x1B
#define ENTER  0xD
#define RIGHT  0x4D
#define DOWN  0x50
#define LEFT  0x4B
#define UP  0x48

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    bool flag;
    bool isOpen;
    bool isMine;
    int neighbours;
} cell;

void printField(void);
void initField(int);
int readKey(void);
void gameOver(void);
int isFull(void);

point cursor = {0, 0};
cell field[10][10];

int main() {
    system("chcp 65001");
    initField(10);
    printField();
    while (true) {
        if (readKey() == 0) break;
        if (isFull()) break;
    }
    getchar(); getchar();
    return 0;
}

void printField(void) {
    system("cls");
    puts("╔══════════╗");
    for (int i = 0; i < 10; ++i) {
        printf("║");
        for (int j = 0; j < 10; ++j) {
            if (!field[i][j].isMine && field[i][j].isOpen) {
                if (field[i][j].neighbours == 0) {
                    if (i == cursor.y && j == cursor.x) printf(BG_WHITE "%c" RESET, OPEN);
                    else printf(BG_GRAY "%c" RESET, OPEN);
                }
                else {
                    if (i == cursor.y && j == cursor.x) printf(BG_WHITE "%d" RESET, field[i][j].neighbours);
                    else printf("%d", field[i][j].neighbours);
                }
            } else {
//                if (field[i][j].isMine) {
//                    if (i == cursor.y && j == cursor.x) printf(BG_WHITE "%c" RESET, MINE);
//                    else printf("%c", MINE);
//                } else {
//                    if (i == cursor.y && j == cursor.x) printf(BG_WHITE "%c" RESET, EMPTY);
//                    else printf("%c", EMPTY);
//                }
                if (i == cursor.y && j == cursor.x) printf(BG_WHITE "%c" RESET, EMPTY);
                else printf("%c", EMPTY);
            }
        }
        puts("║");
    }
    puts("╚══════════╝");
}

void initField(int minesNumber) {
    srand(time(NULL));
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            field[i][j].isOpen = false;
            field[i][j].isMine = false;
            field[i][j].neighbours = 0;
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
                            field[i][j].neighbours++;
}

void openEmpty(int i, int j) {
    if (field[i][j].isOpen || i < 0 || i >= 10 || j < 0 || j >= 10) return;
    field[i][j].isOpen = true;
    if (field[i][j].neighbours == 0)
        for (int x = -1; x < 2; ++x)
            for (int y = -1; y < 2; ++y)
                openEmpty(i + x, j + y);
}

int readKey(void) {
    while (1) {
        int key = _getch();
        switch (key) {
            case ESCAPE:
                exit(0);
            case ENTER:
                if (field[cursor.y][cursor.x].isMine) return 0;
                //field[cursor.y][cursor.x].isOpen = true;
                openEmpty(cursor.y, cursor.x);
                return 1;
            case 0xE0:
                switch (_getch()) {
                    case LEFT:
                        if (cursor.x - 1 >= 0) {
                            cursor.x--;
                            printField();
                        }
                        break;
                    case RIGHT:
                        if (cursor.x + 1 < 10) {
                            cursor.x++;
                            printField();
                        }
                        break;
                    case UP:
                        if (cursor.y - 1 >= 0) {
                            cursor.y--;
                            printField();
                        }
                        break;
                    case DOWN:
                        if (cursor.y + 1 < 10) {
                            cursor.y++;
                            printField();
                        }
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

int isFull(void) {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if (field[i][j].isOpen == true)
                return 0;
    return 1;
}