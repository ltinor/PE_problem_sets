#include<bits/stdc++.h>
using namespace std;

int rand_int(int l,int r){
    return l+rand()%(r-l+1);
}

int main(){
    system("mkdir -p data");
    srand(time(0));
    
    vector<int> test_cases(10);
    
    // 1: sample, p=120 (3 solutions)
    test_cases[0]=120;
    
    // 2-3: small
    test_cases[1]=rand_int(10,100);
    test_cases[2]=rand_int(100,300);
    
    // 4-5: medium
    test_cases[3]=rand_int(300,800);
    test_cases[4]=rand_int(800,1500);
    
    // 6-7: large
    test_cases[5]=rand_int(1500,3000);
    test_cases[6]=rand_int(3000,4500);
    
    // 8: boundary max
    test_cases[7]=5000;
    
    // 9-10: random
    test_cases[8]=rand_int(1,5000);
    test_cases[9]=rand_int(1,5000);
    
    for(int i=0;i<10;i++){
        string filename=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";
        ofstream fout(filename);
        fout<<test_cases[i]<<"\n";
        fout.close();
        cout<<"Generated "<<filename<<" with P="<<test_cases[i]<<"\n";
    }
    
    return 0;
}
