#pragma once
#include <stdbool.h>
#include <windows.h> // For Sleep() and color functions

#define ROWS 10
#define COLS 20
#define REFRESH_RATE 100        // Refresh every 100ms
#define SPEED_BOOST_DURATION 10 // Speed boost lasts for 10 moves
#define NUM_ENEMIES 3           // Number of enemies
#define MAX_LEVELS 3            // Maximum number of levels

// Color codes
#define COLOR_DEFAULT 7  // White
#define COLOR_WALL 8     // Gray
#define COLOR_PACMAN 14  // Yellow
#define COLOR_DOT 10     // Green
#define COLOR_POWERUP 12 // Red
#define COLOR_ENEMY 13   // Magenta

typedef enum
{
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
} Direction;

typedef struct
{
    bool is_wall;
    bool has_dot;
    bool has_powerup;
    bool has_enemy;
    bool powerup_collected; // New flag to track if power-up has been collected
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
    int x, y;            // Position
    Direction direction; // Current direction
} Enemy;

typedef struct
{
    Cell grid[ROWS][COLS];
    Pacman player;
    Enemy enemies[NUM_ENEMIES]; // Array of enemies
    int enemy_count;
    bool is_running;   // Game state
    int current_level; // Current level number
} GameState;

// Function declarations
void initialize_game(GameState *game);
void draw_board(const GameState *game);
void move_pacman(GameState *game, Direction dir);
void save_game(const GameState *game);
void load_game(GameState *game);
void update_game(GameState *game);
void handle_input(GameState *game);
void auto_move_pacman(GameState *game);
void move_enemies(GameState *game);            // Function to move enemies
void set_color(int color);                     // Function to set text color
void load_level(GameState *game, int level);   // Function to load a specific level
bool is_level_complete(const GameState *game); // Check if all dots are collected
