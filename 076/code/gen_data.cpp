#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases, each is multi-test input
    for (int tc = 0; tc < 10; tc++) {
        string filename = string("data/") + (tc < 9 ? "0" : "") + to_string(tc + 1) + ".in";
        ofstream fout(filename);

        int T;
        if (tc == 0) {
            // Sample: single case N=100 (original PE problem)
            T = 1;
            fout << T << "\n";
            fout << 100 << "\n";
        } else if (tc == 1) {
            // Small multi-test
            T = 3;
            fout << T << "\n";
            fout << 5 << "\n" << 10 << "\n" << 20 << "\n";
        } else if (tc == 7) {
            // Boundary: N=2 (minimum), N=100 (maximum)
            T = 2;
            fout << T << "\n";
            fout << 2 << "\n" << 100 << "\n";
        } else {
            // Random multi-test
            T = rand_int(2, 8);
            fout << T << "\n";
            for (int i = 0; i < T; i++) {
                fout << rand_int(2, 100) << "\n";
            }
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
