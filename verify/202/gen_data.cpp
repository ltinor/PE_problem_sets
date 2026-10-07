#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1: PE answer (b=12017639147, answer=1209002624)
    test_cases[0] = 12017639147LL;

    // 2: sample (b=11, answer=2)
    test_cases[1] = 11;

    // 3: second sample (b=1000001, answer=80840)
    test_cases[2] = 1000001;

    // 4-6: small for brute
    test_cases[3] = 5;
    test_cases[4] = 19;
    test_cases[5] = 101;

    // 7-9: medium
    test_cases[6] = 10000001;
    test_cases[7] = 123456789;
    test_cases[8] = 1000000001;

    // 10: boundary - even b (no solution)
    test_cases[9] = 10;

    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with b=" << test_cases[i] << "\n";
    }
}
