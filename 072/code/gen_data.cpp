#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> tests(10);

    // 1: sample d<=8 -> answer is 21
    tests[0] = 8;

    // 2-3: small
    for(int i=1;i<3;i++) tests[i]=rand_ll(2,500);

    // 4-6: medium
    for(int i=3;i<6;i++) tests[i]=rand_ll(1000,50000);

    // 7: min
    tests[6]=2;

    // 8: original PE answer test
    tests[7]=1000000;

    // 9-10: large random
    for(int i=8;i<10;i++) tests[i]=rand_ll(100000,1000000);

    for(int i=0;i<10;i++){
        string filename=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream fout(filename);
        fout<<"1\n"<<tests[i]<<"\n";
        fout.close();
        cout<<"Generated "<<filename<<" with N="<<tests[i]<<"\n";
    }

    return 0;
}
