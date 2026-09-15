#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    system("mkdir -p data");
    // PE348 doesn't take input (fixed problem). Generate a placeholder input.
    vector<ll> tc = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
