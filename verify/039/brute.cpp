#include<bits/stdc++.h>
using namespace std;

int count_solutions(int P){
    int cnt=0;
    for(int a=1;a<=P/3;a++){
        for(int b=a;b<=(P-a)/2;b++){
            int c=P-a-b;
            if(a*a+b*b==c*c) cnt++;
        }
    }
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MAXP=5000;
    vector<int> cnt(MAXP+1,0);
    for(int p=1;p<=MAXP;p++){
        cnt[p]=count_solutions(p);
    }
    
    vector<int> best(MAXP+1);
    int best_p=0,best_cnt=0;
    for(int p=1;p<=MAXP;p++){
        if(cnt[p]>best_cnt){
            best_cnt=cnt[p];
            best_p=p;
        }
        best[p]=best_p;
    }
    
    int P;
    while(cin>>P){
        cout<<best[P]<<"\n";
    }
    
    return 0;
}
