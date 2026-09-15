#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: 同算法
using i128 = __int128;

i128 ipow(i128 a, int b){
    i128 r = 1;
    while(b){ if(b&1) r*=a; a*=a; b>>=1; }
    return r;
}

i128 count_len(int L){
    i128 total = (i128)15 * ipow(16, L-1);
    i128 miss0 = ipow(15, L);
    i128 miss1 = (i128)14 * ipow(15, L-1);
    i128 missA = (i128)14 * ipow(15, L-1);
    i128 miss01 = ipow(14, L);
    i128 miss0A = ipow(14, L);
    i128 miss1A = (i128)13 * ipow(14, L-1);
    i128 missAll = ipow(13, L);
    return total - miss0 - miss1 - missA + miss01 + miss0A + miss1A - missAll;
}

string to_hex(i128 x){
    if(x == 0) return "0";
    string s;
    const char h[] = "0123456789ABCDEF";
    while(x>0){ s += h[x%16]; x/=16; }
    reverse(s.begin(), s.end());
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int D; cin >> D;
    i128 ans = 0;
    for(int L=1; L<=D; L++) ans += count_len(L);
    cout << to_hex(ans) << "\n";
}
