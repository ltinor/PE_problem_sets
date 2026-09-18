// PE714 数据点: PE 锚点 + 参数化梯度 (K=50000 为 PE 全量点, std 约 7s @12 线程)
// 注: 本环境 MinGW 的 ofstream 会段错误, 故用 C stdio.
#include <cstdio>

int main() {
    long long cases[] = {110, 150, 500, 1000, 5000, 10000, 20000, 50000};
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
