#include "robot_grid.h"
#include <stdio.h> // Included for potential debugging if needed

// Define the grid (cost matrix)
const int GRID[N_ROWS][M_COLS] = {
    {12, 3, 4, 13, 5},
    {11, 21, 2, 14, 16},
    {7, 8, 9, 15, 0},
    {10, 17, 20, 19, 1},
    {18, 22, 30, 25, 6}
};

//checks if cell is within boundaries
static int isValid(int row, int col) {
    return (row >= 0 && row < N_ROWS && col >= 0 && col < M_COLS);
}

Cell getNextCell(Cell current) {
    // Check if the current cell is the last cell (bottom-right)
    if (current.row == N_ROWS - 1 && current.col == M_COLS - 1) {
        return (Cell){-1, -1}; // Return the specified termination location
    }

    // Coordinates for the possible neighbors
    int right_row = current.row;
    int right_col = current.col + 1;
    int down_row = current.row + 1;
    int down_col = current.col;

    // Check if neighbors exist
    int has_right = isValid(right_row, right_col);
    int has_down = isValid(down_row, down_col);

    // Case 1: Only Right exists
    if (has_right && !has_down) {
        return (Cell){right_row, right_col};
    } 
    // Case 2: Only Down exists
    else if (!has_right && has_down) {
        return (Cell){down_row, down_col};
    } 
    // Case 3: Both exist (must compare costs)
    else if (has_right && has_down) {
        int cost_right = GRID[right_row][right_col];
        int cost_down = GRID[down_row][down_col];

        // Two neighbors will always have different values according to the prompt
        if (cost_right < cost_down) {
            return (Cell){right_row, right_col};
        } else { // cost_down < cost_right
            return (Cell){down_row, down_col};
        }
    }

    // Should not not be reached unless current is the last cell,
    // which is handled at the start.
    return (Cell){-1, -1}; 
}

int sumPath(Cell current) {
    int total_cost = 0;
    Cell next = current;

    // The loop continues as long as the next cell is valid (not {-1, -1})
    while (next.row != -1) {
        // Add the cost of the current cell to the total
        total_cost += GRID[next.row][next.col];

        // Move to the next cell determined by the greedy choice
        next = getNextCell(next);
    }

    return total_cost;
}
