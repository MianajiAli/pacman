// game.c
#include "game.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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
                .has_enemy = false,
                .visited = false};
        }
    }

    // Add Pacman
    game->player = (Pacman){
        .x = 1,
        .y = 1,
        .direction = 1,
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

void move_pacman(GameState *game, int dir)
{
    Pacman *p = &game->player;
    p->direction = dir;

    int moves = p->speed_boost > 0 ? 2 : 1;
    while (moves-- > 0)
    {
        int new_x = p->x;
        int new_y = p->y;

        switch (dir)
        {
        case 0:
            new_x--;
            break; // Up
        case 1:
            new_y++;
            break; // Right
        case 2:
            new_x++;
            break; // Down
        case 3:
            new_y--;
            break; // Left
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
                p->speed_boost = 10;
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
}

void load_game(GameState *game)
{
    FILE *f = fopen("save.txt", "rb");
    if (f)
    {
        fread(game, sizeof(GameState), 1, f);
        fclose(f);
    }
}

void update_game(GameState *game)
{
    // Placeholder for future updates (e.g., enemy movement)
}
