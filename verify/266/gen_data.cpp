#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Predefined test cases
    vector<int> test_cases = {
        5,      // 01: N=5, primes {2,3}, product=6, PSR=2
        10,     // 02: N=10, primes {2,3,5,7}, product=210
        20,     // 03: N=20
        30,     // 04: N=30
        40,     // 05: N=40
        53,     // 06: N=53 (just below 15th prime)
        190,    // 07: PE verification case
        70,     // 08: N=70
        100,    // 09: N=100
        150,    // 10: N=150
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
