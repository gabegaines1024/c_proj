#ifndef ROBOT_GRID_H
#define ROBOT_GRID_H

#define N_ROWS 5
#define M_COLS 5

extern const int GRID[N_ROWS][M_COLS];

typedef struct {
    int row;
    int col;
} Cell;
Cell getNextCell(Cell current);

int sumPath(Cell current);

#endif
