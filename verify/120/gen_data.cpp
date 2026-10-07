#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> cases;

    // 1: sample M=7 → rmax=42, sum a=3..7: rmax values: a=3→6, a=4→12, a=5→20, a=6→30, a=7→42, total=110
    cases.push_back(7);

    // 2-3: small M
    cases.push_back(3);
    cases.push_back(10);

    // 4-6: medium M
    cases.push_back(50);
    cases.push_back(100);
    cases.push_back(200);

    // 7: PE original M=1000 → ans=333082500
    cases.push_back(1000);

    // 8-10: random
    cases.push_back(rand_int(300, 500));
    cases.push_back(rand_int(600, 800));
    cases.push_back(rand_int(850, 999));

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with M = " << cases[i] << "\n";
    }

    return 0;
}
