#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> cases;

    // 1: sample N=4 → prize=10
    cases.push_back(4);

    // 2-3: small N
    cases.push_back(1);
    cases.push_back(2);

    // 4: N=3
    cases.push_back(3);

    // 5: N=5
    cases.push_back(5);

    // 6: N=6
    cases.push_back(6);

    // 7: PE original N=15 → prize=2269
    cases.push_back(15);

    // 8-10: random
    cases.push_back(rand_int(7, 10));
    cases.push_back(rand_int(11, 13));
    cases.push_back(rand_int(14, 15));

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << cases[i] << "\n";
    }

    return 0;
}
