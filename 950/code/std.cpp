#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 950: Pirate Treasure / 海盗宝藏 (simple / reduced version)
//
// n pirates, C identical indivisible coins, bloodthirstiness p = 1/sqrt(m).
// The most senior pirate proposes a distribution; all pirates vote; if at least
// half accept it stands, otherwise the senior walks the plank and the next most
// senior proposes, and so on.
//
// A pirate's happiness = c + p*w  (c = coins he receives, w = total number of
// plank-walkers), or -infinity if he does not survive.
//
// c(n,C,p) = coins of the most senior *surviving* pirate.
// w(n,C,p) = total number of pirates made to walk the plank.
// T(N,C,p) = sum_{n=1..N} ( c(n,C,p) + w(n,C,p) ).
//
// Backward induction:
//   For the n-pirate game, if the senior's proposal is rejected we move to the
//   (n-1)-pirate game with one extra plank.  In that (n-1)-game, the top
//   w(n-1) pirates walk the plank (die, happiness -infinity) and the remaining
//   survivors keep some coins.  Hence, when the n-senior proposes:
//     * doomed pirates (there are w(n-1) of them) vote "yes" for 0 coins
//       (0 > -infinity), giving free votes;
//     * a surviving pirate j accepts iff c_j >= c_{j-1}(n-1) + p*(1+w(n-1)).
//   The senior needs ceil(n/2) votes: his own + the w(n-1) free votes + enough
//   bribed survivors.  Since p = 1/sqrt(m) is irrational the bribe over a
//   fallback of x coins is x + D, where D = floor((1+w)/sqrt(m)) + 1.
//
// We keep only the multiset of coins held by the *survivors* (frequency array)
// and the number w of doomed pirates.

static ll isqrt128(i128 x) {
    if (x < 0) return -1;
    ll r = (ll)sqrtl((long double)x);
    while ((i128)(r + 1) * (r + 1) <= x) ++r;
    while ((i128)r * r > x) --r;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, C, m;
    if (!(cin >> N >> C >> m)) return 0;

    // frequency of coin values (0..C) held by surviving pirates
    vector<ll> freq(C + 1, 0);
    freq[C] = 1;                 // n = 1: lone pirate takes all coins
    ll w = 0;                    // doomed pirates
    ll c = C;                    // c(1)
    ll ans = c + w;              // T includes the n = 1 term

    for (ll n = 2; n <= N; ++n) {
        ll free_votes = 1 + w;             // own vote + doomed pirates
        ll need = (n + 1) / 2;             // ceil(n/2)
        ll votes_to_buy = need - free_votes;

        if (votes_to_buy <= 0) {
            // Enough free votes: the senior keeps everything, nobody walks.
            c = C;
            w = 0;
            fill(freq.begin(), freq.end(), 0);
            freq[C] = 1;
            freq[0] = n - 1;
        } else {
            ll B = 1 + w;                  // planks if this proposal is rejected
            ll D = isqrt128((i128)B * B * m) / m + 1;  // floor(B/sqrt(m)) + 1

            // sum of the votes_to_buy smallest survivor coins
            ll S = 0, rem = votes_to_buy;
            for (ll v = 0; v <= C && rem > 0; ++v) {
                ll take = min(rem, freq[v]);
                S += take * v;
                rem -= take;
            }
            ll total = S + votes_to_buy * D;

            if (total <= C) {
                // Senior survives.
                ll cnew = C - total;
                vector<ll> nf(C + 1, 0);
                nf[C - total] = 1;                  // senior's share
                rem = votes_to_buy;
                for (ll v = 0; v <= C && rem > 0; ++v) {
                    ll take = min(rem, freq[v]);
                    if (take > 0) {
                        nf[v + D] += take;          // bribed survivors
                        rem -= take;
                    }
                }
                nf[0] += (n - 1 - votes_to_buy);    // doomed + unbribed get 0
                freq.swap(nf);
                c = cnew;
                w = 0;
            } else {
                // Senior cannot afford the votes: he walks the plank.
                // Survivors (and their coins) are unchanged; doomed count +1.
                w = 1 + w;
                // c stays the same (most senior survivor unchanged)
            }
        }

        ans += c + w;
    }

    cout << ans << "\n";
    return 0;
}
