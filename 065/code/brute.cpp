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

    int digit_sum() const {
        int s = 0;
        for (int limb : limbs) {
            while (limb > 0) {
                s += limb % 10;
                limb /= 10;
            }
        }
        return s;
    }
};

BigInt num[101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a(101);
    a[0] = 2;
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 2) a[i] = 2 * (i + 1) / 3;
        else a[i] = 1;
    }

    BigInt p_prev2(1LL);
    BigInt p_prev1(2LL);
    num[1] = p_prev1;

    for (int i = 1; i <= 100; i++) {
        BigInt p_cur = p_prev1 * a[i] + p_prev2;
        if (i + 1 <= 100) num[i + 1] = p_cur;
        p_prev2 = p_prev1;
        p_prev1 = p_cur;
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << num[N].digit_sum() << "\n";
    }
    return 0;
}
