#include<bits/stdc++.h>
using namespace std;

// Brute force: same algorithm but different pruning order
// Or just hardcode the PE answer for verification

const int LEN = 16;
const int N_GUESSES = 22;

struct Guess {
    string digits;
    int correct;
};

Guess guesses[N_GUESSES] = {
    {"5616185650518293", 2},
    {"3847439647293047", 1},
    {"5855462940810587", 3},
    {"9742855507068353", 3},
    {"4296849643607543", 3},
    {"3174248439465858", 1},
    {"4513559094146117", 2},
    {"7890971548908067", 3},
    {"8157356344118483", 1},
    {"2615250744386899", 2},
    {"8690095851526254", 3},
    {"6375711915077050", 1},
    {"6913859173121360", 1},
    {"6442889055042768", 2},
    {"2321386104303845", 0},
    {"2326509471271448", 2},
    {"5251583379644322", 2},
    {"1748270476758276", 3},
    {"4895722652190306", 1},
    {"3041631117224635", 3},
    {"1841236454324589", 3},
    {"2659862637316867", 2}
};

bool consistent(const string &cur) {
    for (int g = 0; g < N_GUESSES; g++) {
        int matched = 0, unknown = 0;
        for (int p = 0; p < LEN; p++) {
            if (cur[p] == '.') unknown++;
            else if (cur[p] == guesses[g].digits[p]) matched++;
        }
        if (matched > guesses[g].correct) return false;
        if (matched + unknown < guesses[g].correct) return false;
    }
    return true;
}

string answer;
bool found = false;

void dfs_brute(string &cur, int pos) {
    if (found) return;
    if (pos == LEN) {
        for (int g = 0; g < N_GUESSES; g++) {
            int matched = 0;
            for (int p = 0; p < LEN; p++)
                if (cur[p] == guesses[g].digits[p]) matched++;
            if (matched != guesses[g].correct) return;
        }
        answer = cur;
        found = true;
        return;
    }

    for (char d = '0'; d <= '9'; d++) {
        cur[pos] = d;
        if (consistent(cur))
            dfs_brute(cur, pos + 1);
        if (found) return;
    }
    cur[pos] = '.';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string cur(LEN, '.');
    dfs_brute(cur, 0);

    cout << answer << "\n";
    return 0;
}
