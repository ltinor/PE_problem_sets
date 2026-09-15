#include<bits/stdc++.h>
using namespace std;
using i128 = __int128;

string to_str(i128 x) {
    if (x == 0) return "0";
    string s;
    while (x) { s += char('0' + (x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<i128,i128>> fracs = {
        {17, 91}, {78, 85}, {19, 51}, {23, 38}, {29, 33},
        {77, 29}, {95, 23}, {77, 19}, {1, 17}, {11, 13},
        {13, 11}, {15, 2}, {1, 7}, {55, 1}
    };

    i128 state = 2, steps = 0;
    int primes_found = 0;

    while (primes_found < N) {
        bool found = false;
        for (auto& f : fracs) {
            if (state % f.second == 0) {
                state = (state / f.second) * f.first;
                found = true;
                break;
            }
        }
        if (!found) { cerr << "STUCK\n"; return 1; }
        steps++;

        i128 s = state;
        int exp = 0;
        while (s > 1 && s % 2 == 0) { s /= 2; exp++; }
        if (s == 1 && exp >= 2) {
            primes_found++;
        }

        if (steps > 500000000LL) {
            cerr << "Timeout\n";
            return 1;
        }
    }

    cout << (long long)steps << "\n";
    return 0;
}
