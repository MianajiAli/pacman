#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h> // Include this for _kbhit() and _getch()

void initialize_game(GameState *game)
{
    // Initialize empty board
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            game->grid[i][j] = (Cell){
                .is_wall = (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1),
                .has_dot = !(i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1),
                .has_powerup = false,
                .has_enemy = false};
        }
    }

    // Add Pacman
    game->player = (Pacman){
        .x = 1,
        .y = 1,
        .direction = DIR_RIGHT,
        .lives = 3,
        .score = 0,
        .speed_boost = 0};

    // Add powerup
    game->grid[5][5].has_powerup = true;
}

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
                printf("P ");
            }
            else if (game->grid[i][j].is_wall)
            {
                printf("##");
            }
            else if (game->grid[i][j].has_powerup)
            {
                printf("$ ");
            }
            else if (game->grid[i][j].has_dot)
            {
                printf(". ");
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }

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

        // Wall collision check
        if (!game->grid[new_x][new_y].is_wall)
        {
            p->x = new_x;
            p->y = new_y;

            // Collect items
            Cell *current = &game->grid[p->x][p->y];
            if (current->has_dot)
            {
                p->score += 10;
                current->has_dot = false;
            }
            else if (current->has_powerup)
            {
                p->speed_boost = SPEED_BOOST_DURATION;
                current->has_powerup = false;
            }
        }

        if (p->speed_boost > 0)
            p->speed_boost--;
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

void update_game(GameState *game)
{
    // Placeholder for future updates (e.g., enemy movement)
}

void handle_input(GameState *game)
{
    if (_kbhit())
    {
        int ch = _getch();
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
    }
}

void auto_move_pacman(GameState *game)
{
    // Randomly move Pacman in auto-play mode
    Direction dir = rand() % 4;
    move_pacman(game, dir);
}
