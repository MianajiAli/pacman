#include "game.h"
#include <conio.h>
#include <stdio.h>
#include <time.h>

int main()
{
    GameState game;
    game.is_running = true;
    game.computer_mode = false; // Initialize computer mode as disabled

    // Seed the random number generator
    srand(time(NULL));

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

        // If computer mode is enabled, auto-move Pac-Man every second
        if (game.computer_mode)
        {
            auto_move_pacman(&game);
            Sleep(1000); // Wait for 1 second
        }

        update_game(&game);
        Sleep(REFRESH_RATE); // Control game speed
    }

    return 0;
}
