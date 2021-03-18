#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BG_WHITE "\x1b[97;107m"
#define BG_GRAY "\x1b[37;47m"
#define BG_RED "\x1b[97;41m"
#define BLACK "\x1b[97;7m"
#define BLUE "\x1b[34m"
#define GREEN "\x1b[32m"
#define PURPLE "\x1b[35m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define EMPTY ' '
#define OPEN ' '
#define FLAG 'F'
#define MINE '*'
#define ESCAPE 0x1B
#define SLASH 0x5C
#define ENTER 0xD
#define RIGHT 0x4D
#define DOWN 0x50
#define LEFT 0x4B
#define UP 0x48

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    bool flag;
    bool isOpen;
    bool isMine;
    int mines;
} cell;

void printField(bool);
void initField(int);
int readKey(void);
void openEmpty(int, int);

int cellsLeft = 100;
point cursor = {0, 0};
cell field[10][10];

int main() {
    system("chcp 65001");
    initField(10);
    printField(0);
    while (true) {
        if (readKey()) {
            printf("You won!");
            break;
        } else {
            printField(1);
            break;
        }
    }
    getchar(); getchar();
    return 0;
}

void printField(bool isGameOver) {
    system("cls");
    puts(" ╔══════════╗");
    for (int i = 0; i < 10; ++i) {
        printf(" ║");
        for (int j = 0; j < 10; ++j) {
            if (i == cursor.y && j == cursor.x) {
                if (!field[i][j].isMine && field[i][j].isOpen) {
                    if (field[i][j].mines) printf(BLACK "%d" RESET, field[i][j].mines);
                    else printf(BG_WHITE "%c" RESET, OPEN);
                } else {
                    if (isGameOver && field[i][j].isMine) {
                        printf(BG_RED "%c" RESET, MINE);
                        continue;
                    }
                    if (field[i][j].flag) printf(BG_WHITE RED "%c" RESET, FLAG);
                    else printf(BG_WHITE "%c" RESET, EMPTY);
                }
            } else {
                if (!field[i][j].isMine && field[i][j].isOpen) {
                    switch (field[i][j].mines) {
                        case 0:
                            printf(BG_GRAY "%c" RESET, OPEN);
                            break;
                        case 1:
                            printf(BG_GRAY BLUE "%d" RESET, field[i][j].mines);
                            break;
                        case 2:
                            printf(BG_GRAY GREEN "%d" RESET, field[i][j].mines);
                            break;
                        case 3:
                            printf(BG_GRAY RED "%d" RESET, field[i][j].mines);
                            break;
                        case 4:
                            printf(BG_GRAY PURPLE "%d" RESET, field[i][j].mines);
                            break;
                        default:
                            printf(BG_GRAY "%d", field[i][j].mines);
                    }
                } else {
                    if (isGameOver && field[i][j].isMine) {
                        printf("%c", MINE);
                        continue;
                    }
                    if (field[i][j].flag) printf(RED "%c" RESET, FLAG);
                    else printf("%c", EMPTY);
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
            field[i][j].mines = 0;
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
                            field[i][j].mines++;
}

//void checkFlags(int i, int j) {
//    int flagsCounter = 0;
//    for (int x = -1; x < 2; ++x)
//        for (int y = -1; y < 2; ++y)
//            if (field[i + x][j + y].flag)
//                flagsCounter++;
//    if (flagsCounter == field[i][j].mines)
//        for (int x = -1; x < 2; ++x)
//            for (int y = -1; y < 2; ++y)
//                openEmpty(i + x, j + y);
//}

void openEmpty(int i, int j) {
    if (field[i][j].isOpen || i < 0 || i >= 10 || j < 0 || j >= 10) return;
    field[i][j].isOpen = true;
    cellsLeft--;
    if (!field[i][j].mines)
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
                if (field[cursor.y][cursor.x].flag) break;
                if (field[cursor.y][cursor.x].isMine) return 0;
                //checkFlags(cursor.y, cursor.x);
                openEmpty(cursor.y, cursor.x);
                printField(0);
                if (cellsLeft == 10) return 1;
                break;
            case SLASH:
                if (field[cursor.y][cursor.x].flag)
                    field[cursor.y][cursor.x].flag = false;
                else
                    field[cursor.y][cursor.x].flag = true;
                printField(0);
                break;
            case 0xE0:
                switch (_getch()) {
                    case LEFT:
                        if (cursor.x - 1 >= 0) {
                            cursor.x--;
                            printField(0);
                        }
                        break;
                    case RIGHT:
                        if (cursor.x + 1 < 10) {
                            cursor.x++;
                            printField(0);
                        }
                        break;
                    case UP:
                        if (cursor.y - 1 >= 0) {
                            cursor.y--;
                            printField(0);
                        }
                        break;
                    case DOWN:
                        if (cursor.y + 1 < 10) {
                            cursor.y++;
                            printField(0);
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

