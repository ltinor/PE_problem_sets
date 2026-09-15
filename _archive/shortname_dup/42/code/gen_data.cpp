#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Generate 10 test cases
    for (int t = 0; t < 10; t++) {
        string filename = string("data/") + (t < 9 ? "0" : "") + to_string(t + 1) + ".in";
        ofstream fout(filename);

        int N;
        if (t == 0) {
            // sample: SKY + a few words
            N = 5;
            fout << N << "\n";
            fout << "SKY\n";
            fout << "A\n";
            fout << "B\n";
            fout << "C\n";
            fout << "ABC\n";
        } else if (t == 1) {
            // edge: 1 word
            N = 1;
            fout << N << "\n";
            fout << "Z\n"; // value = 26, not triangle -> 0
        } else if (t == 2) {
            // 0 words edge
            N = 0;
            fout << N << "\n";
        } else {
            N = rand_int(10, 200);
            fout << N << "\n";
            for (int i = 0; i < N; i++) {
                int len = rand_int(1, 20);
                string word;
                for (int j = 0; j < len; j++) {
                    word += (char)('A' + rand() % 26);
                }
                fout << word << "\n";
            }
        }

        fout.close();
        cout << "Generated " << filename << " with N = " << N << "\n";
    }

    return 0;
}
