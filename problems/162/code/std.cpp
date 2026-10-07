#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 162: 容斥原理 + __int128 + 十六进制输出
// 至多D位十六进制数，含0,1,A各至少一次

using i128 = __int128;

i128 ipow(i128 a, int b){
    i128 r = 1;
    while(b){
        if(b & 1) r *= a;
        a *= a;
        b >>= 1;
    }
    return r;
}

// 长度为L的满足条件的个数
i128 count_len(int L){
    // 总: 首非零, 15 * 16^(L-1)  
    i128 total = (i128)15 * ipow(16, L-1);
    // 缺0: 15 * 15^(L-1)
    i128 miss0 = ipow(15, L);
    // 缺1: 14 * 15^(L-1)
    i128 miss1 = (i128)14 * ipow(15, L-1);
    // 缺A: 14 * 15^(L-1)
    i128 missA = (i128)14 * ipow(15, L-1);
    // 缺0和1: 14 * 14^(L-1)
    i128 miss01 = ipow(14, L);
    // 缺0和A: 14 * 14^(L-1)
    i128 miss0A = ipow(14, L);
    // 缺1和A: 13 * 14^(L-1)
    i128 miss1A = (i128)13 * ipow(14, L-1);
    // 缺全部三个: 13 * 13^(L-1)
    i128 missAll = ipow(13, L);

    return total - miss0 - miss1 - missA + miss01 + miss0A + miss1A - missAll;
}

string to_hex(i128 x){
    if(x == 0) return "0";
    string s;
    const char hexc[] = "0123456789ABCDEF";
    while(x > 0){
        s += hexc[x % 16];
        x /= 16;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    i128 ans = 0;
    for(int L=1; L<=D; L++){
        ans += count_len(L);
    }

    cout << to_hex(ans) << "\n";
}
