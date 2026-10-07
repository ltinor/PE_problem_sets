#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

void gen_file(const string &filename, const vector<int> &manual, int T_rand, int n_min, int n_max) {
    system("mkdir -p data");
    ofstream fout("data/" + filename);

    int total = manual.size() + T_rand;
    fout << total << "\n";

    for (int n : manual) fout << n << "\n";
    for (int i = 0; i < T_rand; i++) fout << rand_int(n_min, n_max) << "\n";

    fout.close();
    cout << "Generated data/" << filename << " with " << total << " cases\n";
}

int main() {
    srand(time(0));

    // 1.in: Sample cases
    {
        vector<int> manual = {
            2,    // d<2: no valid d
            3,    // d<3: d=2 (no cycle)
            4,    // d<4: d=3 (cycle 1)
            8,    // d<8: d=7 (cycle 6)
            11,   // d<11: d=7 (cycle 6)
        };
        gen_file("01.in", manual, 5, 2, 20);
    }

    // 2.in: Original PE problem (N=1000)
    {
        vector<int> manual = {1000};
        gen_file("02.in", manual, 9, 2, 500);
    }

    // 3.in: Medium
    gen_file("03.in", {}, 10, 500, 2000);

    // 4.in: Medium-large
    gen_file("04.in", {}, 10, 2000, 5000);

    // 5.in: Large
    gen_file("05.in", {}, 10, 5000, 8000);

    // 6.in: Very large
    gen_file("06.in", {}, 10, 8000, 10000);

    // 7.in: Edge cases
    {
        vector<int> manual = {
            2,
            3,
            10,
            100,
            500,
            1000,
            5000,
            10000
        };
        gen_file("07.in", manual, 2, 2, 10000);
    }

    // 8.in-10.in: random
    gen_file("08.in", {}, 10, 2, 10000);
    gen_file("09.in", {}, 10, 2, 10000);
    gen_file("10.in", {}, 10, 2, 10000);

    return 0;
}
