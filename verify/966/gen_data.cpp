#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) * (long long)(rand()) % (r - l + 1);
}

// 生成一个合法三角形 (a,b,c)，满足 1<=a<=b<=c 且 a+b>c
void gen_triangle(long long maxc, long long& a, long long& b, long long& c) {
    do {
        c = rand_ll(2, maxc);
        b = rand_ll(1, c);
        a = rand_ll(1, b);
    } while (a + b <= c);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<tuple<long long, long long, long long>> tc(10);
    long long maxc = 100;  // 缩数据

    // 1-2 样例
    tc[0] = {3, 4, 5};
    tc[1] = {3, 4, 6};

    // 3-8 随机合法三角形
    for (int i = 2; i < 8; i++) {
        long long a, b, c;
        gen_triangle(maxc, a, b, c);
        tc[i] = {a, b, c};
    }

    // 9 等边
    tc[8] = {20, 20, 20};
    // 10 边界：c 接近 a+b
    tc[9] = {49, 50, 98};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << get<0>(tc[i]) << " " << get<1>(tc[i]) << " " << get<2>(tc[i]) << "\n";
        fout.close();
        cout << "Generated " << filename << " : "
             << get<0>(tc[i]) << " " << get<1>(tc[i]) << " " << get<2>(tc[i]) << "\n";
    }
    return 0;
}
