#include<bits/stdc++.h>
using namespace std;

int val(char c){
    if(c>='2'&&c<='9') return c-'0';
    if(c=='T') return 10;
    if(c=='J') return 11;
    if(c=='Q') return 12;
    if(c=='K') return 13;
    return 14;
}

struct Hand{
    vector<int> v,s;
    int rank;
    vector<int> tie;
};

int flush_suit(const vector<int>& suits){
    if(suits[0]==suits[1]&&suits[1]==suits[2]&&suits[2]==suits[3]&&suits[3]==suits[4])
        return suits[0];
    return -1;
}

bool is_straight(vector<int> v){
    sort(v.begin(),v.end());
    if(v[0]+1==v[1]&&v[1]+1==v[2]&&v[2]+1==v[3]&&v[3]+1==v[4]) return true;
    if(v[0]==2&&v[1]==3&&v[2]==4&&v[3]==5&&v[4]==14) return true;
    return false;
}

void evaluate(Hand& h){
    vector<int> cnt(15,0);
    for(int x:h.v) cnt[x]++;

    vector<int> pairs,threes,fours;
    for(int i=14;i>=2;i--){
        if(cnt[i]==4) fours.push_back(i);
        else if(cnt[i]==3) threes.push_back(i);
        else if(cnt[i]==2) pairs.push_back(i);
    }
    sort(fours.rbegin(),fours.rend());
    sort(threes.rbegin(),threes.rend());
    sort(pairs.rbegin(),pairs.rend());
    sort(h.v.rbegin(),h.v.rend());

    bool straight=is_straight(h.v);
    int fs=flush_suit(h.s);

    if(fs!=-1 && straight){
        if(h.v[0]==14 && h.v[1]==13){
            h.rank=9;
            h.tie.clear();
            return;
        }
        h.rank=8;
        if(h.v[0]==14 && h.v[1]==5){
            h.tie={5};
        } else {
            sort(h.v.begin(),h.v.end(),greater<int>());
            h.tie={h.v[0]};
        }
        return;
    }

    if(!fours.empty()){
        h.rank=7;
        int fv=fours[0];
        int k=0;
        for(int x:h.v) if(x!=fv) k=x;
        h.tie={fv,k};
        return;
    }

    if(!threes.empty() && !pairs.empty()){
        h.rank=6;
        h.tie={threes[0],pairs[0]};
        return;
    }

    if(fs!=-1){
        h.rank=5;
        h.tie=h.v;
        return;
    }

    if(straight){
        h.rank=4;
        if(h.v[0]==14 && h.v[1]==5){
            h.tie={5};
        } else {
            sort(h.v.begin(),h.v.end(),greater<int>());
            h.tie={h.v[0]};
        }
        return;
    }

    if(!threes.empty()){
        h.rank=3;
        int tv=threes[0];
        vector<int> ks;
        for(int x:h.v) if(x!=tv) ks.push_back(x);
        sort(ks.rbegin(),ks.rend());
        h.tie={tv};
        for(int k:ks) h.tie.push_back(k);
        return;
    }

    if(pairs.size()==2){
        h.rank=2;
        int p1=max(pairs[0],pairs[1]), p2=min(pairs[0],pairs[1]);
        int k=0;
        for(int x:h.v) if(x!=p1&&x!=p2) k=x;
        h.tie={p1,p2,k};
        return;
    }

    if(pairs.size()==1){
        h.rank=1;
        int pv=pairs[0];
        vector<int> ks;
        for(int x:h.v) if(x!=pv) ks.push_back(x);
        sort(ks.rbegin(),ks.rend());
        h.tie={pv};
        for(int k:ks) h.tie.push_back(k);
        return;
    }

    h.rank=0;
    h.tie=h.v;
}

bool better(Hand& h1, Hand& h2){
    if(h1.rank!=h2.rank) return h1.rank>h2.rank;
    for(size_t i=0;i<min(h1.tie.size(),h2.tie.size());i++){
        if(h1.tie[i]!=h2.tie[i]) return h1.tie[i]>h2.tie[i];
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin>>N;

    int p1_wins=0;
    while(N--){
        vector<string> cards(10);
        for(int i=0;i<10;i++) cin>>cards[i];

        Hand h1,h2;
        for(int i=0;i<5;i++){
            h1.v.push_back(val(cards[i][0]));
            if(cards[i][1]=='S') h1.s.push_back(0);
            else if(cards[i][1]=='H') h1.s.push_back(1);
            else if(cards[i][1]=='D') h1.s.push_back(2);
            else h1.s.push_back(3);
        }
        for(int i=5;i<10;i++){
            h2.v.push_back(val(cards[i][0]));
            if(cards[i][1]=='S') h2.s.push_back(0);
            else if(cards[i][1]=='H') h2.s.push_back(1);
            else if(cards[i][1]=='D') h2.s.push_back(2);
            else h2.s.push_back(3);
        }

        evaluate(h1);
        evaluate(h2);

        if(better(h1,h2)) p1_wins++;
    }

    cout<<p1_wins<<"\n";
}
