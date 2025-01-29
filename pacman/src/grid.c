#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

void init_grid(Grid *g)
{
    char layout[MAX_ROWS][MAX_COLS + 1] = {
        "##############################",
        "#  . . . . . . . . . . . . . #",
        "# . . . . . . . . . . . . . .#",
        "# . ###################### . #",
        "# . . . . . . . . . . . . . .#",
        "# . ###################### . #",
        "# . . . . . . . . . . . . . .#",
        "# . ###################### . #",
        "# . . . . . . . . . . . . . .#",
        "# . ###################### . #",
        "# . . . . . . . . . p . . . .#",
        "# . ###################### . #",
        "# . . . . . . . . . . . . . .#",
        "# . ###################### . #",
        "# . . . . . . . . . . . . . .#",
        "# . ###################### . #",
        "# . . . . . . . . . . . . . .#",
        "##############################"};

    g->score = 0;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            g->grid[i][j].type = layout[i][j];
        }
    }
}

void print_grid(Grid *g)
{
#ifdef _WIN32
    system("cls"); // Windows: Clear screen
#else
    system("clear"); // Linux/macOS: Clear screen
#endif

    // Print the grid without spaces between characters
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            printf("%c", g->grid[i][j].type);
        }
        printf("\n");
    }

    printf("\nScore: %d\n", g->score);
}
