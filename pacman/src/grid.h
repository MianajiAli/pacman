#ifndef GRID_H
#define GRID_H

#define MAX_ROWS 20
#define MAX_COLS 30

typedef struct {
    char type; // P = Pacman, # = Wall, . = Dot, ' ' = Empty
} Cell;

typedef struct {
    Cell grid[MAX_ROWS][MAX_COLS];
    int score;
} Grid;

void init_grid(Grid *g);
void print_grid(Grid *g);

#endif
