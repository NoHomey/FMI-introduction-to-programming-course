#include <iostream>

const char EMPTY = ' ';
const char WALL = '#';
const char GOLD = '$';
const int DIM = 6;

char maze[DIM][DIM] = {
    {'$', ' ', ' ', '$', ' ', '#'},
    {' ', ' ', '#', ' ', '$', ' '},
    {' ', ' ', ' ', '$', ' ', ' '},
    {' ', '#', ' ', '#', '#', ' '},
    {' ', '$', ' ', ' ', ' ', '#'},
    {'#', '#', '#', ' ', ' ', ' '}
};

bool canStepOn(int row, int col) {
    return (row >= 0) && (row < DIM) && (col >= 0) && (col < DIM) && ((maze[row][col] == GOLD) || (maze[row][col] == EMPTY));
}

bool canPickUpGold(int row, int col, size_t goldToPickUp) {
    if((row == 0) && (col == 0)) {
        if(maze[0][0] == GOLD) {
            --goldToPickUp;
        }
        return goldToPickUp == 0;
    }
    const char ORIGINAL_CELL = maze[row][col];
    bool isPossible = false;
    if(ORIGINAL_CELL == GOLD) {
        --goldToPickUp;
    }
    maze[row][col] = WALL;
    if(canStepOn(row + 1, col) && canPickUpGold(row + 1, col, goldToPickUp)) {
        isPossible = true;
    }
    if(canStepOn(row, col + 1) && canPickUpGold(row, col + 1, goldToPickUp)) {
        isPossible = true;
    }
    if(canStepOn(row - 1, col) && canPickUpGold(row - 1, col, goldToPickUp)) {
        isPossible = true;
    }
    if(canStepOn(row, col - 1) && canPickUpGold(row, col - 1, goldToPickUp)) {
        isPossible = true;
    }
    maze[row][col] = ORIGINAL_CELL;

    return isPossible;
}

int main() {
    std::cout << canPickUpGold(DIM - 1, DIM - 1, 5) << std::endl;

    return 0;
}
