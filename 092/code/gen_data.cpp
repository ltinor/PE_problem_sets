#include <bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int main() {
    system("mkdir -p data");

    vector<int> test_cases = {
        100,          // small sample
        1000,         // small
        10000,        // medium
        100000,       // larger
        1000000,      // large
        10000000,     // PE answer: 8581146
        rand_int(1, 1000),
        rand_int(1000, 100000),
        rand_int(100000, 5000000),
        rand_int(5000000, 10000000),
    };

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
