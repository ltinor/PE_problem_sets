#include<bits/stdc++.h>
using namespace std;

// A complete valid Sudoku grid template
int full_grid[9][9] = {
    {5,3,4,6,7,8,9,1,2},
    {6,7,2,1,9,5,3,4,8},
    {1,9,8,3,4,2,5,6,7},
    {8,5,9,7,6,1,4,2,3},
    {4,2,6,8,5,3,7,9,1},
    {7,1,3,9,2,4,8,5,6},
    {9,6,1,5,3,7,2,8,4},
    {2,8,7,4,1,9,6,3,5},
    {3,4,5,2,8,6,1,7,9}
};

int puzzle[9][9];

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int blanks;
    if (mode == "small") {
        blanks = rand() % 10 + 30; // 30-39 blanks (easy)
    } else {
        blanks = rand() % 15 + 45; // 45-59 blanks (harder)
    }

    // Start with full grid
    memcpy(puzzle, full_grid, sizeof(full_grid));

    // Remove random cells
    int removed = 0;
    while (removed < blanks) {
        int r = rand() % 9;
        int c = rand() % 9;
        if (puzzle[r][c] != 0) {
            puzzle[r][c] = 0;
            removed++;
        }
    }

    // Output: N=1, then the grid
    cout << "1\n";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << puzzle[i][j];
        }
        cout << "\n";
    }

    return 0;
}
