#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force protein folding for small n
// Enumerate all 2^n strings, find optimal folding for each

vector<pair<int,int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};

int count_contacts(const vector<pair<int,int>>& positions, const string& s) {
    int contacts = 0;
    set<pair<int,int>> pos_set(positions.begin(), positions.end());
    for (int i = 0; i < (int)positions.size(); i++) {
        if (s[i] != 'H') continue;
        for (int j = i + 1; j < (int)positions.size(); j++) {
            if (s[j] != 'H') continue;
            if (abs(j - i) == 1) continue; // adjacent
            int dx = abs(positions[i].first - positions[j].first);
            int dy = abs(positions[i].second - positions[j].second);
            if (dx + dy == 1) contacts++;
        }
    }
    return contacts;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n > 6) {
        cout << "-1\n";
        return 0;
    }

    // Enumerate all self-avoiding walks of length n
    ll total_contacts = 0;
    ll total_strings = 1LL << n;

    // Precompute SAWs
    vector<vector<pair<int,int>>> saws;
    function<void(int, vector<pair<int,int>>&, set<pair<int,int>>&)> dfs_saw = 
        [&](int depth, vector<pair<int,int>>& path, set<pair<int,int>>& visited) {
        if (depth == n) {
            saws.push_back(path);
            return;
        }
        pair<int,int> last = path.back();
        for (auto [dx, dy] : dirs) {
            pair<int,int> nxt = {last.first + dx, last.second + dy};
            if (visited.count(nxt)) continue;
            path.push_back(nxt);
            visited.insert(nxt);
            dfs_saw(depth + 1, path, visited);
            visited.erase(nxt);
            path.pop_back();
        }
    };

    vector<pair<int,int>> path = {{0,0}};
    set<pair<int,int>> visited = {{0,0}};
    dfs_saw(1, path, visited);

    // For each string and each SAW, compute max contacts
    for (ll mask = 0; mask < total_strings; mask++) {
        string s;
        for (int i = 0; i < n; i++) {
            s += (mask & (1LL << i)) ? 'H' : 'P';
        }
        int best = 0;
        for (auto& saw : saws) {
            best = max(best, count_contacts(saw, s));
        }
        total_contacts += best;
    }

    cout << fixed << setprecision(9) << (double)total_contacts / total_strings << "\n";
    return 0;
}
