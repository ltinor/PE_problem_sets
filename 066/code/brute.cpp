#include<bits/stdc++.h>
using namespace std;

struct BigInt {
    static const int BASE = 1000000000;
    vector<int> limbs;

    BigInt() {}
    BigInt(long long val) {
        if (val == 0) limbs.push_back(0);
        while (val > 0) {
            limbs.push_back(val % BASE);
            val /= BASE;
        }
    }

    BigInt operator+(const BigInt& o) const {
        BigInt res;
        int carry = 0;
        int n = max(limbs.size(), o.limbs.size());
        for (int i = 0; i < n || carry; i++) {
            long long sum = carry;
            if (i < (int)limbs.size()) sum += limbs[i];
            if (i < (int)o.limbs.size()) sum += o.limbs[i];
            res.limbs.push_back(sum % BASE);
            carry = sum / BASE;
        }
        return res;
    }

    BigInt operator*(int k) const {
        if (k == 0) return BigInt(0LL);
        BigInt res;
        long long carry = 0;
        for (int i = 0; i < (int)limbs.size() || carry; i++) {
            long long prod = carry;
            if (i < (int)limbs.size()) prod += (long long)limbs[i] * k;
            res.limbs.push_back(prod % BASE);
            carry = prod / BASE;
        }
        return res;
    }

    bool operator<(const BigInt& o) const {
        if (limbs.size() != o.limbs.size())
            return limbs.size() < o.limbs.size();
        for (int i = (int)limbs.size() - 1; i >= 0; i--) {
            if (limbs[i] != o.limbs[i])
                return limbs[i] < o.limbs[i];
        }
        return false;
    }

    bool operator>(const BigInt& o) const {
        return o < *this;
    }
};

pair<BigInt, BigInt> pell(int D) {
    int a0 = (int)sqrt(D);
    if (a0 * a0 == D) return {BigInt(0LL), BigInt(0LL)};

    vector<int> a_seq;
    a_seq.push_back(a0);
    int m = 0, d = 1, a = a0;
    while (a != 2 * a0) {
        m = d * a - m;
        d = (D - m * m) / d;
        a = (a0 + m) / d;
        a_seq.push_back(a);
    }
    int L = (int)a_seq.size() - 1;

    BigInt p_prev2(0LL), p_prev1(1LL);
    BigInt q_prev2(1LL), q_prev1(0LL);

    int total = (L % 2 == 1) ? 2 * L : L;

    for (int i = 0; i < total; i++) {
        int ai = (i == 0) ? a_seq[0] : a_seq[1 + (i - 1) % L];
        BigInt p = p_prev1 * ai + p_prev2;
        BigInt q = q_prev1 * ai + q_prev2;
        p_prev2 = p_prev1;
        p_prev1 = p;
        q_prev2 = q_prev1;
        q_prev1 = q;
    }

    return {p_prev1, q_prev1};
}

BigInt best_x[1001];
int best_D[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BigInt max_x(0LL);
    int max_D_val = 0;

    for (int D = 2; D <= 1000; D++) {
        auto [x, y] = pell(D);
        if (x.limbs.size() == 1 && x.limbs[0] == 0) continue;
        if (x > max_x) {
            max_x = x;
            max_D_val = D;
        }
        best_x[D] = max_x;
        best_D[D] = max_D_val;
    }

    int T;
    cin >> T;
    while (T--) {
        int M;
        cin >> M;
        cout << best_D[M] << "\n";
    }
    return 0;
}
