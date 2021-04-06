#ifndef MINESWEEPER_HEADER_H
#define MINESWEEPER_HEADER_H

#define BG_WHITE "\x1b[97;107m"
#define BG_GRAY "\x1b[37;47m"
#define BG_RED "\x1b[97;41m"
#define WHITE_BLACK "\x1b[97;7m"
#define GRAY_BLACK "\x1b[37;7m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define PURPLE "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

typedef enum {
    EMPTY = ' ',
    OPEN = ' ',
    FLAG = 'F',
    MINE = '*'
} type;

typedef enum {
    ONE = 0x31,
    TWO = 0x32,
    THREE = 0x33,
    ESCAPE = 0x1B,
    SLASH = 0x5C,
    ENTER = 0xD,
    RIGHT = 0x4D,
    DOWN = 0x50,
    LEFT = 0x4B,
    UP = 0x48
} key;

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

void startGame(void);
void initField(void);
void printField(state);
action readKey(void);
void openEmpty(int, int);

#endif //MINESWEEPER_HEADER_H