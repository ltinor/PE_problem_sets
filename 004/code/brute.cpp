#include<bits/stdc++.h>
using namespace std;

bool is_pal(int x) {
    int y = 0, t = x;
    while(t) {
        y = y * 10 + t % 10;
        t /= 10;
    }
    return x == y;
}

int main() {
    int ans = 0;

    for(int i = 100; i <= 999; i++) {
        for(int j = 100; j <= 999; j++) {
            int x = i * j;
            if(is_pal(x)) {
                ans = max(ans, x);
            }
        }
    }

    cout << ans << endl;
}