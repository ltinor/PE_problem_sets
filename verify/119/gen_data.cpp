#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> cases;

    // 1: K=1 → a1=81 (8+1=9, 9^2=81)
    cases.push_back(1);

    // 2: sample K=2 → a2=512
    cases.push_back(2);

    // 3: K=5
    cases.push_back(5);

    // 4: K=8
    cases.push_back(8);

    // 5: sample K=10 → a10=614656
    cases.push_back(10);

    // 6: K=15
    cases.push_back(15);

    // 7: K=20
    cases.push_back(20);

    // 8: K=25
    cases.push_back(25);

    // 9: PE original K=30 → a30=248155780267521
    cases.push_back(30);

    // 10: K=28
    cases.push_back(28);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with K = " << cases[i] << "\n";
    }

    return 0;
}
