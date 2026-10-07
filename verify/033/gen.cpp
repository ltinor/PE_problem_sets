#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    // Answer is always 100, just generate dummy input
    int t = 1 + rand() % 100;
    cout << t << "\n";
}
