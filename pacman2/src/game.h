#pragma once
#include <stdbool.h>
#include <windows.h> // For Sleep()

#define ROWS 10
#define COLS 20
#define REFRESH_RATE 100        // Refresh every 100ms
#define SPEED_BOOST_DURATION 10 // Speed boost lasts for 10 moves

typedef enum
{
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
} Direction;

typedef struct
{
    bool is_wall;     // Is this cell a wall?
    bool has_dot;     // Does it contain a dot?
    bool has_powerup; // Does it contain $?
    bool has_enemy;   // Is there an enemy here?
} Cell;

typedef struct
{
    int x, y;            // Position
    Direction direction; // Current direction
    int lives;
    int score;
    int speed_boost; // Remaining speed boost moves
} Pacman;

typedef struct
{
    Cell grid[ROWS][COLS];
    Pacman player;
    int enemy_count;
    bool is_running; // Game state
} GameState;

// Function declarations
void initialize_game(GameState *game);
void draw_board(const GameState *game);
void move_pacman(GameState *game, Direction dir);
void save_game(const GameState *game);
void load_game(GameState *game);
void update_game(GameState *game);
void handle_input(GameState *game);
void auto_move_pacman(GameState *game); // For auto-play mode
