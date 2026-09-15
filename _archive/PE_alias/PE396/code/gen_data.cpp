#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    system("mkdir -p data"); srand(time(0));
    vector<ll> tc(10);
    tc[0] = 8;   // ΣG(1..7) = 2517 (PE verify)
    tc[1] = 5;   // G(1..4)
    tc[2] = 10;
    for (int i = 3; i < 6; i++) tc[i] = 2 + rand() % 6;
    tc[6] = 3;   // G(1..2) = G(1)+G(2) = 1+3 = 4
    tc[7] = 12;
    for (int i = 8; i < 10; i++) tc[i] = 4 + rand() % 8;
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i + 1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
