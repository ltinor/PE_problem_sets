#include<bits/stdc++.h>
using namespace std;

bool check(const set<int> &a, const set<int> &b){
    vector<pair<int,int>> squares = {
        {0,1}, {0,4}, {0,9}, {1,6}, {2,5},
        {3,6}, {4,9}, {6,4}, {8,1}
    };

    for(auto &sq : squares){
        int d1 = sq.first, d2 = sq.second;
        bool ok = false;
        if((a.count(d1) || (d1==6 && a.count(9)) || (d1==9 && a.count(6))) &&
           (b.count(d2) || (d2==6 && b.count(9)) || (d2==9 && b.count(6))))
            ok = true;
        if((b.count(d1) || (d1==6 && b.count(9)) || (d1==9 && b.count(6))) &&
           (a.count(d2) || (d2==6 && a.count(9)) || (d2==9 && a.count(6))))
            ok = true;
        if(!ok) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dummy;
    cin >> dummy;

    vector<set<int>> combos;
    for(int mask = 0; mask < (1<<10); mask++){
        if(__builtin_popcount(mask) == 6){
            set<int> s;
            for(int i = 0; i < 10; i++)
                if(mask & (1<<i)) s.insert(i);
            combos.push_back(s);
        }
    }

    int ans = 0;
    int m = combos.size();
    for(int i = 0; i < m; i++){
        for(int j = i; j < m; j++){
            if(check(combos[i], combos[j]))
                ans++;
        }
    }

    cout << ans << "\n";
}
