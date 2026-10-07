#include <bits/stdc++.h>
using namespace std;

int randint(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 01.in: samples
    {
        ofstream fout("data/01.in");
        fout << "3\n";
        fout << "5\n";
        fout << "1000\n";
        fout << "342\n";
        fout.close();
    }

    // 02-04: small n
    for (int id = 2; id <= 4; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 10;
        fout << T << "\n";
        for (int t = 0; t < T; t++) {
            fout << randint(1, 100) << "\n";
        }
        fout.close();
    }

    // 05-07: medium
    for (int id = 5; id <= 7; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 10;
        fout << T << "\n";
        for (int t = 0; t < T; t++) {
            fout << randint(100, 10000) << "\n";
        }
        fout.close();
    }

    // 08-10: boundary + large
    for (int id = 8; id <= 10; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 5;
        fout << T << "\n";
        fout << "1\n";
        fout << "999\n";
        fout << "1000\n";
        fout << "100000\n";
        fout << "500000\n";
        fout.close();
    }
    return 0;
}
