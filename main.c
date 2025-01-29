#include <stdio.h>
#include <conio.h>  // For _getch() on Windows
#include <stdlib.h> // For system() function
#include <windows.h> // For Sleep function

#define WIDTH 10
#define HEIGHT 10

char map[HEIGHT][WIDTH + 1] = {
    "##########",
    "#P       #",
    "#  ####  #",
    "#  #     #",
    "#  #  ####",
    "#  #     #",
    "#  ####  #",
    "#        #",
    "#        #",
    "##########",
};

int pac_x = 1, pac_y = 1;

void draw_map() {
    system("cls");  // Use "clear" for Linux/Mac
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", map[i]);
    }
}

void move_pacman(char direction) {
    int new_x = pac_x, new_y = pac_y;

    switch (direction) {
        case 'w': new_y--; break;
        case 's': new_y++; break;
        case 'a': new_x--; break;
        case 'd': new_x++; break;
    }

    if (map[new_y][new_x] != '#') { // Prevent moving into walls
        map[pac_y][pac_x] = ' ';
        pac_x = new_x;
        pac_y = new_y;
        map[pac_y][pac_x] = 'P';
    }
}

int main() {
    char input;
    while (1) {
        draw_map();
        if (_kbhit()) { // Check if a key was pressed
            input = _getch(); // Get user input
            if (input == 'q') break;
            move_pacman(input);
        }
        Sleep(200); // Add delay to control movement speed
    }
    return 0;
}
