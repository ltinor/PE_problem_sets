// PE009 特殊判题器 (SPJ)
// 用法: spj <input_file> <output_file>
// 输入: 首行 T, 随后 T 行每行一个整数 S (目标周长)
// 合法输出: T 行, 每行一个整数 abc:
//   存在正整数三元组 (a,b,c) 使 a+b+c = S, a^2+b^2 = c^2 且 a*b*c = abc;
//   若无解则输出 0 (判题器会验证确实无解).
// 每个 Pythagorean 三元组 = k x 本原三元组(m,n): a=k(m^2-n^2), b=2kmn, c=k(m^2+n^2),
// 周和 = k*2m(m+n). 注意: 原版枚举漏掉 k>1 的非本原三元组 (如 (9,12,15), S=36), 已修正.
// 实现: 使用 C stdio (本环境 MinGW 的 C++ ifstream 有兼容问题).
// 退出码: 0 = AC, 1 = WA
#include <cstdio>
#include <cstdlib>

typedef long long ll;

// 判定: 存在 k>=1, m>nn>=1 使 a=k(m^2-nn^2), b=k*2m*nn, c=k(m^2+nn^2)
//       满足 a+b+c = S 且 a*b*c = user_ans (user_ans = 0 时判定确实无解)
bool check(ll S, ll user_ans) {
    for (ll m = 2; 2 * m * (m + 1) <= S; m++) {
        for (ll nn = 1; nn < m; nn++) {
            ll prim = 2 * m * (m + nn);
            if (S % prim) continue;
            ll k = S / prim;
            ll a = k * (m * m - nn * nn);
            ll b = k * 2 * m * nn;
            ll c = k * (m * m + nn * nn);
            if (a + b + c != S) continue;
            if (user_ans == 0) return false;        // 选手称无解, 但存在解
            if (a * b * c == user_ans) return true; // 乘积匹配
        }
    }
    return user_ans == 0; // 确实无解 => 输出 0 正确
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: spj <input_file> <output_file>\n");
        return 1;
    }
    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "r");
    if (!fin || !fout) {
        fprintf(stderr, "Cannot open file\n");
        return 1;
    }
    ll T;
    if (fscanf(fin, "%lld", &T) != 1) {
        fprintf(stderr, "Cannot read T\n");
        return 1;
    }
    while (T--) {
        ll S;
        if (fscanf(fin, "%lld", &S) != 1) {
            fprintf(stderr, "Cannot read S\n");
            return 1;
        }
        ll user_ans;
        if (fscanf(fout, "%lld", &user_ans) != 1) {
            fprintf(stderr, "Wrong Answer: cannot read user output\n");
            return 1;
        }
        if (!check(S, user_ans)) {
            fprintf(stderr, "Wrong Answer\n");
            return 1;
        }
    }
    printf("Accepted\n");
    fclose(fin);
    fclose(fout);
    return 0;
}
