#include <bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

void gen_case(const string &filename, const vector<int> &manual_data,
              int T_random = 0, int K_min = 1, int K_max = 2000000) {
    system("mkdir -p data");
    ofstream fout("data/" + filename);

    int T = manual_data.size() + T_random;
    fout << T << "\n";

    for(int x : manual_data) fout << x << "\n";

    for(int i = 0; i < T_random; i++) {
        fout << rand_int(K_min, K_max) << "\n";
    }

    fout.close();
    cout << "Generated data/" << filename << endl;
}

int main() {

    gen_case("1.in", {10}, 0);
    gen_case("2.in", {}, 100, 1, 10000);
    gen_case("3.in", {}, 1000, 1, 500000);
    gen_case("4.in", {}, 10000, 1, 2000000);
    gen_case("5.in", {}, 10000, 1500000, 2000000);

    {
        vector<int> manual;
        for(int i = 1; i <= 10000; i++) manual.push_back(i * 200);
        gen_case("6.in", manual, 0);
    }

    {
        vector<int> manual;
        for(int i = 10000; i >= 1; i--) manual.push_back(i * 200);
        gen_case("7.in", manual, 0);
    }

    for(int i = 8; i <= 10; i++) {
        gen_case(to_string(i) + ".in", {}, 10000, 1, 2000000);
    }

    return 0;
}