// File: game.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "game.h"

void initializeGame(GameState *game, int newGame)
{
    game->score = 0;
    game->boostCounter = 0;
    game->enemyCount = 2;
    game->computerMode = 0;

    if (newGame)
    {
        game->level = 1;
        // Initialize the maze with walls and dots
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
                {
                    // Borders are walls
                    game->maze[y][x].display = '#';
                    game->maze[y][x].isPassable = 0;
                    game->maze[y][x].hasDot = 0;
                    game->maze[y][x].hasBoost = 0;
                }
                else
                {
                    // Inside is passable and has dots
                    game->maze[y][x].display = '.';
                    game->maze[y][x].isPassable = 1;
                    game->maze[y][x].hasDot = 1;
                    game->maze[y][x].hasBoost = 0;
                }
            }
        }

        // Add some boost items ($)
        game->maze[2][2].display = '$';
        game->maze[2][2].hasBoost = 1;
        game->maze[2][2].hasDot = 0;

        // Initialize Pacman's position
        game->pacman.x = 1;
        game->pacman.y = 1;

        // Initialize enemies
        for (int i = 0; i < game->enemyCount; i++)
        {
            game->enemies[i].pos.x = WIDTH - 2;
            game->enemies[i].pos.y = HEIGHT - 2;
            game->enemies[i].direction = rand() % 4;
        }
    }
}
void drawGame(const GameState *game)
{
    system("cls"); // Clear the console (Windows-specific)
    printf("Score: %d\tLevel: %d\t", game->score, game->level);
    if (game->boostCounter > 0)
        printf("Boost: %d ", game->boostCounter);
    printf("\n");

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == game->pacman.x && y == game->pacman.y)
            {
                printf("C"); // Pacman
            }
            else
            {
                int enemyHere = 0;
                for (int i = 0; i < game->enemyCount; i++)
                {
                    if (game->enemies[i].pos.x == x && game->enemies[i].pos.y == y)
                    {
                        printf("E"); // Enemy
                        enemyHere = 1;
                        break;
                    }
                }
                if (!enemyHere)
                {
                    // Display the cell content
                    if (game->maze[y][x].hasDot)
                    {
                        printf("."); // Dot
                    }
                    else if (game->maze[y][x].hasBoost)
                    {
                        printf("$"); // Boost item
                    }
                    else
                    {
                        printf("%c", game->maze[y][x].display); // Wall or empty space
                    }
                }
            }
        }
        printf("\n");
    }
}
int handleInput(GameState *game, int input)
{
    int dx = 0, dy = 0;
    int moves = game->boostCounter > 0 ? 2 : 1;

    switch (input)
    {
    case 'w':
    case 'W':
        dy = -1;
        break;
    case 's':
    case 'S':
        dy = 1;
        break;
    case 'a':
    case 'A':
        dx = -1;
        break;
    case 'd':
    case 'D':
        dx = 1;
        break;
    case 'c':
        game->computerMode = !game->computerMode;
        break;
    }

    for (int i = 0; i < moves; i++)
    {
        int newX = game->pacman.x + dx;
        int newY = game->pacman.y + dy;

        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT &&
            game->maze[newY][newX].isPassable)
        {
            game->pacman.x = newX;
            game->pacman.y = newY;

            if (game->maze[newY][newX].hasDot)
            {
                game->score += 10;
                game->maze[newY][newX].hasDot = 0;
            }
            if (game->maze[newY][newX].hasBoost)
            {
                game->boostCounter = 10;
                game->maze[newY][newX].hasBoost = 0;
            }
        }
    }
    if (game->boostCounter > 0)
        game->boostCounter--;

    return 1;
}

void moveEnemies(GameState *game)
{
    for (int i = 0; i < game->enemyCount; i++)
    {
        int directions[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
        game->enemies[i].direction = rand() % 4;

        int newX = game->enemies[i].pos.x + directions[game->enemies[i].direction][0];
        int newY = game->enemies[i].pos.y + directions[game->enemies[i].direction][1];

        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT &&
            game->maze[newY][newX].isPassable)
        {
            game->enemies[i].pos.x = newX;
            game->enemies[i].pos.y = newY;
        }
    }
}

int checkCollisions(GameState *game)
{
    for (int i = 0; i < game->enemyCount; i++)
    {
        if (game->pacman.x == game->enemies[i].pos.x &&
            game->pacman.y == game->enemies[i].pos.y)
        {
            printf("\nGAME OVER! Final Score: %d\n", game->score);
            return 1;
        }
    }
    return 0;
}

void saveGame(const GameState *game)
{
    FILE *file = fopen(SAVE_FILE, "wb");
    if (file)
    {
        fwrite(game, sizeof(GameState), 1, file);
        fclose(file);
    }
}

int loadGame(GameState *game)
{
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file)
    {
        fread(game, sizeof(GameState), 1, file);
        fclose(file);
        return 1;
    }
    return 0;
}

void generateRandomMaze(GameState *game)
{
    srand(time(NULL));
    // Maze generation logic here (omitted for brevity)
    // Ensure all areas are accessible
}

void computerMove(GameState *game)
{
    int directions[4] = {'w', 's', 'a', 'd'};
    handleInput(game, directions[rand() % 4]);
}
