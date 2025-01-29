// game.c
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h> // For _kbhit() and _getch()

// Function to set text color
void set_color(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to load a specific level
void load_level(GameState *game, int level)
{
    // Define level maps
    char levels[MAX_LEVELS][ROWS][COLS] = {
        // Level 1
        {
            "####################",
            "#..................#",
            "#.###.###.###.###.#",
            "#.#...........#...#",
            "#.###.###.###.###.#",
            "#..................#",
            "#........  ........#",
            "#.#...........#...#",
            "#.###.###.###.###.#",
            "####################"},
        // Level 2
        {
            "####################",
            "#..................#",
            "#.###.###.###.###.#",
            "#.#...#...#...#...#",
            "#.###.###.###.###.#",
            "#..................#",
            "#.###.###.###.###.#",
            "#.#...#...#...#...#",
            "#.###.###.###.###.#",
            "####################"},
        // Level 3
        {
            "####################",
            "#..................#",
            "#.###.###.###.###.#",
            "#.#.#.#.#.#.#.#.#.#",
            "#.###.###.###.###.#",
            "#..................#",
            "#.###.###.###.###.#",
            "#.#.#.#.#.#.#.#.#.#",
            "#.###.###.###.###.#",
            "####################"}};

    // Load the specified level
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            game->grid[i][j] = (Cell){
                .is_wall = (levels[level][i][j] == '#'),
                .has_dot = (levels[level][i][j] == '.'),
                .has_powerup = false,
                .has_enemy = false,
                .powerup_collected = false};
        }
    }

    // Reset Pacman's position
    game->player.x = 1;
    game->player.y = 1;

    // Add powerup
    game->grid[5][5].has_powerup = true;
    game->grid[5][5].powerup_collected = false;

    // Add enemies
    game->enemy_count = NUM_ENEMIES;
    game->enemies[0] = (Enemy){.x = 5, .y = 10, .direction = DIR_LEFT};
    game->enemies[1] = (Enemy){.x = 7, .y = 15, .direction = DIR_UP};
    game->enemies[2] = (Enemy){.x = 3, .y = 5, .direction = DIR_DOWN};

    // Mark enemy positions on the grid
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        game->grid[game->enemies[i].x][game->enemies[i].y].has_enemy = true;
    }

    // Set the current level
    game->current_level = level;
}

// Function to check if all dots are collected
bool is_level_complete(const GameState *game)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (game->grid[i][j].has_dot)
            {
                return false;
            }
        }
    }
    return true;
}

void initialize_game(GameState *game)
{
    // Load the first level
    load_level(game, 0);
}

void update_game(GameState *game)
{
    // Move enemies
    move_enemies(game);

    // Check for collisions between Pacman and enemies
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        if (game->player.x == game->enemies[i].x && game->player.y == game->enemies[i].y)
        {
            printf("Game Over! You were caught by an enemy.\n");
            game->is_running = false;
            return;
        }
    }

    // Check if the level is complete
    if (is_level_complete(game))
    {
        if (game->current_level < MAX_LEVELS - 1)
        {
            // Load the next level
            load_level(game, game->current_level + 1);
            printf("Level %d complete! Moving to level %d...\n", game->current_level, game->current_level + 1);
        }
        else
        {
            // All levels completed
            printf("Congratulations! You completed all levels!\n");
            game->is_running = false;
        }
    }
}

// Rest of the functions remain unchanged...
void draw_board(const GameState *game)
{
    system("cls"); // Clear screen (Windows)

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            const Pacman *p = &game->player;

            if (i == p->x && j == p->y)
            {
                set_color(COLOR_PACMAN); // Yellow for Pacman
                printf("P ");
            }
            else if (game->grid[i][j].has_enemy)
            {
                set_color(COLOR_ENEMY); // Magenta for enemies
                printf("E ");
            }
            else if (game->grid[i][j].is_wall)
            {
                set_color(COLOR_WALL); // Gray for walls
                printf("##");
            }
            else if (game->grid[i][j].has_powerup)
            {
                set_color(COLOR_POWERUP); // Red for power-ups
                printf("$ ");
            }
            else if (game->grid[i][j].has_dot)
            {
                set_color(COLOR_DOT); // Green for dots
                printf(". ");
            }
            else
            {
                set_color(COLOR_DEFAULT); // White for empty spaces
                printf("  ");
            }
        }
        printf("\n");
    }

    // Reset color to default
    set_color(COLOR_DEFAULT);

    printf("\nScore: %d | Speed Boost: %d\n",
           game->player.score,
           game->player.speed_boost);
}

void move_pacman(GameState *game, Direction dir)
{
    Pacman *p = &game->player;
    p->direction = dir;

    int moves = (p->speed_boost > 0) ? 2 : 1; // Double moves during speed boost

    while (moves-- > 0)
    {
        int new_x = p->x;
        int new_y = p->y;

        // Update new position based on direction
        switch (dir)
        {
        case DIR_UP:
            new_x--;
            break;
        case DIR_RIGHT:
            new_y++;
            break;
        case DIR_DOWN:
            new_x++;
            break;
        case DIR_LEFT:
            new_y--;
            break;
        }

        // Wall collision check: Prevent movement through walls
        if (!game->grid[new_x][new_y].is_wall)
        {
            // Cell where Pac-Man will move
            Cell *current = &game->grid[new_x][new_y];

            // Collect dot if available
            if (current->has_dot)
            {
                p->score += 10;
                current->has_dot = false; // Remove dot from the grid
            }

            // Check if there's a power-up and it has not been collected yet
            if (current->has_powerup && !current->powerup_collected)
            {
                // Activate speed boost
                p->speed_boost = SPEED_BOOST_DURATION;
                current->powerup_collected = true;  // Mark power-up as collected
                current->has_powerup = false;       // Remove power-up from the grid
                printf("Speed boost activated!\n"); // Debug message
            }

            // Update Pac-Man's position
            p->x = new_x;
            p->y = new_y;
        }

        // If the speed boost is active, decrease its remaining moves
        if (p->speed_boost > 0)
        {
            p->speed_boost--;
        }
    }
}

void move_enemies(GameState *game)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        Enemy *e = &game->enemies[i];

        // Randomly choose a direction
        Direction dir = rand() % 4;

        int new_x = e->x;
        int new_y = e->y;

        // Update new position based on direction
        switch (dir)
        {
        case DIR_UP:
            new_x--;
            break;
        case DIR_RIGHT:
            new_y++;
            break;
        case DIR_DOWN:
            new_x++;
            break;
        case DIR_LEFT:
            new_y--;
            break;
        }

        // Wall collision check: Prevent movement through walls
        if (!game->grid[new_x][new_y].is_wall)
        {
            // Update enemy position
            game->grid[e->x][e->y].has_enemy = false; // Clear old position
            e->x = new_x;
            e->y = new_y;
            game->grid[e->x][e->y].has_enemy = true; // Mark new position
        }
    }
}

void save_game(const GameState *game)
{
    FILE *f = fopen("save.txt", "wb");
    if (f)
    {
        fwrite(game, sizeof(GameState), 1, f);
        fclose(f);
    }
    else
    {
        printf("Error saving game!\n");
    }
}

void load_game(GameState *game)
{
    FILE *f = fopen("save.txt", "rb");
    if (f)
    {
        fread(game, sizeof(GameState), 1, f);
        fclose(f);
    }
    else
    {
        printf("Error loading game!\n");
    }
}

void handle_input(GameState *game)
{
    if (_kbhit())
    {
        int ch = _getch();

        // Handle the key press
        switch (ch)
        {
        case 'w':
            move_pacman(game, DIR_UP);
            break;
        case 'd':
            move_pacman(game, DIR_RIGHT);
            break;
        case 's':
            move_pacman(game, DIR_DOWN);
            break;
        case 'a':
            move_pacman(game, DIR_LEFT);
            break;
        case 'q':
            save_game(game);
            game->is_running = false;
            break;
        }

        // Clear the input buffer to prevent key press "sticking"
        while (_kbhit())
            _getch();
    }
}

void auto_move_pacman(GameState *game)
{
    // Randomly move Pacman in auto-play mode
    Direction dir = rand() % 4;
    move_pacman(game, dir);
}
