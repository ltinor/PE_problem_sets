#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll mygcd(ll a,ll b){return b?mygcd(b,a%b):a;}

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases, each is a group with T=1
    // We'll generate 10 groups of N,a,b
    vector<tuple<ll,ll,ll>> tests(10);

    // 1: sample from original PE (d<=8, a=3,b=7) -> answer should be 2
    tests[0] = {8, 3, 7};

    // 2-3: small N
    for(int i=1;i<3;i++){
        ll N=rand_ll(10,500);
        ll b,a;
        do{ b=rand_ll(2,N); a=rand_ll(1,b-1); }while(mygcd(a,b)!=1);
        tests[i]={N,a,b};
    }

    // 4-6: medium
    for(int i=3;i<6;i++){
        ll N=rand_ll(1000,50000);
        ll b,a;
        do{ b=rand_ll(2,N); a=rand_ll(1,b-1); }while(mygcd(a,b)!=1);
        tests[i]={N,a,b};
    }

    // 7: edge case N=2
    tests[6]={2,1,2};

    // 8: original PE answer test
    tests[7]={1000000,3,7};

    // 9-10: large random
    for(int i=8;i<10;i++){
        ll N=rand_ll(100000,1000000);
        ll b,a;
        do{ b=rand_ll(2,N); a=rand_ll(1,b-1); }while(mygcd(a,b)!=1);
        tests[i]={N,a,b};
    }

    for(int i=0;i<10;i++){
        string filename=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream fout(filename);
        auto [N,a,b]=tests[i];
        fout<<"1\n"<<N<<" "<<a<<" "<<b<<"\n";
        fout.close();
        cout<<"Generated "<<filename<<" with N="<<N<<" a="<<a<<" b="<<b<<"\n";
    }

    return 0;
}
