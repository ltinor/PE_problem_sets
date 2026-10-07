#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    // 01.in: sample
    ofstream("data/01.in") << "3\nSKY\nA\nABC\n";
    // 02-04: small
    for (int id = 2; id <= 4; id++) {
        string fn = string("data/") + (id<10?"0":"") + to_string(id) + ".in";
        ofstream f(fn);
        int N = 10 + rand() % 20;
        f << N << "\n";
        for (int i = 0; i < N; i++) {
            int len = rand() % 10 + 1;
            for (int j = 0; j < len; j++) f << char('A' + rand() % 26);
            f << "\n";
        }
    }
    // 05-07: medium
    for (int id = 5; id <= 7; id++) {
        string fn = string("data/") + (id<10?"0":"") + to_string(id) + ".in";
        ofstream f(fn);
        int N = 50 + rand() % 100;
        f << N << "\n";
        for (int i = 0; i < N; i++) {
            int len = rand() % 15 + 1;
            for (int j = 0; j < len; j++) f << char('A' + rand() % 26);
            f << "\n";
        }
    }
    // 08-10: large
    for (int id = 8; id <= 10; id++) {
        string fn = string("data/") + (id<10?"0":"") + to_string(id) + ".in";
        ofstream f(fn);
        int N = 500 + rand() % 500;
        f << N << "\n";
        for (int i = 0; i < N; i++) {
            int len = rand() % 20 + 1;
            for (int j = 0; j < len; j++) f << char('A' + rand() % 26);
            f << "\n";
        }
    }
}
