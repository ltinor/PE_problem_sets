#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> tests={
        {10, 10},     // sample-like small
        {5, 5},       // tiny
        {20, 10},
        {30, 20},
        {50, 30},
        {75, 50},
        {100, 100},   // max
        {10, 100},    // asymmetric
        {100, 10},    // asymmetric
        {60, 60}
    };

    for(int i=0;i<10;i++){
        string fname=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream f(fname);
        f<<tests[i].first<<" "<<tests[i].second<<"\n";
        f.close();
        cout<<"Generated "<<fname<<" A="<<tests[i].first<<" B="<<tests[i].second<<"\n";
    }
    return 0;
}
