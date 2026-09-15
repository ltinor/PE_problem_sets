#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l,long long r){
    return l + (long long)rand()*rand()%(r-l+1);
}

// 生成一个随机的50位数字
string rand_50digit(){
    string s;
    s += '1' + rand() % 9; // 首位不能为0
    for(int i = 1; i < 50; i++){
        s += '0' + rand() % 10;
    }
    return s;
}

int main(int argc,char* argv[]){
    srand(time(0));

    // 始终生成100个50位数字
    for(int i = 0; i < 100; i++){
        cout << rand_50digit() << "\n";
    }
}
