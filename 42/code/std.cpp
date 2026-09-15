#include<bits/stdc++.h>
using namespace std;

bool is_triangle(int x) {
    // t_k = k*(k+1)/2 = x  =>  k^2 + k - 2x = 0
    // k = (-1 + sqrt(1 + 8x)) / 2
    int disc = 1 + 8 * x;
    int r = (int)sqrt(disc);
    if (r * r != disc) return false;
    return (r - 1) % 2 == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    cin.ignore(); // consume newline after N

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        string word;
        getline(cin, word);

        int val = 0;
        for (char c : word) {
            val += (c - 'A' + 1);
        }
        if (is_triangle(val)) cnt++;
    }

    cout << cnt << "\n";
    return 0;
}
