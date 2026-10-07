#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1: PE answer (N=100, K=50, answer=115039000)
    test_cases[0] = {100, 50};

    // 2-3: sample / small
    test_cases[1] = {6, 3};   // example from problem: B={1,3,6,8,10,11}
    test_cases[2] = {6, 2};

    // 4-5: small for brute verification
    test_cases[3] = {10, 3};
    test_cases[4] = {12, 4};

    // 6-8: medium
    test_cases[5] = {20, 5};
    test_cases[6] = {30, 8};
    test_cases[7] = {40, 10};

    // 9: random
    test_cases[8] = {30 + rand_int(0, 10), rand_int(2, 10)};

    // 10: near max
    test_cases[9] = {50, 15};

    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].first << " K=" << test_cases[i].second << "\n";
    }
}
