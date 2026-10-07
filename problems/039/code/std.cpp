#include<bits/stdc++.h>
using namespace std;

int gcd(int a,int b){
    while(b){int t=a%b;a=b;b=t;}
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int MAXP=5000;
    vector<int> cnt(MAXP+1,0);
    
    // Euclid's formula
    for(int m=2;m*m<=MAXP;m++){
        for(int n=1;n<m;n++){
            if((m-n)%2==0) continue;
            if(gcd(m,n)!=1) continue;
            int a=m*m-n*n;
            int b=2*m*n;
            int c=m*m+n*n;
            int p=a+b+c;
            for(int k=1;k*p<=MAXP;k++){
                cnt[k*p]++;
            }
        }
    }
    
    // prefix best: for each p, which p'<=p has max count
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
