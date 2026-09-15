#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for (int t = 0; t < 10; t++) {
        string filename = string("data/") + (t < 9 ? "0" : "") + to_string(t + 1) + ".in";
        ofstream fout(filename);

        int N;
        if (t == 0) {
            // Sample: passcode "312", only one 3-char subsequence possible
            N = 1;
            fout << N << "\n";
            fout << "312\n";
        } else if (t <= 2) {
            N = rand_int(3, 8);
            fout << N << "\n";
        } else if (t <= 5) {
            N = rand_int(10, 25);
            fout << N << "\n";
        } else if (t <= 8) {
            N = rand_int(30, 45);
            fout << N << "\n";
        } else {
            N = 50;
            fout << N << "\n";
        }

        if (t > 0) {
            int len = rand_int(3, 8);
            string passcode;
            set<char> used;
            for (int i = 0; i < len; i++) {
                char c;
                do {
                    c = '0' + rand_int(0, 9);
                } while (used.count(c));
                used.insert(c);
                passcode += c;
            }
            for (int i = 0; i < N; i++) {
                int a = rand_int(0, len - 3);
                int b = rand_int(a + 1, len - 2);
                int c = rand_int(b + 1, len - 1);
                fout << passcode[a] << passcode[b] << passcode[c] << "\n";
            }
        }

        fout.close();
        cout << "Generated " << filename << " with N = " << N << "\n";
    }

    return 0;
}
