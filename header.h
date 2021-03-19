#ifndef MINESWEEPER_HEADER_H
#define MINESWEEPER_HEADER_H

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

typedef enum {
    DEFAULT,
    DEFEAT,
    WIN
} state;

typedef enum {
    OPEN_CELL,
    SET_FLAG
} action;

typedef struct {
    int x;
    int y;
} point;

typedef struct {
    bool flag;
    bool isOpen;
    bool isMine;
    int minesCounter;
} cell;

void printField(state);
void initField(int);
action readKey(void);
void openEmpty(int, int);

#endif //MINESWEEPER_HEADER_H
