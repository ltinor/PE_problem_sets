#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    if (mode == "pe") cout << "5000000\n";
    else if (mode == "large") cout << "2000\n";
    else cout << (1 + rand() % 200) << "\n";
}
