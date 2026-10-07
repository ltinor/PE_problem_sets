#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1: N=7, M=3 → 17 (sample)
    test_cases[0] = {7, 3};

    // 2: N=4, M=3
    test_cases[1] = {4, 3};

    // 3: N=10, M=3
    test_cases[2] = {10, 3};

    // 4: N=20, M=3
    test_cases[3] = {20, 3};

    // 5: N=30, M=3
    test_cases[4] = {30, 3};

    // 6: N=40, M=3
    test_cases[5] = {40, 3};

    // 7: N=50, M=3 → 16475640049 (original PE)
    test_cases[6] = {50, 3};

    // 8: N=20, M=4
    test_cases[7] = {20, 4};

    // 9: N=40, M=5
    test_cases[8] = {40, 5};

    // 10: N=50, M=4
    test_cases[9] = {50, 4};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with N=" << test_cases[i].first << " M=" << test_cases[i].second << "\n";
    }

    return 0;
}
