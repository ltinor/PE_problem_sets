#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> cases;

    // 1: N=1 → only {1}, not prime → 0 sets
    cases.push_back(1);

    // 2: N=2 → digits {1,2}, primes: 2, but 12 not prime, 21 not prime. Only {2}? No "1" is not prime. Sets: none. Actually 2 is prime but 1 is not. So 0.
    cases.push_back(2);

    // 3: N=3 → digits {1,2,3}
    cases.push_back(3);

    // 4: N=4
    cases.push_back(4);

    // 5: N=5
    cases.push_back(5);

    // 6: N=6
    cases.push_back(6);

    // 7: N=7
    cases.push_back(7);

    // 8: N=8
    cases.push_back(8);

    // 9: PE original N=9 → ans=44680
    cases.push_back(9);

    // 10: duplicate N=9 for verification
    cases.push_back(9);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << cases[i] << "\n";
    }

    return 0;
}
