#include <bits/stdc++.h>
using namespace std;

int main() {

    int T;
    cin >> T;
    while(T--) {
        int m;
        cin >> m;
        vector<vector<int>> a(m, vector<int>(m));
        for(int i = 0; i < m; i++)
            for(int j = 0; j < m; j++)
                cin >> a[i][j];

        int ans = INT_MIN;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < m; ++j) {
                if(j + 3 < m) ans = max(ans, a[i][j]*a[i][j+1]*a[i][j+2]*a[i][j+3]);
                if(i + 3 < m) ans = max(ans, a[i][j]*a[i+1][j]*a[i+2][j]*a[i+3][j]);
                if(i + 3 < m && j + 3 < m) ans = max(ans, a[i][j]*a[i+1][j+1]*a[i+2][j+2]*a[i+3][j+3]);
                if(i + 3 < m && j - 3 >= 0) ans = max(ans, a[i][j]*a[i+1][j-1]*a[i+2][j-2]*a[i+3][j-3]);
            }
        }
        cout << ans << "\n";
    }
}