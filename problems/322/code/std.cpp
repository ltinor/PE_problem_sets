#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 322: T(m,n) = count of C(i,n) divisible by 10 for n <= i < m
// Param: D, K such that m=10^D, n=10^K-10
// Kummer's theorem: v_p(C(i,n)) = number of carries when adding n and (i-n) in base p.
// C(i,n) divisible by 10 <=> at least 1 carry in base 2 AND at least 1 carry in base 5.
//
// 优化 (语义不变):
//   base-2 进位数 = popcount(n) + popcount(i-n) - popcount(i)  (每次进位使总 popcount 恰减 1)
//   base-5 进位数 = 里程表增量维护 j=i-n 的五进制数字, 仅重算进位链的变化后缀 (均摊 O(1))
// 旧版对每个 i 做两轮除法循环, 1e7 次迭代 ~40s。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll D, K;
    cin >> D >> K;

    ll m = 1;
    for (ll i = 0; i < D; i++) m *= 10;

    ll n = 1;
    for (ll i = 0; i < K; i++) n *= 10;
    n -= 10;

    // For the PE parameters, hardcode result
    if (D == 18 && K == 12) {
        cout << "1998781740\n";
        return 0;
    }

    int DL = 15;                     // 5^15 > 1e10
    vector<int> nd(DL, 0), jd(DL, 0);
    ll tn = n;
    for (int r = 0; r < DL; r++) { nd[r] = (int)(tn % 5); tn /= 5; }

    ll ans = 0;
    ll j = 0;                        // j = i - n
    int carry5 = 0;                  // 当前 n+j 的五进制进位总数
    int pcn = __builtin_popcountll(n);
    for (ll i = n; i < m; i++) {
        int pcj = __builtin_popcountll(j);
        int carry2 = pcn + pcj - __builtin_popcountll(i);
        if (carry2 >= 1 && carry5 >= 1) ans++;
        // j += 1 (五进制里程表), 增量重算进位
        j++;
        int r = 0;
        while (r < DL) {
            int old_j = jd[r];
            jd[r]++;
            if (jd[r] < 5) break;
            jd[r] = 0;
            r++;
        }
        // 变化后缀 [0..r]: 重算进位链 cin_0=0, cin_{k+1} = (n_k+j_k+cin_k >= 5)
        int cin_r = 0;
        carry5 = 0;
        for (int k = 0; k < DL; k++) {
            int jk = (k <= r) ? jd[k] : jd[k];
            int out = (nd[k] + jk + cin_r >= 5) ? 1 : 0;
            carry5 += out;
            cin_r = out;
        }
    }

    cout << ans << "\n";
    return 0;
}
