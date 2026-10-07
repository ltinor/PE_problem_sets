#include <bits/stdc++.h>
using namespace std;

// A known full grid
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

void generate_puzzle(int blanks) {
    memcpy(puzzle, full_grid, sizeof(full_grid));
    int removed = 0;
    while (removed < blanks) {
        int r = rand() % 9;
        int c = rand() % 9;
        if (puzzle[r][c] != 0) {
            puzzle[r][c] = 0;
            removed++;
        }
    }
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // We create 10 test cases, each containing 1 puzzle
    // The puzzles have varying difficulty (number of blanks)
    int blanks[10] = {30, 32, 34, 36, 38, 40, 42, 44, 46, 48};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);

        generate_puzzle(blanks[i]);
        fout << "1\n";
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                fout << puzzle[r][c];
            }
            fout << "\n";
        }
        fout.close();
        cout << "Generated " << filename << " with " << blanks[i] << " blanks\n";
    }

    return 0;
}
