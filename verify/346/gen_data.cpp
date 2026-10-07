#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<ll> tests(10);

    // 1: PE original (N=10^12) → answer: 336108797689833276
    tests[0] = 1000000000000LL;

    // 2: given example (N=1000) → answer: 15864
    tests[1] = 1000;

    // 3: small (N=50) → answer: sum of {1,7,13,15,21,31,40,43} = 171
    tests[2] = 50;

    // 4-5: small range
    tests[3] = 100;
    tests[4] = 500;

    // 6-7: medium
    tests[5] = 10000;
    tests[6] = 100000;

    // 8-9: large
    tests[7] = 10000000LL;
    tests[8] = 100000000LL;

    // 10: near PE
    tests[9] = 1000000000000LL;

    for(int i = 0; i < 10; i++){
        string fname = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << tests[i] << "\n";
    }
    return 0;
}
