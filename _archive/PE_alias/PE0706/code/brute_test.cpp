#include <bits/stdc++.h>
using namespace std;

int f_of_n(long long n) {
    string s = to_string(n);
    int d = s.size();
    vector<int> pref(d + 1, 0);
    for (int i = 0; i < d; i++) {
        pref[i+1] = (pref[i] + (s[i] - '0')) % 3;
    }
    int cnt[3] = {};
    for (int i = 0; i <= d; i++) cnt[pref[i]]++;
    return cnt[0]*(cnt[0]-1)/2 + cnt[1]*(cnt[1]-1)/2 + cnt[2]*(cnt[2]-1)/2;
}

int main() {
    for (int D = 1; D <= 6; D++) {
        long long start = 1;
        for (int i = 1; i < D; i++) start *= 10;
        long long end = start * 10;
        int cnt = 0;
        for (long long n = start; n < end; n++) {
            if (f_of_n(n) % 3 == 0) cnt++;
        }
        cout << "F(" << D << ") = " << cnt << endl;
    }
    return 0;
}
