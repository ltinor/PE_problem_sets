#include <bits/stdc++.h>
using namespace std;

mt19937 rng(time(0));

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int main() {
    system("mkdir -p data");

    vector<int> test_cases = {
        2,   // sample: 14
        50,  // PE answer: 14234
        rand_int(0, 10),
        rand_int(0, 10),
        rand_int(11, 30),
        rand_int(11, 30),
        rand_int(31, 49),
        rand_int(31, 49),
        0,   // min
        1,   // just 1
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
