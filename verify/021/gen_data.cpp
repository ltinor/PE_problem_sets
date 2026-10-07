#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases
    for (int tc = 0; tc < 10; tc++) {
        string filename = string("data/") + (tc < 9 ? "0" : "") + to_string(tc + 1) + ".in";
        ofstream fout(filename);

        int T, minN, maxN;
        if (tc == 0) {
            // Sample: single test case N=300 (contains amicable pair 220,284)
            T = 1;
            fout << T << "\n";
            fout << "300\n";
        } else if (tc == 1) {
            // Small: few tests, small N
            T = rand_ll(2, 5);
            minN = 1; maxN = 300;
            fout << T << "\n";
            for (int i = 0; i < T; i++) {
                fout << rand_ll(minN, maxN) << "\n";
            }
        } else if (tc == 2) {
            // Small random
            T = rand_ll(3, 10);
            minN = 1; maxN = 5000;
            fout << T << "\n";
            for (int i = 0; i < T; i++) {
                fout << rand_ll(minN, maxN) << "\n";
            }
        } else if (tc == 3 || tc == 4) {
            // Medium
            T = rand_ll(10, 100);
            minN = 1; maxN = 50000;
            fout << T << "\n";
            for (int i = 0; i < T; i++) {
                fout << rand_ll(minN, maxN) << "\n";
            }
        } else if (tc == 5 || tc == 6) {
            // Large
            T = rand_ll(50, 200);
            minN = 1; maxN = 100000;
            fout << T << "\n";
            for (int i = 0; i < T; i++) {
                fout << rand_ll(minN, maxN) << "\n";
            }
        } else if (tc == 7) {
            // Edge: boundary N=1
            T = 3;
            fout << T << "\n1\n10\n100\n";
        } else if (tc == 8) {
            // Edge: max N
            T = 1;
            fout << "1\n100000\n";
        } else {
            // Mixed random
            T = rand_ll(100, 200);
            minN = 1; maxN = 100000;
            fout << T << "\n";
            for (int i = 0; i < T; i++) {
                fout << rand_ll(minN, maxN) << "\n";
            }
        }

        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
