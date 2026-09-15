#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> cases;

    // 1: sample K=10
    cases.push_back(10);

    // 2-3: small K
    cases.push_back(1);
    cases.push_back(2);
    cases.push_back(5);

    // 5: K=15
    cases.push_back(15);

    // 6: K=50
    cases.push_back(50);

    // 7: PE original K=200 → ans=1582
    cases.push_back(200);

    // 8-10: random
    cases.push_back(rand_int(20, 40));
    cases.push_back(rand_int(60, 100));
    cases.push_back(rand_int(120, 180));

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << cases[i] << "\n";
    }

    return 0;
}
