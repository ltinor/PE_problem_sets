#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<ll> tests(10);

    // 1: PE original (M=10^18) → answer: 115384615384614952
    tests[0] = 1000000000000000000LL;

    // 2: small (M=100) 
    tests[1] = 100;

    // 3-5: small-medium
    tests[2] = 1000;
    tests[3] = 5000;
    tests[4] = 10000;

    // 6-8: medium-large
    tests[5] = 100000;
    tests[6] = 1000000LL;
    tests[7] = 10000000LL;

    // 9-10: large
    tests[8] = 100000000LL;
    tests[9] = 1000000000LL;

    for(int i = 0; i < 10; i++){
        string fname = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " M=" << tests[i] << "\n";
    }
    return 0;
}
