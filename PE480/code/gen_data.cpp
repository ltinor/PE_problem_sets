#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    // Test cases: word queries for which we have known positions
    vector<string> tc = {
        "aaaaaacdee",       // W(10), so P = 10
        "euler",            // P = 115246685191495243
        "legionary",        // part of expression
        "calorimeters",     // part of expression
        "annihilate",       // part of expression
        "orchestrated",     // part of expression
        "fluttering"         // part of expression
    };
    for (int i = 0; i < (int)tc.size(); i++) {
        char fn[32];
        sprintf(fn, "data/%02d.in", i+1);
        ofstream f(fn);
        f << tc[i] << "\n";
    }
}
