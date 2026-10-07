#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * (long long)rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 每组数据：10 个整数，0..15
    vector<vector<int>> cases(10);

    // 样例：P(2,...,2) = 7120
    cases[0] = vector<int>(10, 2);

    // 小数据
    for (int i = 1; i < 4; i++) {
        cases[i].resize(10);
        for (int j = 0; j < 10; j++) cases[i][j] = rand_ll(0, 5);
    }

    // 中等数据
    for (int i = 4; i < 7; i++) {
        cases[i].resize(10);
        for (int j = 0; j < 10; j++) cases[i][j] = rand_ll(5, 10);
    }

    // 大数据（接近上界 15）
    for (int i = 7; i < 9; i++) {
        cases[i].resize(10);
        for (int j = 0; j < 10; j++) cases[i][j] = rand_ll(10, 15);
    }

    // 边界：全 0
    cases[9] = vector<int>(10, 0);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        for (int j = 0; j < 10; j++) {
            if (j) fout << " ";
            fout << cases[i][j];
        }
        fout << "\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }
    return 0;
}
