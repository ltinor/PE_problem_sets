#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    system("mkdir -p data");
    srand(time(0));

    struct Test { ll G, L, S, MOD; };
    vector<Test> tests(10);

    // MOD = 101^4 = 104060401
    ll MOD = 104060401;

    // 1: PE original → answer: 84664213
    tests[0] = {1000000, 1000000000000LL, 1000000000000000000LL, MOD};

    // 2: given example (G=10, L=100, S=1) → 91
    tests[1] = {10, 100, 1, MOD};

    // 3: given example (G=10, L=100, S=2) → 327
    tests[2] = {10, 100, 2, MOD};

    // 4: given example (G=10, L=100, S=3) → 1135
    tests[3] = {10, 100, 3, MOD};

    // 5-6: small variations
    tests[4] = {100, 1000, 5, MOD};
    tests[5] = {1000, 100000, 10, MOD};

    // 7-8: medium
    tests[6] = {10000, 1000000, 100, MOD};
    tests[7] = {100000, 10000000, 1000, MOD};

    // 9-10: large
    tests[8] = {500000, 500000000000LL, 1000000000LL, MOD};
    tests[9] = {1000000, 1000000000000LL, 1000000000000000000LL, MOD};

    for(int i = 0; i < 10; i++){
        string fname = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i].G << " " << tests[i].L << " " << tests[i].S << " " << tests[i].MOD << "\n";
        fout.close();
        cout << "Generated " << fname << "\n";
    }
    return 0;
}
