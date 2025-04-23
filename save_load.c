#include "game.h"
#include <stdio.h>

void save_game(const GameState *game)
{
    FILE *f = fopen("save.txt", "wb");
    if (f)
    {
        fwrite(game, sizeof(GameState), 1, f);
        fclose(f);
    }
    else
    {
        printf("Error saving game!\n");
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
    else
    {
        printf("Error loading game!\n");
    }
}
