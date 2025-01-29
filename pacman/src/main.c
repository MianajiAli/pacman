#include <stdio.h>
#include <conio.h>  // Windows-specific for getch()
#include "grid.h"
#include "game.h"

int main() {
    Grid gameGrid;
    init_grid(&gameGrid);

    char input;
    while (1) {
        print_grid(&gameGrid);
        printf("\nMove (WASD): ");

        input = _getch(); // Reads input without Enter
        move_pacman(&gameGrid, input);
    }

    return 0;
}
