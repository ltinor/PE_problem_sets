#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    ll N;
    string mode = "small";
    if (argc > 1) mode = argv[1];
    if (mode == "small") N = rand() % 50 + 1;
    else N = rand() % 100000 + 100;
    cout << N << "\n";
    return 0;
}
