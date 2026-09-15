#include<bits/stdc++.h>
using namespace std;

int main(){
    system("mkdir -p data");
    srand(time(0));
    
    // 10 test cases for N = 1..9
    vector<int> test_cases(10);
    test_cases[0]=9;  // sample / original PE case
    
    for(int i=1;i<=8;i++)
        test_cases[i]=i+1;  // N=2..9
    
    test_cases[9]=1;
    
    for(int i=0;i<10;i++){
        string filename=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream fout(filename);
        fout<<test_cases[i]<<"\n";
        fout.close();
        cout<<"Generated "<<filename<<" with N="<<test_cases[i]<<"\n";
    }
    
    return 0;
}
