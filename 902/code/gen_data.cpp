// PE902 数据点: 题面锚点 2/3/4 + 梯度 (100 即 PE 点, 闭式算法瞬时)
// 注: 本环境 MinGW 的 ofstream 会段错误, 用 C stdio.
#include <cstdio>
int main() {
    long long cases[] = {2, 3, 4, 5, 10, 50, 100};
    int n = sizeof(cases) / sizeof(cases[0]);
    for (int i = 0; i < n; i++) {
        char fn[64];
        snprintf(fn, sizeof(fn), "data/%02d.in", i + 1);
        FILE* f = fopen(fn, "w");
        if (!f) return 1;
        fprintf(f, "%lld\n", cases[i]);
        fclose(f);
    }
    return 0;
}
