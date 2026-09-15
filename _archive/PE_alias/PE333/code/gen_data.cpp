#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p ../data");
    vector<int> tc = {100, 50, 30, 80, 150, 200, 300, 500, 1000, 2000};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "../data/%02d.in", i + 1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
