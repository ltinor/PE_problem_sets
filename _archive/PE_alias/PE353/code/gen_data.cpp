#include<bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    vector<int> tc = {1, 2, 3, 4, 5, 6, 7, 8, 10, 15};
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32]; snprintf(fn, 32, "data/%02d.in", i+1);
        ofstream f(fn); f << tc[i] << "\n";
    }
    return 0;
}
