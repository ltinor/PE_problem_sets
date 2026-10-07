#include<bits/stdc++.h>
using namespace std;
#define ll long long

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<ll>> a(N, vector<ll>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> a[i][j];
        }
    }

    vector<vector<ll>> dist(N, vector<ll>(N, LLONG_MAX));
    priority_queue<pair<ll, pair<int,int>>, vector<pair<ll, pair<int,int>>>, greater<pair<ll, pair<int,int>>>> pq;

    dist[0][0] = a[0][0];
    pq.push({a[0][0], {0, 0}});

    while(!pq.empty()){
        auto [d, pos] = pq.top(); pq.pop();
        int x = pos.first, y = pos.second;

        if(d != dist[x][y]) continue;

        if(x == N-1 && y == N-1) break;

        for(int k = 0; k < 4; k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(nx >= 0 && nx < N && ny >= 0 && ny < N){
                ll nd = d + a[nx][ny];
                if(nd < dist[nx][ny]){
                    dist[nx][ny] = nd;
                    pq.push({nd, {nx, ny}});
                }
            }
        }
    }

    cout << dist[N-1][N-1] << "\n";

    return 0;
}
