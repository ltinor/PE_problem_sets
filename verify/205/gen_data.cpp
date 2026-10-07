#include <bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<tuple<int,int,int,int>> test_cases(10);

    // 1: PE answer (9 four-sided vs 6 six-sided, answer=0.5731441)
    test_cases[0] = {9, 4, 6, 6};

    // 2-3: simple cases
    test_cases[1] = {1, 6, 1, 6};  // 1d6 vs 1d6 → 15/36 = 0.4166667
    test_cases[2] = {2, 4, 1, 6};  // 2d4 vs 1d6

    // 4-6: small for brute
    test_cases[3] = {2, 6, 2, 4};
    test_cases[4] = {3, 4, 2, 6};
    test_cases[5] = {1, 20, 1, 4};

    // 7-9: medium
    test_cases[6] = {5, 6, 4, 6};
    test_cases[7] = {6, 8, 5, 10};
    test_cases[8] = {10, 4, 8, 6};

    // 10: near max
    test_cases[9] = {10, 20, 10, 20};

    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(filename);
        fout << get<0>(test_cases[i]) << " " << get<1>(test_cases[i]) << " "
             << get<2>(test_cases[i]) << " " << get<3>(test_cases[i]) << "\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }
}
