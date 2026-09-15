#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1000000;

int d[MAXN + 1];    // sum of proper divisors
int vis[MAXN + 1];  // 0=unvisited, 1=visiting, 2=done
int depth[MAXN + 1];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Sieve to compute sum of proper divisors
    // d[i] will hold sum of proper divisors of i
    for (int i = 1; i <= N; i++) {
        for (int j = 2 * i; j <= N; j += i) {
            d[j] += i;
        }
    }

    int best_len = 0;
    int best_min = 0;

    for (int i = 2; i <= N; i++) {
        if (vis[i]) continue;

        vector<int> chain;
        int cur = i;
        while (true) {
            if (cur > N || cur < 1) {
                // exceeds bound or reaches 0/1 (which have no proper divisors)
                for (int v : chain) vis[v] = 2;
                break;
            }
            if (vis[cur] == 1) {
                // Found a cycle! Locate the start of the cycle in chain
                int cycle_start = -1;
                for (int j = 0; j < (int)chain.size(); j++) {
                    if (chain[j] == cur) {
                        cycle_start = j;
                        break;
                    }
                }
                int cycle_len = (int)chain.size() - cycle_start;
                if (cycle_len > 1) {
                    int cycle_min = cur;
                    for (int j = cycle_start; j < (int)chain.size(); j++) {
                        cycle_min = min(cycle_min, chain[j]);
                    }
                    if (cycle_len > best_len) {
                        best_len = cycle_len;
                        best_min = cycle_min;
                    } else if (cycle_len == best_len && cycle_min < best_min) {
                        best_min = cycle_min;
                    }
                }
                for (int v : chain) vis[v] = 2;
                break;
            }
            if (vis[cur] == 2) {
                // already processed
                for (int v : chain) vis[v] = 2;
                break;
            }

            vis[cur] = 1;
            chain.push_back(cur);
            cur = d[cur];
        }
    }

    cout << best_min << "\n";
    return 0;
}
