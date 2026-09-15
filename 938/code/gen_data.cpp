#include <bits/stdc++.h>
using namespace std;

int main() {
    system("mkdir -p data");
    srand((unsigned)time(0));
    vector<pair<int,int>> tc(10);
    tc[0] = {2, 2};       // 样例 P=0.4666666667
    tc[1] = {10, 9};      // 样例 P=0.4118903397
    tc[2] = {34, 25};     // 样例 P=0.3665688069
    tc[3] = {1, 1};
    tc[4] = {5, 5};
    tc[5] = {1, 10};
    tc[6] = {10, 1};
    tc[7] = {20, 20};
    tc[8] = {30, 15};
    tc[9] = {200, 100};   // 缩小后的 PE 参数（原 24690,12345）

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tc[i].first << " " << tc[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with R,B = " << tc[i].first << "," << tc[i].second << "\n";
    }
    return 0;
}
