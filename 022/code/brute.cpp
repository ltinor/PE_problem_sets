#include<bits/stdc++.h>
using namespace std;
#define ll long long

int name_value(const string& s) {
    int sum = 0;
    for (char c : s) {
        sum += (c - 'A' + 1);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> names(N);
    for (int i = 0; i < N; i++) {
        cin >> names[i];
    }

    sort(names.begin(), names.end());

    ll total = 0;
    for (int i = 0; i < N; i++) {
        ll score = (ll)(i + 1) * name_value(names[i]);
        total += score;
    }

    cout << total << "\n";
    return 0;
}
