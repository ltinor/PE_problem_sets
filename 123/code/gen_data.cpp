#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull rand_ull(ull l, ull r) {
    return l + (ull)rand() * rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ull> cases;

    // 1: sample: T=100, first n where r > 100
    cases.push_back(100);

    // 2: T=1000
    cases.push_back(1000);

    // 3: T=10000
    cases.push_back(10000);

    // 4: T=100000
    cases.push_back(100000);

    // 5: T=1000000
    cases.push_back(1000000);

    // 6: T=10000000 (1e7)
    cases.push_back(10000000ULL);

    // 7: PE original T=10000000000 (1e10) → ans=21035
    cases.push_back(10000000000ULL);

    // 8: T=100000000000 (1e11)
    cases.push_back(100000000000ULL);

    // 9: T=1000000000000 (1e12, max)
    cases.push_back(1000000000000ULL);

    // 10: random
    cases.push_back(rand_ull(1000000, 5000000000ULL));

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with T = " << cases[i] << "\n";
    }

    return 0;
}
