#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> cases;

    // 1: sample N=5 → ans=15
    cases.push_back(5);

    // 2-4: small N
    cases.push_back(1);
    cases.push_back(2);
    cases.push_back(6);

    // 5: PE original N=50 → ans=100808458960497
    cases.push_back(50);

    // 6-8: random medium
    cases.push_back(rand_int(10, 20));
    cases.push_back(rand_int(21, 35));
    cases.push_back(rand_int(36, 45));

    // 9-10: random large
    cases.push_back(rand_int(46, 50));
    cases.push_back(rand_int(40, 50));

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << cases[i] << "\n";
    }

    return 0;
}
