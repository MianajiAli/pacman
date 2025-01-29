#include "game.h"
#include <conio.h>
#include <stdio.h>

int main()
{
    GameState game;
    game.is_running = true;

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

    // Main game loop
    while (game.is_running)
    {
        draw_board(&game);
        handle_input(&game);
        update_game(&game);
        Sleep(REFRESH_RATE); // Control game speed
    }

    return 0;
}
