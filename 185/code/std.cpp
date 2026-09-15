#include<bits/stdc++.h>
using namespace std;

string g[22]={"5616185650518293","3847439647293047","5855462940810587","9742855507068353","4296849643607543","3174248439465858","4513559094146117","7890971548908067","8157356344118483","2615250744386899","8690095851526254","6375711915077050","6913859173121360","6442889055042768","2321386104303845","2326509471271448","5251583379644322","1748270476758276","4895722652190306","3041631117224635","1841236454324589","2659862637316867"};
int M[22]={2,1,3,3,3,1,2,3,1,2,3,1,1,2,0,2,2,3,1,3,3,2};

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int _; cin >> _;
    
    // Phase 1: constraint propagation
    vector<set<char>> dom(16);
    for(int i=0;i<16;i++) for(char d='0';d<='9';d++) dom[i].insert(d);
    
    // Remove digits from the 0-match guess
    for(int i=0;i<16;i++) dom[i].erase(g[14][i]);
    
    // Iterative propagation
    bool changed=true;
    while(changed){
        changed=false;
        for(int j=0;j<22;j++){
            // Count forced matches
            int forced=0, possible=0;
            for(int i=0;i<16;i++){
                if(dom[i].size()==1 && *dom[i].begin()==g[j][i]) forced++;
                if(dom[i].count(g[j][i])) possible++;
            }
            // If forced > M[j], contradiction
            if(forced > M[j]){cout<<"IMPOSSIBLE\n";return 0;}
            // If possible == M[j], all possible ones must match
            if(possible == M[j] && possible > forced){
                for(int i=0;i<16;i++){
                    if(dom[i].count(g[j][i]) && !(dom[i].size()==1 && *dom[i].begin()==g[j][i])){
                        // This position MUST be g[j][i]
                        dom[i].clear(); dom[i].insert(g[j][i]);
                        changed=true;
                    }
                }
            }
            // If forced == M[j], all non-forced positions must NOT match
            if(forced == M[j]){
                for(int i=0;i<16;i++){
                    if(dom[i].size()>1 && dom[i].count(g[j][i])){
                        dom[i].erase(g[j][i]); changed=true;
                    }
                }
            }
        }
    }
    
    // Count remaining domain size (for info)
    int sr = 1;
    for(int i=0;i<16;i++) sr*=dom[i].size();
    
    // Phase 2: backtrack with reduced domains
    string best(16,'?');
    vector<vector<char>> choices(16);
    for(int i=0;i<16;i++) for(char d:dom[i]) choices[i].push_back(d);
    
    function<bool(int)> dfs=[&](int pos)->bool{
        if(pos==16){
            for(int j=0;j<22;j++){
                int c=0; for(int i=0;i<16;i++) if(best[i]==g[j][i]) c++;
                if(c!=M[j]) return false;
            }
            return true;
        }
        for(char d:choices[pos]){
            best[pos]=d;
            // Prune
            bool ok=true;
            for(int j=0;j<22&&ok;j++){
                int cur=0, unk=15-pos;
                for(int i=0;i<=pos;i++) if(best[i]==g[j][i]) cur++;
                int poss=cur;
                for(int i=pos+1;i<16;i++) if(dom[i].count(g[j][i])) poss++;
                if(cur>M[j]||poss<M[j]) ok=false;
            }
            if(ok && dfs(pos+1)) return true;
        }
        return false;
    };
    
    if(dfs(0)) cout<<best<<"\n";
    else cout<<"NOT_FOUND\n";
}
