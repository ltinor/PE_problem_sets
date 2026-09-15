#include<bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    vector<int> tc = {3, 5, 8, 11, 15, 20, 30, 50, 80, 100};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
