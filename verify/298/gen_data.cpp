#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Format: T M K
    vector<tuple<int,int,int>> test_cases(10);

    // 1: PE case (T=50, M=5, K=10, answer≈1.76882294)
    test_cases[0] = {50, 5, 10};

    // 2-4: small cases
    test_cases[1] = {5, 2, 5};
    test_cases[2] = {10, 3, 6};
    test_cases[3] = {10, 5, 10};

    // 5-7: medium
    test_cases[4] = {20, 5, 10};
    test_cases[5] = {30, 5, 10};
    test_cases[6] = {50, 3, 10};

    // 8-10: variations
    test_cases[7] = {50, 4, 10};
    test_cases[8] = {30, 5, 8};
    test_cases[9] = {40, 5, 10};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << get<0>(test_cases[i]) << " " << get<1>(test_cases[i]) << " " << get<2>(test_cases[i]) << "\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
