#include <bits/stdc++.h>
using namespace std;
int main() {
    system("mkdir -p data");
    vector<int> c={1,5,10,20,30,40,50,75,100,200};
    for(int i=0;i<10;i++){
        string f="data/"+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream o(f); o<<c[i]<<"\n";
    }
}
