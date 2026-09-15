#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> cases(10);

    // 1. sample B=8 (primes 2,3,5,7 → only triple 2,3,5)
    cases[0] = 8;

    // 2-3. small B
    cases[1] = 10;
    cases[2] = 20;

    // 4-6. medium
    cases[3] = 50;
    cases[4] = 100;
    cases[5] = 500;

    // 7-8. large
    cases[6] = 1000;
    cases[7] = 5000;

    // 9-10. random
    cases[8] = rand_int(30, 200);
    cases[9] = rand_int(200, 2000);

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " B=" << cases[i] << "\n";
    }
    return 0;
}
