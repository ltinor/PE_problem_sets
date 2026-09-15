#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p ../data");
    vector<int> tc = {14, 1, 2, 3, 5, 7, 10, 12, 15, 20};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "../data/%02d.in", i + 1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
