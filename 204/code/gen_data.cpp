#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,ll>> test_cases(10);

    // 1: PE answer (n=100, m=10^9, answer=2944730)
    test_cases[0] = {100, 1000000000LL};

    // 2: sample (n=5, m=10^8, answer=1105)
    test_cases[1] = {5, 100000000LL};

    // 3-5: small
    test_cases[2] = {5, 100};
    test_cases[3] = {10, 1000000};
    test_cases[4] = {20, 10000000};

    // 6-8: medium
    test_cases[5] = {30, 100000000};
    test_cases[6] = {50, 100000000LL};
    test_cases[7] = {100, 10000000};

    // 9: boundary small
    test_cases[8] = {2, 1000000000000LL};

    // 10: boundary
    test_cases[9] = {100, 1000000000000LL};

    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with n=" << test_cases[i].first << " m=" << test_cases[i].second << "\n";
    }
}
