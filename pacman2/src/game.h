// game.h
#pragma once
#include <stdbool.h>
#include <windows.h> // For Sleep()

#define ROWS 10
#define COLS 20
#define REFRESH_RATE 100 // Refresh every 100ms

typedef struct
{
    bool is_wall;     // Is this cell a wall?
    bool has_dot;     // Does it contain a dot?
    bool has_powerup; // Does it contain $?
    bool has_enemy;   // Is there an enemy here?
    bool visited;     // For maze generation checks
} Cell;

typedef struct
{
    int x, y;      // Position
    int direction; // 0-3 (up, right, down, left)
    int lives;
    int score;
    int speed_boost; // Remaining speed boost moves
} Pacman;

typedef struct
{
    Cell grid[ROWS][COLS];
    Pacman player;
    int enemy_count;
} GameState;

// Function declarations
void initialize_game(GameState *game);
void draw_board(const GameState *game);
void move_pacman(GameState *game, int dir);
void save_game(const GameState *game);
void load_game(GameState *game);
void update_game(GameState *game);
