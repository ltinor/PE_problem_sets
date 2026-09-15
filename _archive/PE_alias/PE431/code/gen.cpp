#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    if (mode == "pe") cout << "pe\n";
    else if (mode == "large") cout << "test1\n";
    else cout << "small " << (rand()%5+1) << " " << (20+rand()%30) << "\n";
}
