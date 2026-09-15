#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1: sample (P=50, Hx=5) → 291.0089
    test_cases[0] = {50, 5};
    // 2: P=200, Hx=5
    test_cases[1] = {200, 5};
    // 3: P=500, Hx=5
    test_cases[2] = {500, 5};
    // 4: P=1000, Hx=5
    test_cases[3] = {1000, 5};
    // 5: P=100, Hx=1
    test_cases[4] = {100, 1};
    // 6: P=100, Hx=3
    test_cases[5] = {100, 3};
    // 7: P=200, Hx=7
    test_cases[6] = {200, 7};
    // 8: P=300, Hx=5
    test_cases[7] = {300, 5};
    // 9: P=2000, Hx=5
    test_cases[8] = {2000, 5};
    // 10: P=5000, Hx=5
    test_cases[9] = {5000, 5};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with P = " << test_cases[i].first 
             << " Hx = " << test_cases[i].second << "\n";
    }

    return 0;
}
