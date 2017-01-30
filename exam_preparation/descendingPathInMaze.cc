#include <iostream>

int maze[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 0}
};

void markVisited(int row, int col) {
    maze[row][col] = -1;
}

bool canStepOn(int row, int col) {
    return (row >= 0) && (row < 4) && (col >= 0) && (col < 4) && (maze[row][col] == 0);
}

bool existsDescendingPathInMaze(int fromRow, int fromCol, int toRow, int toCol) {
    if((fromRow == toRow) && (fromCol == toCol)) {
        return true;
    }
    markVisited(fromRow, fromCol);
    if(canStepOn(fromRow + 1, fromCol) && existsDescendingPathInMaze(fromRow + 1, fromCol, toRow, toCol)) {
        return true;
    }
    if(canStepOn(fromRow, fromCol + 1) && existsDescendingPathInMaze(fromRow, fromCol + 1, toRow, toCol)) {
        return true;
    }

    return false;
}

int main() {
    std::cout << existsDescendingPathInMaze(2, 0, 3, 3) << std::endl;
    std::cout << existsDescendingPathInMaze(2, 3, 0, 0) << std::endl;

    return 0;
}
