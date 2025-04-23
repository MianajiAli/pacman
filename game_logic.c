

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void load_level(GameState *game, int level)
{
    printf("Debug: Loading level %d...\n", level); // Debug message

    // Construct the file path
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "./levels/map%d.txt", level + 1); // level + 1 to match file names

    // Open the file
    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        printf("Error: Unable to open level file: %s\n", filepath);
        return;
    }

    // Read the grid layout
    char line[COLS + 2]; // +2 for newline and null terminator
    for (int i = 0; i < ROWS; i++)
    {
        if (fgets(line, sizeof(line), file))
        {
            // Remove newline character if present
            line[strcspn(line, "\n")] = '\0';

            // Parse each character in the line
            for (int j = 0; j < COLS; j++)
            {
                game->grid[i][j] = (Cell){
                    .is_wall = (line[j] == '#'),
                    .has_dot = (line[j] == '.'),
                    .has_powerup = (line[j] == '$'),
                    .has_enemy = false,
                    .powerup_collected = false};

                // Set player starting position
                if (line[j] == 'P')
                {
                    game->player.x = i;
                    game->player.y = j;
                }
            }
        }
        else
        {
            printf("Error: Level file is incomplete or improperly formatted.\n");
            fclose(file);
            return;
        }
    }

    // Read enemy positions
    int enemy_index = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "E ", 2) == 0)
        { // Check if the line starts with "E "
            int x, y;
            if (sscanf(line, "E %d %d", &x, &y) == 2)
            { // Parse enemy position
                if (enemy_index < NUM_ENEMIES)
                {
                    game->enemies[enemy_index] = (Enemy){.x = x, .y = y, .direction = DIR_LEFT};
                    game->grid[x][y].has_enemy = true;
                    enemy_index++;
                }
            }
        }
    }

    // Close the file
    fclose(file);

    // Set the current level
    game->current_level = level;

    printf("Debug: Level %d loaded successfully from %s.\n", level, filepath); // Debug message
}
void initialize_game(GameState *game)
{
    printf("Debug: Initializing game...\n"); // Debug message
    load_level(game, 0);                     // Load the first level
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
