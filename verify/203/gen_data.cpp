#include <bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE answer (N=51, answer=34029210557338)
    test_cases[0] = 51;

    // 2: sample (N=8, answer=105)
    test_cases[1] = 8;

    // 3-5: small
    test_cases[2] = 5;
    test_cases[3] = 10;
    test_cases[4] = 15;

    // 6-8: medium
    test_cases[5] = 20;
    test_cases[6] = 30;
    test_cases[7] = 40;

    // 9: boundary min
    test_cases[8] = 1;

    // 10: boundary near max
    test_cases[9] = 50;

    for(int i = 0; i < 10; i++){
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i+1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i] << "\n";
    }
}
