#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    
    // PE: W(10,2) = 324, W(100,10) = 1514704946113500
    // PE answer: W(1000000, 100) mod 1000036000099 = 65579304332
    // OJ: n ≤ 50, c ≤ 5
    
    struct Case { int n, c; };
    Case cases[] = {
        {5, 1},    // very small
        {10, 2},   // PE example: W(10,2)=324
        {8, 3},    // small
        {12, 2},   // medium
        {15, 3},   // medium
        {18, 4},   // medium-large
        {22, 3},   // medium
        {25, 4},   // large
        {30, 5},   // larger
        {40, 5},   // near max
    };
    
    for (int i = 0; i < 10; i++) {
        string fn = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream f(fn);
        f << cases[i].n << " " << cases[i].c << "\n";
        f.close();
        cout << "Generated " << fn << " n=" << cases[i].n << " c=" << cases[i].c << "\n";
    }
    return 0;
}
