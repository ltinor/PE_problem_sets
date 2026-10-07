#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int fact[10];
vector<int> chain_len(MAXN + 1, -1);

int digit_fact_sum(int x) {
    if (x == 0) return fact[0];
    int s = 0;
    while (x) {
        s += fact[x % 10];
        x /= 10;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= 9; i++) fact[i] = fact[i-1] * i;

    int N, K;
    cin >> N >> K;

    for (int start = 1; start < N; start++) {
        if (chain_len[start] != -1) continue;

        // Follow chain and record path
        vector<int> path;
        unordered_map<int, int> pos;
        int cur = start;
        while (pos.find(cur) == pos.end() && (cur > MAXN || chain_len[cur] == -1)) {
            pos[cur] = path.size();
            path.push_back(cur);
            cur = digit_fact_sum(cur);
        }

        // Now cur is either in path (cycle) or has known chain_len
        if (cur <= MAXN && chain_len[cur] != -1) {
            // Reached a known value; work backwards
            int suffix_len = chain_len[cur];
            for (int i = (int)path.size() - 1; i >= 0; i--) {
                suffix_len++;
                if (path[i] <= MAXN) chain_len[path[i]] = suffix_len;
            }
        } else {
            // cur is in path at position pos[cur]
            int cycle_start = pos[cur];
            int cycle_len = (int)path.size() - cycle_start;
            for (int i = cycle_start; i < (int)path.size(); i++) {
                if (path[i] <= MAXN) chain_len[path[i]] = cycle_len;
            }
            int suffix_len = cycle_len;
            for (int i = cycle_start - 1; i >= 0; i--) {
                suffix_len++;
                if (path[i] <= MAXN) chain_len[path[i]] = suffix_len;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i < N; i++) {
        if (chain_len[i] == K) ans++;
    }

    cout << ans << "\n";
    return 0;
}
