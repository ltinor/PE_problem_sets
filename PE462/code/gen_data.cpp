#include<bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    vector<int> tc = {6, 8, 10, 12, 16, 20, 50, 100, 500, 1000};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
