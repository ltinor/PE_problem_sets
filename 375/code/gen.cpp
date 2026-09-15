#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    ll N;
    if (mode == "small") N = rand() % 200 + 1;
    else N = rand() % 1000000 + 1000;
    cout << N << "\n";
    return 0;
}
