#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE419 brute: simulate look-and-say sequence

string next_las(const string& s) {
    string res;
    int i = 0, n = s.size();
    while (i < n) {
        char d = s[i];
        int cnt = 1;
        while (i + cnt < n && s[i + cnt] == d) cnt++;
        res += to_string(cnt) + d;
        i += cnt;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s = "1";
    for (int i = 2; i <= n; i++) s = next_las(s);
    ll a = count(s.begin(), s.end(), '1');
    ll b = count(s.begin(), s.end(), '2');
    ll c = count(s.begin(), s.end(), '3');
    cout << a << "," << b << "," << c << "\n";
}
