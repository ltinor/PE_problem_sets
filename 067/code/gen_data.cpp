#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

void gen_triangle(int R, const string& filename){
    ofstream fout(filename);
    fout << R << "\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j <= i; j++){
            if(j > 0) fout << " ";
            fout << rand_int(0, 99);
        }
        fout << "\n";
    }
    fout.close();
}

int main(){
    system("mkdir -p data");
    srand(time(0));

    // 1 样例（题目中的小三角形）
    {
        ofstream fout("data/01.in");
        fout << "4\n";
        fout << "3\n";
        fout << "7 4\n";
        fout << "2 4 6\n";
        fout << "8 5 9 3\n";
        fout.close();
    }

    // 2-3 小数据 R ≤ 10
    for(int i = 1; i <= 2; i++){
        string fn = "data/0" + to_string(i+1) + ".in";
        gen_triangle(rand_int(2, 10), fn);
    }

    // 4-5 中等数据 R ≤ 30
    for(int i = 3; i <= 4; i++){
        string fn = "data/0" + to_string(i+1) + ".in";
        gen_triangle(rand_int(11, 30), fn);
    }

    // 6-8 大数据 R ≤ 100
    for(int i = 5; i <= 7; i++){
        string fn = "data/0" + to_string(i+1) + ".in";
        gen_triangle(rand_int(50, 100), fn);
    }

    // 9 边界：R=2
    gen_triangle(2, "data/09.in");

    // 10 边界：R=100
    gen_triangle(100, "data/10.in");

    cout << "Generated 10 test cases.\n";
    return 0;
}
