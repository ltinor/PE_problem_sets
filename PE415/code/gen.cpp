#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll N;
    if (mode == "small") N = 1;
    else if (mode == "large") N = 2;
    else N = atoll(argv[1]);
    cout << N << "\n";
}
