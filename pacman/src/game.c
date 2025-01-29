#include "game.h"
#include <stdio.h>

void move_pacman(Grid *g, char direction) {
    int x = -1, y = -1;

    // Find Pacman
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (g->grid[i][j].type == 'P') {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1) break;
    }

    if (x == -1 || y == -1) return;

    // Calculate new position
    int newX = x, newY = y;
    if (direction == 'w') newX--; // Up
    else if (direction == 's') newX++; // Down
    else if (direction == 'a') newY--; // Left
    else if (direction == 'd') newY++; // Right

    // Prevent moving into walls
    if (g->grid[newX][newY].type == '#') return;

    // If moving onto a dot, increase score
    if (g->grid[newX][newY].type == '.') {
        g->score++;
    }

    // Move Pacman
    g->grid[x][y].type = ' ';  // Clear old position
    g->grid[newX][newY].type = 'P';  // Move Pacman
}
