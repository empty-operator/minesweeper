#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int neighbours;
    bool isMine;
} cell;

void printField(void);
void initField(int);

cell field[10][10];

int main() {
    system("chcp 65001");
    initField(10);
    printField();
    getchar(); getchar();
    return 0;
}

void printField(void) {
    puts("╔══════════╗");
    for (int i = 0; i < 10; ++i) {
        printf("║");
        for (int j = 0; j < 10; ++j) {
            if (!field[i][j].isMine) {
                if (field[i][j].neighbours == 0) putchar(' ');
                else printf("%d", field[i][j].neighbours);
            } else putchar(' ');
        }
        puts("║");
    }
    puts("╚══════════╝");
}

void initField(int minesNumber) {
    srand(time(NULL));
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
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