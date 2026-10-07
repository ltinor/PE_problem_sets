#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int A_max, B_max;
        cin >> A_max >> B_max;

        // Count distinct a^b for 2≤a≤A_max, 2≤b≤B_max
        // Use prime factorization to generate canonical keys, stored in set<string>
        set<string> distinct;
        vector<vector<pair<int,int>>> factor(A_max + 1);
        for (int a = 2; a <= A_max; a++) {
            int tmp = a;
            for (int p = 2; p * p <= tmp; p++) {
                if (tmp % p == 0) {
                    int cnt = 0;
                    while (tmp % p == 0) {
                        tmp /= p;
                        cnt++;
                    }
                    factor[a].push_back({p, cnt});
                }
            }
            if (tmp > 1) factor[a].push_back({tmp, 1});
        }

        for (int a = 2; a <= A_max; a++) {
            for (int b = 2; b <= B_max; b++) {
                // Build a canonical string representation
                string key;
                for (auto& pf : factor[a]) {
                    key += to_string(pf.first) + "^" + to_string(pf.second * b) + ",";
                }
                distinct.insert(key);
            }
        }

        cout << distinct.size() << "\n";
    }
    return 0;
}
