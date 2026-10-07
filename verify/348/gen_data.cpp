#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    system("mkdir -p data");
    srand(time(0));

    struct Test { ll K, W; };
    vector<Test> tests(10);

    // 1: PE original (K=5, W=4) → answer: 1004195061
    tests[0] = {5, 4};

    // 2: easier (K=1, W=1) → first palindromic sum of square+cube in 1 way
    // Actually let's test various
    tests[1] = {1, 1};
    tests[2] = {1, 2};

    // 3-5: small numbers of ways
    tests[3] = {3, 2};
    tests[4] = {3, 3};
    tests[5] = {2, 4};

    // 6-8: larger
    tests[6] = {5, 3};
    tests[7] = {5, 2};
    tests[8] = {3, 5};

    // 9-10: PE original variations
    tests[9] = {5, 4};

    for(int i = 0; i < 10; i++){
        string fname = string("data/") + (i<9?"0":"") + to_string(i+1) + ".in";
        ofstream fout(fname);
        fout << tests[i].K << " " << tests[i].W << "\n";
        fout.close();
        cout << "Generated " << fname << " K=" << tests[i].K << " W=" << tests[i].W << "\n";
    }
    return 0;
}
