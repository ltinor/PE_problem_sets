#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for (int tc = 0; tc < 10; tc++) {
        string filename = string("data/") + (tc < 9 ? "0" : "") + to_string(tc + 1) + ".in";
        ofstream fout(filename);

        if (tc == 0) {
            // Original PE: N=10000 → 48861552
            fout << "1\n10000\n";
        } else if (tc == 1) {
            // Sample: N=100 → 2438
            fout << "1\n100\n";
        } else if (tc == 2) {
            // Small: N=10
            fout << "1\n10\n";
        } else if (tc == 3) {
            // N=5 (minimum)
            fout << "1\n5\n";
        } else if (tc == 7) {
            // Medium
            fout << "1\n1000\n";
        } else if (tc == 8) {
            // Multi-test
            fout << "3\n50\n200\n500\n";
        } else {
            // Random
            fout << "1\n" << rand_int(5, 10000) << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
