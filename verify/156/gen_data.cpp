#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Fixed answer: always output 21295121502550
    // 10 test cases with dummy input
    vector<int> test_cases = {1, 2, 3, 5, 10, 20, 50, 100, 1, 1};

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with t = " << test_cases[i] << "\n";
    }

    return 0;
}
