#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));
    
    // 10 test cases
    vector<pair<int,vector<int>>> test_cases(10);
    
    // 1: original PE problem
    test_cases[0]={7,{1,10,100,1000,10000,100000,1000000}};
    
    // 2-3: simple small
    test_cases[1]={1,{1}};
    test_cases[2]={2,{1,10}};
    
    // 4-6: medium
    test_cases[3]={3,{5,50,500}};
    test_cases[4]={3,{12,100,999}};
    test_cases[5]={4,{1,100,1000,10000}};
    
    // 7-8: boundary
    test_cases[6]={1,{1000000}};
    test_cases[7]={2,{1,1000000}};
    
    // 9-10: random
    test_cases[8]={5,{7,77,777,7777,77777}};
    test_cases[9]={6,{9,99,999,9999,99999,999999}};
    
    for(int i=0;i<10;i++){
        string filename=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream fout(filename);
        fout<<test_cases[i].first;
        for(int p:test_cases[i].second)
            fout<<" "<<p;
        fout<<"\n";
        fout.close();
        cout<<"Generated "<<filename<<" with K="<<test_cases[i].first<<"\n";
    }
    
    return 0;
}
