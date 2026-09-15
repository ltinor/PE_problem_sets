#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    // 1 样例 (PE 原题 context: N that would give f(N)=420)
    // N = 1328125 (5^1 * 13^2 * 17^3, gives f=420) — actually let's verify:
    // 5≡1(mod4), 13≡1(mod4), 17≡1(mod4)
    // e: 1,2,3 → 2*1+1=3, 2*2+1=5, 2*3+1=7 → 3*5*7=105, f=4*105=420
    test_cases[0] = 1328125;

    // 2-3 小数据
    test_cases[1] = 1;    // f(1)=4
    test_cases[2] = 5;    // f(5)=4*3=12

    // 4-5 中数据
    test_cases[3] = 25;   // 5^2, f=4*(2*2+1)=4*5=20
    test_cases[4] = 65;   // 5*13, f=4*3*3=36

    // 6-7 包含 ≡3 mod 4 素数
    test_cases[5] = 15;   // 3*5, 3≡3→ignored, 5≡1→e=1, f=4*3=12
    test_cases[6] = 100;  // 2^2*5^2, f=4*5=20

    // 8-9 大数
    test_cases[7] = 1000000;
    test_cases[8] = 999999937; // large prime ≡ 1 mod 4? Let me check: 999999937 = ...

    // 10 随机
    test_cases[9] = rand_ll(100000, 1000000000);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
