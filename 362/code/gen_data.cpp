#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1. Sample: S(100)=193
    test_cases[0] = 100;

    // 2-3. Very small
    test_cases[1] = 10;
    test_cases[2] = 25;

    // 4-5. Small
    test_cases[3] = 50;
    test_cases[4] = 75;

    // 6-7. Medium
    test_cases[5] = 150;
    test_cases[6] = 200;

    // 8. Border
    test_cases[7] = 300;

    // 9-10. Larger (but within brute verification range)
    test_cases[8] = 500;
    test_cases[9] = 500;

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " with N=" << test_cases[i] << "\n";
    }
    return 0;
}
