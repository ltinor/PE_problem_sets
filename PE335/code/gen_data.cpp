#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p ../data");
    vector<int> tc = {5, 100, 3, 4, 6, 7, 8, 9, 10, 20};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "../data/%02d.in", i + 1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
