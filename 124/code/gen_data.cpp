#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int, int>> cases; // (N, K)

    // Multiple test cases per file
    vector<vector<pair<int, int>>> test_groups(10);

    // 1: sample - single case
    test_groups[0] = {{10, 4}}; // rad(1)=1,rad(2)=2,rad(3)=3,rad(4)=2,rad(5)=5,... sorted: 1→1, 2→2, 4→2, 3→3 → 4th is 3? Let me check. Actually PE 124 answer: n≤100000, K=10000 → 21417

    // 2-3: small N, single case
    test_groups[1] = {{5, 3}};
    test_groups[2] = {{20, 10}};

    // 4-6: medium N with multiple queries
    test_groups[3] = {{1000, 500}};
    test_groups[4] = {{5000, 2500}};
    test_groups[5] = {{10000, 5000}};

    // 7: PE original N=100000, K=10000 → ans=21417
    test_groups[6] = {{100000, 10000}};

    // 8: N=100000, K=1
    test_groups[7] = {{100000, 1}};

    // 9: N=100000, K=100000
    test_groups[8] = {{100000, 100000}};

    // 10: random
    test_groups[9] = {{rand_int(50000, 80000), rand_int(1, 50000)}};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_groups[i][0].first << " " << test_groups[i][0].second << "\n";
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
