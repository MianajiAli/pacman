#include "game.h"
#include <stdio.h>

void set_color(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
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
