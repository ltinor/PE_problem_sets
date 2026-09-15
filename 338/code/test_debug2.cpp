#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll G1(ll N) {
    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll p = 1; a * p <= N; p++) {
            ll w = a * p;
            ll maxb = min(N / (p + 1), w / (p + 1));
            ans += maxb;
        }
    }
    return ans;
}
ll G2(ll N) {
    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll p = 2; a * p <= N; p++) {
            ll w = a * p;
            ll maxb = min(N / (p - 1), w / (p - 1));
            ans += maxb;
        }
    }
    return ans;
}
ll O(ll N) {
    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll p = 2; a * p <= N; p++) {
            ll h = a * (p - 1);
            if (h <= N && h <= a * p) ans++;
        }
    }
    return ans;
}
ll D(ll N) {
    ll ans = 0;
    for (ll w = 1; w <= N; w++) {
        for (ll h = 1; h <= w; h++) {
            set<pair<ll,ll>> rects;
            ll raw = 0;
            for (ll a = 1; a * a <= w; a++) {
                if (w % a != 0) continue;
                for (ll aa : {a, w / a}) {
                    ll p = w / aa;
                    if (h % (p + 1) == 0) {
                        ll b = h / (p + 1);
                        if (b > 0) {
                            ll wp = w + aa, hp = h - b;
                            if (hp > 0) {
                                if (wp < hp) swap(wp, hp);
                                if (wp != w || hp != h) { rects.insert({wp, hp}); raw++; }
                            }
                        }
                    }
                    if (p > 1 && h % (p - 1) == 0) {
                        ll b = h / (p - 1);
                        if (b > 0) {
                            ll wp = w - aa, hp = h + b;
                            if (wp > 0) {
                                if (wp < hp) swap(wp, hp);
                                if (wp != w || hp != h) { rects.insert({wp, hp}); raw++; }
                            }
                        }
                    }
                }
            }
            ans += raw - (ll)rects.size();
        }
    }
    return ans;
}

int main() {
    ll N = 10;
    ll g1 = G1(N), g2 = G2(N), om = O(N), dd = D(N);
    printf("G1=%lld G2=%lld O=%lld D=%lld -> %lld\n", g1, g2, om, dd, g1+g2-om-dd);
    
    N = 100;
    g1 = G1(N), g2 = G2(N), om = O(N), dd = D(N);
    printf("N=100: G1=%lld G2=%lld O=%lld D=%lld -> %lld\n", g1, g2, om, dd, g1+g2-om-dd);
    
    // Actual via direct F(w,h)
    ll actual = 0;
    for (ll w = 1; w <= N; w++) {
        for (ll h = 1; h <= w; h++) {
            set<pair<ll,ll>> rects;
            for (ll a = 1; a * a <= w; a++) {
                if (w % a) continue;
                for (ll aa : {a, w/a}) {
                    ll p = w / aa;
                    if (h % (p+1) == 0) {
                        ll b = h / (p+1);
                        if (b > 0) {
                            ll wp = w+aa, hp = h-b;
                            if (hp > 0) {
                                if (wp < hp) swap(wp, hp);
                                if (wp != w || hp != h) rects.insert({wp,hp});
                            }
                        }
                    }
                    if (p > 1 && h % (p-1) == 0) {
                        ll b = h / (p-1);
                        if (b > 0) {
                            ll wp = w-aa, hp = h+b;
                            if (wp > 0) {
                                if (wp < hp) swap(wp, hp);
                                if (wp != w || hp != h) rects.insert({wp,hp});
                            }
                        }
                    }
                }
            }
            actual += rects.size();
        }
    }
    printf("Actual G(%lld) = %lld\n", N, actual);
    return 0;
}
