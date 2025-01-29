// main.c
#include "game.h"
#include <conio.h>
#include <stdio.h>

int main()
{
    GameState game;

    // Check for saved game
    FILE *f = fopen("save.txt", "r");
    if (f)
    {
        fclose(f);
        printf("Load saved game? (y/n): ");
        if (getchar() == 'y')
            load_game(&game);
        else
            initialize_game(&game);
    }
    else
    {
        initialize_game(&game);
    }

    while (1)
    {
        draw_board(&game);

        if (_kbhit())
        {
            int ch = _getch();
            switch (ch)
            {
            case 'w':
                move_pacman(&game, 0);
                break;
            case 'd':
                move_pacman(&game, 1);
                break;
            case 's':
                move_pacman(&game, 2);
                break;
            case 'a':
                move_pacman(&game, 3);
                break;
            case 'q':
                save_game(&game);
                return 0;
            }
        }

        update_game(&game);  // Update game state (e.g., enemies)
        Sleep(REFRESH_RATE); // Refresh every 100ms
    }

    return 0;
}
