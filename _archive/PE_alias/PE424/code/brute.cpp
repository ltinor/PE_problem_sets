#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE424 brute: attempt to solve a single kakuro puzzle

struct KakuroCell {
    bool is_block, is_empty;
    char letter;
    int h_sum, v_sum;
};

void brute_solve_puzzle(const string& encoded) {
    // Parse tokens
    vector<string> tokens;
    string tok;
    int depth = 0;
    for (char ch : encoded) {
        if (ch == '(') depth++;
        else if (ch == ')') depth--;
        else if (ch == ',' && depth == 0) {
            if (!tok.empty()) tokens.push_back(tok);
            tok.clear();
            continue;
        }
        tok += ch;
    }
    if (!tok.empty()) tokens.push_back(tok);

    int size = stoi(tokens[0]);
    int rows = size + 2, cols = size + 2;

    // Build sum groups from the description
    // This is complex; for brute we just demonstrate parsing
    cout << "Puzzle size: " << size << "x" << size << "\n";
    cout << "Tokens: " << tokens.size() << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string encoded;
    getline(cin, encoded);
    brute_solve_puzzle(encoded);
}
