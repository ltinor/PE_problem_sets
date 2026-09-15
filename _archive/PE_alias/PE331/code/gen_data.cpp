#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p ../data");
    srand(time(0));
    vector<int> tc = {5, 3, 4, 6, 7, 8, 9, 10, 11, 12};
    for (int i = 0; i < 10; i++) {
        char fn[32]; sprintf(fn, "../data/%02d.in", i + 1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
