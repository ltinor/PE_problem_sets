#include <bits/stdc++.h>
using namespace std;

double eval_rpn(const vector<int>& expr) {
    vector<double> stk;
    for (int tok : expr) {
        if (tok >= 0) {
            stk.push_back((double)tok);
        } else {
            if (stk.size() < 2) return -1e9;
            double b = stk.back(); stk.pop_back();
            double a = stk.back(); stk.pop_back();
            int op = -tok - 1;
            if (op == 0) stk.push_back(a + b);
            else if (op == 1) stk.push_back(a - b);
            else if (op == 2) stk.push_back(a * b);
            else {
                if (fabs(b) < 1e-9) return -1e9;
                stk.push_back(a / b);
            }
        }
    }
    if (stk.size() != 1) return -1e9;
    return stk.back();
}

bool is_int(double x, double eps = 1e-7) {
    double r = round(x);
    return fabs(x - r) < eps && r > 0;
}

void generate_all(const vector<int>& nums, unordered_set<int>& targets) {
    vector<vector<int>> patterns = {
        {0, 1, -1, 2, -2, 3, -3},
        {0, 1, 2, -2, -1, 3, -3},
        {0, 1, -1, 2, 3, -3, -2},
        {0, 1, 2, -2, 3, -3, -1},
        {0, 1, 2, 3, -3, -2, -1}
    };

    vector<vector<int>> perms;
    vector<int> p = nums;
    sort(p.begin(), p.end());
    do { perms.push_back(p); } while (next_permutation(p.begin(), p.end()));

    for (int op1 = 0; op1 < 4; op1++) {
        for (int op2 = 0; op2 < 4; op2++) {
            for (int op3 = 0; op3 < 4; op3++) {
                vector<int> ops = {op1, op2, op3};
                for (auto& perm : perms) {
                    for (auto& pattern : patterns) {
                        vector<int> expr;
                        int op_idx = 0, num_idx = 0;
                        for (int tok : pattern) {
                            if (tok >= 0) expr.push_back(perm[num_idx++]);
                            else expr.push_back(-(ops[op_idx++] + 1));
                        }
                        double val = eval_rpn(expr);
                        if (is_int(val)) targets.insert((int)round(val));
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int best_len = 0, best_abcd = 0;

    for (int a = 0; a <= 9; a++) {
        for (int b = a + 1; b <= 9; b++) {
            for (int c = b + 1; c <= 9; c++) {
                for (int d_ = c + 1; d_ <= 9; d_++) {
                    unordered_set<int> targets;
                    generate_all({a, b, c, d_}, targets);
                    int len = 0;
                    for (int i = 1; ; i++) {
                        if (targets.count(i)) len++;
                        else break;
                    }
                    if (len > best_len) {
                        best_len = len;
                        best_abcd = a * 1000 + b * 100 + c * 10 + d_;
                    }
                }
            }
        }
    }

    cout << best_abcd << "\n";
    return 0;
}
