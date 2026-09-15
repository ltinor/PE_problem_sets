#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for (int tc = 0; tc < 10; tc++) {
        string filename = string("data/") + (tc < 9 ? "0" : "") + to_string(tc + 1) + ".in";
        ofstream fout(filename);

        int T, minN, maxN;
        if (tc == 0) {
            // Sample: N=24 (first expressible, answer includes 1..23)
            T = 1;
            fout << "1\n24\n";
        } else if (tc == 1) {
            // Small: few tests
            T = rand_ll(2, 5);
            fout << T << "\n";
            for (int i = 0; i < T; i++) fout << rand_ll(1, 100) << "\n";
        } else if (tc == 2 || tc == 3) {
            // Medium small
            T = rand_ll(5, 20);
            fout << T << "\n";
            for (int i = 0; i < T; i++) fout << rand_ll(1, 5000) << "\n";
        } else if (tc == 4 || tc == 5) {
            // Medium
            T = rand_ll(10, 50);
            fout << T << "\n";
            for (int i = 0; i < T; i++) fout << rand_ll(1, 20000) << "\n";
        } else if (tc == 6 || tc == 7) {
            // Large
            T = rand_ll(50, 100);
            fout << T << "\n";
            for (int i = 0; i < T; i++) fout << rand_ll(1, 28123) << "\n";
        } else if (tc == 8) {
            // Edge: boundary N=1
            fout << "5\n1\n12\n23\n24\n25\n";
        } else {
            // Maximum
            T = 1;
            fout << "1\n28123\n";
        }

        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
