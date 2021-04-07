#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "header.h"

extern difficulty gameDifficulty;

void updateStats(clock_t result) {
    printf_s("Ваш час: %d\n", result);
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm, &t);
    record new = {result, {tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900}};
    FILE *f = fopen("stats.dat", "r");
    FILE *fnew = fopen("stats.tmp", "w+b");
    if (f == NULL) {
        f = fopen("stats.dat", "w+b");
        record empty = {-1, {0, 0, 0}};
        for (int i = 0; i < 15; ++i)
            fwrite(&empty, sizeof(record), 1, f);
        rewind(f);
    }
    record all[15];
    fread(all, sizeof(record), 15, f);
    fwrite(all, sizeof(record), 15, fnew);
    rewind(f);
    rewind(fnew);
    switch (gameDifficulty) {
        case BEGINNER:
            fseek(f, 0, SEEK_SET);
            fseek(fnew, 0, SEEK_SET);
            break;
        case INTERMEDIATE:
            fseek(f, 5 * sizeof(record), SEEK_SET);
            fseek(fnew, 5 * sizeof(record), SEEK_SET);
            break;
        case EXPERT:
            fseek(f, 10 * sizeof(record), SEEK_SET);
            fseek(fnew, 10 * sizeof(record), SEEK_SET);
            break;
    }
    record buf;
    bool isInserted = false;
    fread(&buf, sizeof(record), 1, f);
    for (int i = 0; i < 5; ++i) {
        if (!isInserted)
            if (buf.time < new.time && buf.time != -1) {
                fwrite(&buf, sizeof(record), 1, fnew);
                fread(&buf, sizeof(record), 1, f);
            }
            else {
                fwrite(&new, sizeof(record), 1, fnew);
                isInserted = true;
            }
        else {
            fwrite(&buf, sizeof(record), 1, fnew);
            fread(&buf, sizeof(record), 1, f);
        }
    }
    _fcloseall();
    remove("stats.dat");
    rename("stats.tmp", "stats.dat");
}

void printStats(void) {
    FILE *f = fopen("D:\\files\\minesweeper\\stats.dat", "rb");
    record buf;
    printf_s("╔══════════════════╦══════════════════╦══════════════════╗\n");
    printf_s("║ %-27s ║ %-22s ║ %-23s ║\n", "Початківець", "Аматор", "Експерт");
    printf_s("╠═════╦════════════╬═════╦════════════╬═════╦════════════╣\n");
    for (int i = 0; i < 5; fseek(f, ++i * sizeof(record), SEEK_SET)) {
        printf_s("║");
        for (int j = 0; j < 3; ++j) {
            fread(&buf, sizeof(record), 1, f);
            if (buf.time == -1)
                printf_s("     ║            ║", buf.time, buf.date.day, buf.date.month, buf.date.year);
            else
                printf_s(" %3d ║ %2d.%2d.%d ║", buf.time, buf.date.day, buf.date.month, buf.date.year);
            fseek(f, 5 * sizeof(record), SEEK_CUR);
        }
        printf_s("\n");
    }
    printf_s("╚═════╩════════════╩═════╩════════════╩═════╩════════════╝\n");
    fclose(f);
}
