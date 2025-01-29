// File: main.c
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "game.h"

int main()
{
    GameState game;
    int input;
    int gameRunning = 1;
    clock_t lastMove = 0;
    FILE *file;

    // Check for saved game
    if ((file = fopen(SAVE_FILE, "r")))
    {
        fclose(file);
        printf("Saved game found. Load? (y/n): ");
        input = getchar();
        initializeGame(&game, (input != 'y' && input != 'Y'));
        if (input == 'y' || input == 'Y')
            loadGame(&game);
    }
    else
    {
        initializeGame(&game, 1);
    }

    while (gameRunning)
    {
        if (game.computerMode && clock() - lastMove > CLOCKS_PER_SEC)
        {
            computerMove(&game);
            lastMove = clock();
        }

        if (_kbhit())
        {
            input = _getch();
            if (input == 27)
            { // ESC key
                printf("\nSave and quit? (y/n): ");
                if (_getch() == 'y')
                {
                    saveGame(&game);
                    gameRunning = 0;
                }
                continue;
            }
            gameRunning = handleInput(&game, input);
        }

        moveEnemies(&game);
        gameRunning = !checkCollisions(&game);
        drawGame(&game);
        Sleep(200);
    }

    return 0;
}
