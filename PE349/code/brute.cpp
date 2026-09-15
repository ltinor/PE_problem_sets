#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE349 brute: simulate fully for small N
int main() {
    ll N; cin >> N;
    set<pair<int,int>> black;
    int x = 0, y = 0, dir = 0;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    ll black_count = 0;

    for (ll step = 0; step < N; step++) {
        auto p = make_pair(x, y);
        if (black.count(p)) {
            black.erase(p);
            black_count--;
            dir = (dir + 3) % 4;
        } else {
            black.insert(p);
            black_count++;
            dir = (dir + 1) % 4;
        }
        x += dx[dir];
        y += dy[dir];
    }
    cout << black_count << "\n";
    return 0;
}
