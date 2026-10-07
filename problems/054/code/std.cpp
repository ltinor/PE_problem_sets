#include<bits/stdc++.h>
using namespace std;

int val(char c){return c>='2'&&c<='9'?c-'0':c=='T'?10:c=='J'?11:c=='Q'?12:c=='K'?13:14;}
int suit(char c){return c=='S'?0:c=='H'?1:c=='D'?2:3;}

// Returns rank*1000000 + tiebreaker (higher = better hand)
int eval(vector<int> vals, vector<int> suits){
    sort(vals.begin(), vals.end());
    int cnt[15]={0}; for(int v:vals) cnt[v]++;
    
    int pairs=0,three=0,four=0;
    int pair_vals[2]={0};
    for(int v=2;v<=14;v++){
        if(cnt[v]==2){pair_vals[pairs]=v; pairs++;}
        if(cnt[v]==3) three=v;
        if(cnt[v]==4) four=v;
    }
    
    bool flush=1; for(int i=1;i<5;i++) if(suits[i]!=suits[0]) flush=0;
    bool straight=0;
    if(vals[0]+1==vals[1]&&vals[1]+1==vals[2]&&vals[2]+1==vals[3]&&vals[3]+1==vals[4]) straight=1;
    if(vals[0]==2&&vals[1]==3&&vals[2]==4&&vals[3]==5&&vals[4]==14) straight=1; // A-2-3-4-5
    
    int score=0;
    if(straight&&flush&&vals[4]==14) score=9e6+vals[4];          // royal flush
    else if(straight&&flush) score=8e6+vals[4];                   // straight flush
    else if(four) score=7e6+four*100+vals[4];                     // four of kind
    else if(three&&pairs) score=6e6+three*100+pair_vals[0];       // full house
    else if(flush) score=5e6+vals[4]*10000+vals[3]*1000+vals[2]*100+vals[1]*10+vals[0];
    else if(straight) score=4e6+vals[4];
    else if(three) score=3e6+three*10000+vals[4]*100+vals[3];
    else if(pairs==2) score=2e6+max(pair_vals[0],pair_vals[1])*10000+min(pair_vals[0],pair_vals[1])*100+vals[4];
    else if(pairs==1) score=1e6+pair_vals[0]*10000+vals[4]*100+vals[3];
    else score=vals[4]*10000+vals[3]*1000+vals[2]*100+vals[1]*10+vals[0]; // high card
    
    return score;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin>>N;
    int wins=0;
    while(N--){
        vector<int> v1,v2,s1,s2;
        for(int i=0;i<10;i++){
            string c; cin>>c;
            int v=val(c[0]), s=suit(c[1]);
            if(i<5){v1.push_back(v);s1.push_back(s);}
            else{v2.push_back(v);s2.push_back(s);}
        }
        if(eval(v1,s1)>eval(v2,s2)) wins++;
    }
    cout<<wins<<"\n";
}
