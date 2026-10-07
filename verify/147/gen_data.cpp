#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1: PE answer (47x43, answer=846910284)
    test_cases[0] = {47, 43};

    // 2-3: very small grids
    test_cases[1] = {1, 1};
    test_cases[2] = {2, 2};

    // 4-5: small grids
    test_cases[3] = {3, 2};
    test_cases[4] = {4, 4};

    // 6-7: medium grids
    test_cases[5] = {5, 5};
    test_cases[6] = {8, 6};

    // 8-10: larger grids
    test_cases[7] = {10, 10};
    test_cases[8] = {20, 15};
    test_cases[9] = {30, 20};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with W=" << test_cases[i].first
             << " H=" << test_cases[i].second << "\n";
    }

    return 0;
}
