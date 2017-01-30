#include <iostream>

const char EMPTY = ' ';
const char WALL = '#';
const char PYTHON = '%';
const int DIM = 6;

char maze[DIM][DIM] = {
    {'%', '%', ' ', '%', ' ', '#'},
    {'%', '%', '#', ' ', '%', ' '},
    {'%', ' ', ' ', '%', ' ', ' '},
    {' ', '#', ' ', '#', '#', ' '},
    {' ', '%', ' ', ' ', ' ', '#'},
    {'#', '#', '#', ' ', ' ', ' '}
};

bool canStepOn(int row, int col) {
    return (row >= 0) && (row < DIM) && (col >= 0) && (col < DIM) && ((maze[row][col] == PYTHON) || (maze[row][col] == EMPTY));
}

bool canExit(int row, int col, int countOfPythonsThatCanKill = 3) {
    if((row == 0) && (col == 0)) {
        return ((countOfPythonsThatCanKill == 0) && (maze[0][0] == EMPTY)) || ((countOfPythonsThatCanKill == 1) && (maze[0][0] == PYTHON));
    }
    const char ORIGINAL_CELL = maze[row][col];
    bool isPossible = false;
    if(ORIGINAL_CELL == PYTHON) {
        if(countOfPythonsThatCanKill == 0) {
            return false;
        } else {
            --countOfPythonsThatCanKill;
        }
    }
    maze[row][col] = WALL;
    if(canStepOn(row + 1, col) && canExit(row + 1, col, countOfPythonsThatCanKill)) {
        isPossible = true;
    }
    if(canStepOn(row, col + 1) && canExit(row, col + 1, countOfPythonsThatCanKill)) {
        isPossible = true;
    }
    if(canStepOn(row - 1, col) && canExit(row - 1, col, countOfPythonsThatCanKill)) {
        isPossible = true;
    }
    if(canStepOn(row, col - 1) && canExit(row, col - 1, countOfPythonsThatCanKill)) {
        isPossible = true;
    }
    maze[row][col] = ORIGINAL_CELL;

    return isPossible;
}

int main() {
    std::cout << canExit(DIM - 1, DIM - 1) << std::endl;

    return 0;
}
