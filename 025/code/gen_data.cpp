#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

void gen_file(const string &filename, const vector<int> &manual, int T_rand, int d_min, int d_max) {
    system("mkdir -p data");
    ofstream fout("data/" + filename);

    int total = manual.size() + T_rand;
    fout << total << "\n";

    for (int d : manual) fout << d << "\n";
    for (int i = 0; i < T_rand; i++) fout << rand_int(d_min, d_max) << "\n";

    fout.close();
    cout << "Generated data/" << filename << " with " << total << " cases\n";
}

int main() {
    srand(time(0));

    // 1.in: Sample cases
    {
        vector<int> manual = {
            1,    // F1 has 1 digit -> 1
            2,    // first 2-digit Fibonacci -> 7
            3,    // first 3-digit -> 12
            4,    // first 4-digit
            5,    // first 5-digit
        };
        gen_file("01.in", manual, 5, 1, 10);
    }

    // 2.in: Small D
    gen_file("02.in", {}, 10, 1, 500);

    // 3.in: Medium D
    gen_file("03.in", {}, 10, 500, 1000);

    // 4.in: Original PE problem
    {
        vector<int> manual = {1000};
        gen_file("04.in", manual, 9, 1000, 2000);
    }

    // 5.in: Large D
    gen_file("05.in", {}, 10, 2000, 3500);

    // 6.in: Very large D
    gen_file("06.in", {}, 10, 3500, 5000);

    // 7.in: Edge cases
    {
        vector<int> manual = {
            1,
            2, 
            3,
            10,
            100,
            1000,
            2000,
            3000,
            4000,
            5000
        };
        gen_file("07.in", manual, 0, 0, 0);
    }

    // 8.in-10.in: random
    gen_file("08.in", {}, 10, 1, 5000);
    gen_file("09.in", {}, 10, 1, 5000);
    gen_file("10.in", {}, 10, 1, 5000);

    return 0;
}
