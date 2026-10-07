#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

string rand_50digit(){
    string s;
    s += '1' + rand() % 9;
    for(int i = 1; i < 50; i++){
        s += '0' + rand() % 10;
    }
    return s;
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    for(int t = 0; t < 10; t++){
        string filename = string("data/") + (t < 9 ? "0" : "") + to_string(t + 1) + ".in";
        ofstream fout(filename);

        // 每个测试用例固定100行
        for(int i = 0; i < 100; i++){
            fout << rand_50digit() << "\n";
        }
        fout.close();
        cout << "Generated " << filename << "\n";
    }

    return 0;
}
