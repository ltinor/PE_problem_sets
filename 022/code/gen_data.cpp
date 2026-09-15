#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

string rand_name(int len) {
    string s;
    for (int i = 0; i < len; i++) {
        s += (char)('A' + rand() % 26);
    }
    return s;
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for (int tc = 0; tc < 10; tc++) {
        string filename = string("data/") + (tc < 9 ? "0" : "") + to_string(tc + 1) + ".in";
        ofstream fout(filename);

        int N;
        if (tc == 0) {
            // Sample: small number of short names
            N = 5;
            fout << N << "\n";
            vector<string> names = {"JOHN", "COLIN", "ADAM", "DAVID", "MARY"};
            for (const string& s : names) fout << s << "\n";
        } else if (tc == 1) {
            N = rand_ll(2, 8);
            fout << N << "\n";
            for (int i = 0; i < N; i++) {
                fout << rand_name(rand_ll(2, 5)) << "\n";
            }
        } else if (tc == 2 || tc == 3) {
            N = rand_ll(5, 20);
            fout << N << "\n";
            for (int i = 0; i < N; i++) {
                fout << rand_name(rand_ll(2, 8)) << "\n";
            }
        } else if (tc == 4 || tc == 5) {
            N = rand_ll(50, 500);
            fout << N << "\n";
            for (int i = 0; i < N; i++) {
                fout << rand_name(rand_ll(2, 12)) << "\n";
            }
        } else if (tc == 6 || tc == 7) {
            N = rand_ll(1000, 5000);
            fout << N << "\n";
            for (int i = 0; i < N; i++) {
                fout << rand_name(rand_ll(3, 15)) << "\n";
            }
        } else if (tc == 8) {
            // Edge: single name
            N = 1;
            fout << "1\nAAAA\n";
        } else {
            // Large max
            N = 5000;
            fout << N << "\n";
            for (int i = 0; i < N; i++) {
                fout << rand_name(rand_ll(3, 20)) << "\n";
            }
        }

        fout.close();
        cout << "Generated " << filename << " with N=" << N << "\n";
    }

    return 0;
}
