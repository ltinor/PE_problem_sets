#include<bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    vector<int> tc = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
}
