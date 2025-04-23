#include "game.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

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
        case 'c': // Toggle computer mode
            game->computer_mode = !game->computer_mode;
            printf("Computer mode %s\n", game->computer_mode ? "enabled" : "disabled");
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
    // Randomly choose a direction
    Direction dir = rand() % 4;

    // Move Pac-Man in the chosen direction
    move_pacman(game, dir);

    // Print debug message
    printf("Auto-moving Pac-Man in direction: %d\n", dir);
}
