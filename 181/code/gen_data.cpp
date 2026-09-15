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
            // Sample: original PE problem (60B, 40W)
            fout << "1\n60 40\n";
        } else if (tc == 1) {
            // Small sample: B=3, W=1 → 7
            fout << "1\n3 1\n";
        } else if (tc == 2) {
            // Another small: B=2, W=2
            fout << "1\n2 2\n";
        } else if (tc == 7) {
            // Boundary: min and max
            fout << "2\n0 0\n60 60\n";
        } else if (tc == 8) {
            // Multi-test small
            fout << "5\n";
            for (int t = 0; t < 5; t++) {
                fout << rand_int(0, 10) << " " << rand_int(0, 8) << "\n";
            }
        } else {
            // Random cases
            int T = rand_int(2, 6);
            fout << T << "\n";
            for (int t = 0; t < T; t++) {
                fout << rand_int(0, 60) << " " << rand_int(0, 40) << "\n";
            }
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
