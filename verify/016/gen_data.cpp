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
        fout << "2 15\n";
        fout << "2 1000\n";
        fout << "10 100\n";
        fout.close();
    }

    // 02-04: small a,b
    for (int id = 2; id <= 4; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 10;
        fout << T << "\n";
        for (int t = 0; t < T; t++) {
            int a = randint(2, 20);
            int b = randint(1, 10);
            fout << a << " " << b << "\n";
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
            int a = randint(2, 100);
            int b = randint(100, 1000);
            fout << a << " " << b << "\n";
        }
        fout.close();
    }

    // 08-10: boundary + large
    for (int id = 8; id <= 10; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 5;
        fout << T << "\n";
        fout << "2 1\n";
        fout << "99 1000\n";
        fout << "100 1000\n";
        fout << "3 500\n";
        fout << "2 5000\n";
        fout.close();
    }
    return 0;
}
