#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,ull>> test_cases(10);

    // 1: M=3, K=1000000 → n=30 (from PE description)
    test_cases[0] = {3, 1000000ULL};

    // 2: M=10, K=1000000 → n=57 (from PE description)
    test_cases[1] = {10, 1000000ULL};

    // 3: M=50, K=1000000 → n=168 (original PE)
    test_cases[2] = {50, 1000000ULL};

    // 4: M=3, K=100
    test_cases[3] = {3, 100ULL};

    // 5: M=5, K=5000
    test_cases[4] = {5, 5000ULL};

    // 6: M=20, K=500000
    test_cases[5] = {20, 500000ULL};

    // 7: M=30, K=1000000
    test_cases[6] = {30, 1000000ULL};

    // 8: M=40, K=1000000
    test_cases[7] = {40, 1000000ULL};

    // 9: M=3, K=10 → n=7 (manually: F(3,6)=something, F(3,7)=?)
    test_cases[8] = {3, 10ULL};

    // 10: M=5, K=1000000
    test_cases[9] = {5, 1000000ULL};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with M=" << test_cases[i].first << " K=" << test_cases[i].second << "\n";
    }

    return 0;
}
