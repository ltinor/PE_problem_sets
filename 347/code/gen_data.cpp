#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<ll> tests(10);

    // 1: PE original (N=10^7) → answer: 11109800204052
    tests[0] = 10000000;

    // 2: given example (N=100) → answer: 2262
    tests[1] = 100;

    // 3-5: small
    tests[2] = 10;
    tests[3] = 30;
    tests[4] = 50;

    // 6-7: medium
    tests[5] = 1000;
    tests[6] = 100000;

    // 8-10: large
    tests[7] = 500000;
    tests[8] = 2000000;
    tests[9] = 10000000;

    for(int i = 0; i < 10; i++){
        string fname = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << tests[i] << "\n";
    }
    return 0;
}
