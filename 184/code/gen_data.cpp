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
            // Original PE: R=105 → 1725323624056
            fout << "1\n105\n";
        } else if (tc == 1) {
            // Sample: R=2 → 8
            fout << "1\n2\n";
        } else if (tc == 2) {
            // Sample: R=3 → 360
            fout << "1\n3\n";
        } else if (tc == 3) {
            // Sample: R=5 → 10600
            fout << "1\n5\n";
        } else if (tc == 7) {
            // Medium
            fout << "1\n10\n";
        } else if (tc == 8) {
            // Multi small
            fout << "3\n4\n6\n8\n";
        } else {
            // Random medium
            fout << "1\n" << rand_int(2, 30) << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
