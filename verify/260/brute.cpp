#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 260: Stone Game brute force for small N
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<vector<vector<bool>>> dp(N+1, 
        vector<vector<bool>>(N+1, vector<bool>(N+1, false)));
    ll s = 0;
    for (int a = 0; a <= N; a++) {
        for (int b = a; b <= N; b++) {
            for (int c = b; c <= N; c++) {
                if (a==0 && b==0 && c==0) continue;
                bool w = false;
                for (int n = 1; n <= a && !w; n++) {
                    auto v = vector<int>{a-n,b,c}; sort(v.begin(),v.end());
                    if (!dp[v[0]][v[1]][v[2]]) w=true;
                }
                for (int n = 1; n <= b && !w; n++) {
                    auto v = vector<int>{a,b-n,c}; sort(v.begin(),v.end());
                    if (!dp[v[0]][v[1]][v[2]]) w=true;
                }
                for (int n = 1; n <= c && !w; n++) {
                    auto v = vector<int>{a,b,c-n}; sort(v.begin(),v.end());
                    if (!dp[v[0]][v[1]][v[2]]) w=true;
                }
                for (int n = 1; n <= min(a,b) && !w; n++) {
                    auto v = vector<int>{a-n,b-n,c}; sort(v.begin(),v.end());
                    if (!dp[v[0]][v[1]][v[2]]) w=true;
                }
                for (int n = 1; n <= min(a,c) && !w; n++) {
                    auto v = vector<int>{a-n,b,c-n}; sort(v.begin(),v.end());
                    if (!dp[v[0]][v[1]][v[2]]) w=true;
                }
                for (int n = 1; n <= min(b,c) && !w; n++) {
                    auto v = vector<int>{a,b-n,c-n}; sort(v.begin(),v.end());
                    if (!dp[v[0]][v[1]][v[2]]) w=true;
                }
                for (int n = 1; n <= a && !w; n++)
                    if (!dp[a-n][b-n][c-n]) w=true;
                dp[a][b][c]=w;
                if(!w)s+=a+b+c;
            }
        }
    }
    cout << s << "\n";
}
