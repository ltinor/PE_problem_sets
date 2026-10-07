#include<bits/stdc++.h>
using namespace std;

int grid[9][9];
int row_mask[9], col_mask[9], box_mask[3][3];
bool solved;

inline int get_candidates(int r, int c) {
    return 0x1FF & ~(row_mask[r] | col_mask[c] | box_mask[r/3][c/3]);
}

void set_cell(int r, int c, int d) {
    int bit = 1 << (d-1);
    row_mask[r] |= bit;
    col_mask[c] |= bit;
    box_mask[r/3][c/3] |= bit;
    grid[r][c] = d;
}

void clear_cell(int r, int c, int d) {
    int bit = 1 << (d-1);
    row_mask[r] &= ~bit;
    col_mask[c] &= ~bit;
    box_mask[r/3][c/3] &= ~bit;
    grid[r][c] = 0;
}

bool dfs() {
    int best_r = -1, best_c = -1, best_cnt = 10;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (grid[r][c] == 0) {
                int cand = get_candidates(r, c);
                int cnt = __builtin_popcount(cand);
                if (cnt == 0) return false;
                if (cnt < best_cnt) {
                    best_cnt = cnt;
                    best_r = r;
                    best_c = c;
                    if (cnt == 1) goto place;
                }
            }
        }
    }

    if (best_r == -1) {
        solved = true;
        return true;
    }

place:
    int cand = get_candidates(best_r, best_c);
    for (int d = 1; d <= 9; d++) {
        if (cand & (1 << (d-1))) {
            set_cell(best_r, best_c, d);
            if (dfs()) return true;
            clear_cell(best_r, best_c, d);
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    long long ans = 0;

    while (N--) {
        for (int i = 0; i < 9; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < 9; j++) {
                grid[i][j] = s[j] - '0';
            }
        }

        memset(row_mask, 0, sizeof(row_mask));
        memset(col_mask, 0, sizeof(col_mask));
        memset(box_mask, 0, sizeof(box_mask));

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (grid[i][j] != 0) {
                    int d = grid[i][j];
                    int bit = 1 << (d-1);
                    row_mask[i] |= bit;
                    col_mask[j] |= bit;
                    box_mask[i/3][j/3] |= bit;
                }
            }
        }

        solved = false;
        dfs();

        ans += grid[0][0] * 100 + grid[0][1] * 10 + grid[0][2];
    }

    cout << ans << "\n";
    return 0;
}
