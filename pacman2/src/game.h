// File: game.h
#ifndef GAME_H
#define GAME_H

#define WIDTH 20
#define HEIGHT 10
#define MAX_ENEMIES 5
#define SAVE_FILE "savegame.dat"

typedef struct
{
    char display;
    int isPassable;
    int hasDot;
    int hasBoost;
} Cell;

typedef struct
{
    int x, y;
} Position;

typedef struct
{
    Position pos;
    int direction;
} Enemy;

typedef struct
{
    Cell maze[HEIGHT][WIDTH];
    Position pacman;
    int score;
    int boostCounter;
    int level;
    int enemyCount;
    Enemy enemies[MAX_ENEMIES];
    int computerMode;
} GameState;

void initializeGame(GameState *game, int newGame);
void drawGame(const GameState *game);
int handleInput(GameState *game, int input);
void moveEnemies(GameState *game);
int checkCollisions(GameState *game);
void saveGame(const GameState *game);
int loadGame(GameState *game);
void generateRandomMaze(GameState *game);
void computerMove(GameState *game);

#endif
