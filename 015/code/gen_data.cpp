#include <bits/stdc++.h>
using namespace std;
#define ll long long

int randint(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 1.in: 样例
    {
        ofstream fout("data/01.in");
        fout << "3\n";
        fout << "2 2\n";
        fout << "3 3\n";
        fout << "20 20\n";
        fout.close();
    }

    // 2-4: 小数据
    for (int id = 2; id <= 4; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 10;
        fout << T << "\n";
        for (int t = 0; t < T; t++) {
            int n = randint(1, 30);
            int m = randint(1, 30);
            fout << n << " " << m << "\n";
        }
        fout.close();
    }

    // 5-7: 中等数据
    for (int id = 5; id <= 7; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 10;
        fout << T << "\n";
        for (int t = 0; t < T; t++) {
            int n = randint(100, 500);
            int m = randint(100, 500);
            fout << n << " " << m << "\n";
        }
        fout.close();
    }

    // 8-10: 边界+大数据
    for (int id = 8; id <= 10; id++) {
        string fname = string("data/") + (id < 10 ? "0" : "") + to_string(id) + ".in";
        ofstream fout(fname);
        int T = 5;
        fout << T << "\n";
        fout << "1 1\n";
        fout << "500 500\n";
        fout << "1 500\n";
        fout << "500 1\n";
        fout << "250 250\n";
        fout.close();
    }
    return 0;
}
