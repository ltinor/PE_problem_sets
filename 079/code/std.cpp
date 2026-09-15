#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Build graph: for each 3-digit attempt, a comes before b, b before c
    set<char> chars;
    map<char, set<char>> graph; // graph[x] = set of chars that come after x
    map<char, int> indeg;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        chars.insert(s[0]);
        chars.insert(s[1]);
        chars.insert(s[2]);

        // s[0] -> s[1]
        if (graph[s[0]].find(s[1]) == graph[s[0]].end()) {
            graph[s[0]].insert(s[1]);
        }
        // s[1] -> s[2]
        if (graph[s[1]].find(s[2]) == graph[s[1]].end()) {
            graph[s[1]].insert(s[2]);
        }
    }

    // Compute indegree
    for (auto &p : graph) {
        for (char v : p.second) {
            indeg[v]++;
        }
    }

    // Topological sort (Kahn's algorithm)
    priority_queue<char, vector<char>, greater<char>> pq;
    for (char c : chars) {
        if (indeg[c] == 0) {
            pq.push(c);
        }
    }

    string result;
    while (!pq.empty()) {
        char u = pq.top();
        pq.pop();
        result += u;
        for (char v : graph[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                pq.push(v);
            }
        }
    }

    cout << result << "\n";

    return 0;
}
