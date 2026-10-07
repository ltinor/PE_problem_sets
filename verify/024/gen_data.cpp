#include<bits/stdc++.h>
using namespace std;

long long fact[11];

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

void gen_file(const string &filename, int T, const vector<pair<int, long long>> &manual,
              int T_rand, int N_min, int N_max) {
    system("mkdir -p data");
    ofstream fout("data/" + filename);

    int total = manual.size() + T_rand;
    fout << total << "\n";

    for (auto &p : manual) {
        fout << p.first << " " << p.second << "\n";
    }

    for (int i = 0; i < T_rand; i++) {
        int N = rand_ll(N_min, N_max);
        long long K = rand_ll(1, fact[N]);
        fout << N << " " << K << "\n";
    }

    fout.close();
    cout << "Generated data/" << filename << " with " << total << " cases\n";
}

int main() {
    srand(time(0));

    fact[0] = 1;
    for (int i = 1; i <= 10; i++) fact[i] = fact[i-1] * i;

    // 1.in: Sample (mostly small, well-known)
    {
        vector<pair<int, long long>> manual = {
            {3, 1},   // 012
            {3, 6},   // 210
            {4, 1},   // 0123
            {4, 24},  // 3210
            {5, 120}, // 43210
        };
        gen_file("01.in", 0, manual, 5, 2, 5);
    }

    // 2.in: Small N, edge K
    {
        vector<pair<int, long long>> manual = {
            {1, 1},    // just 0
            {2, 1},    // 01
            {2, 2},    // 10
        };
        gen_file("02.in", 0, manual, 7, 2, 4);
    }

    // 3.in: N=10, varied K
    {
        vector<pair<int, long long>> manual = {
            {10, 1},            // first
            {10, fact[10]},     // last
            {10, 1000000},      // original PE problem
        };
        gen_file("03.in", 0, manual, 7, 5, 9);
    }

    // 4.in-6.in: mixed random
    gen_file("04.in", 0, {}, 10, 1, 10);
    gen_file("05.in", 0, {}, 10, 5, 10);
    gen_file("06.in", 0, {}, 10, 8, 10);

    // 7.in: edge values
    {
        vector<pair<int, long long>> manual = {
            {1, 1},             // N=1
            {10, 1},            // first perm of 10
            {10, fact[10]},     // last perm of 10
            {10, fact[10] / 2}, // middle
            {9, fact[9]},       // last of N=9
        };
        gen_file("07.in", 0, manual, 5, 3, 8);
    }

    // 8.in-10.in: more random
    gen_file("08.in", 0, {}, 10, 1, 10);
    gen_file("09.in", 0, {}, 10, 1, 10);
    gen_file("10.in", 0, {}, 10, 1, 10);

    return 0;
}
