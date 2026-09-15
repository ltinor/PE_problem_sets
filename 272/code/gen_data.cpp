#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    vector<pair<long long, long long>> test_cases(10);
    
    // 1: PE example: N=91, K=8 (check C(91)=8, sum of n with C(n)=8, n≤91)
    // C(91)=8, so only n=91 might qualify. But also check smaller n.
    test_cases[0] = {91, 8};
    
    // 2: small: K=2 (should find n=9 where C(9)=? 
    // 9 has x³≡1 mod 9: x=1,4,7 → C(9)=2. Also n=7: C(7)=? 7≡1mod3: 3 sols → C(7)=2. Sum=16)
    test_cases[1] = {20, 2};
    
    // 3: K=0
    test_cases[2] = {100, 0};
    
    // 4: K=2, larger bound
    test_cases[3] = {200, 2};
    
    // 5: PE answer (N=100000000000, K=242, expected=8495585919506151122)
    test_cases[4] = {100000000000LL, 242};
    
    // 6-10: random small
    test_cases[5] = {50, 2};
    test_cases[6] = {30, 0};
    test_cases[7] = {100, 8};
    test_cases[8] = {500, 2};
    test_cases[9] = {1000, 8};
    
    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].first << " K=" << test_cases[i].second << "\n";
    }
    
    return 0;
}
