#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases: N M pairs (multiple groups)
    vector<pair<long long,int>> tests={
        {10, 50},        // sample-like
        {100, 10},       // small
        {200, 50},       // small max iter
        {500, 5},        // few iterations
        {1000, 50},      // medium
        {2000, 30},
        {5000, 50},
        {10000, 20},
        {10000, 50},     // max
        {7500, 25}
    };

    for(int i=0;i<10;i++){
        string fname=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream f(fname);
        long long N=tests[i].first;
        int M=tests[i].second;
        f<<N<<" "<<M<<"\n";
        f.close();
        cout<<"Generated "<<fname<<"\n";
    }
    return 0;
}
