#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    vector<long long> test_cases(10);
    
    // 1: PE example (n=91, answer=363)
    test_cases[0] = 91;
    
    // 2-3: small n
    test_cases[1] = 7;
    test_cases[2] = 9;
    
    // 4-5: medium (product of small primes)
    test_cases[3] = 2 * 3 * 5 * 7;       // 210
    test_cases[4] = 3 * 7 * 13;           // 273
    test_cases[5] = 2 * 3 * 7 * 13;       // 546
    
    // 6: product of several primes ≡ 1 mod 3
    test_cases[6] = 7 * 13 * 19;          // 1729
    
    // 7-8: larger
    test_cases[7] = 2 * 3 * 7 * 13 * 19;  // 10374
    test_cases[8] = 7 * 13 * 19 * 31;     // 53599
    
    // 9: PE answer (n=13082761331670030, answer=4617456485273129588)
    test_cases[9] = 13082761331670030LL;
    
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }
    
    return 0;
}
