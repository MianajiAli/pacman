#include "game.h"
#include <stdlib.h>

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
