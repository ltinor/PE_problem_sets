#include <bits/stdc++.h>
using namespace std;

// Evaluate an expression given as RPN (reverse Polish notation)
// Each element is either a number (>=0) or an operator: 0=+, 1=-, 2=*, 3=/
double eval_rpn(const vector<int>& expr) {
    vector<double> stk;
    for (int tok : expr) {
        if (tok >= 0) {
            stk.push_back((double)tok);
        } else {
            if (stk.size() < 2) return -1e9;
            double b = stk.back(); stk.pop_back();
            double a = stk.back(); stk.pop_back();
            int op = -tok - 1; // op: -1->0(+), -2->1(-), -3->2(*), -4->3(/)
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

// Check if a value is an integer
bool is_int(double x, double eps = 1e-7) {
    double r = round(x);
    return fabs(x - r) < eps && r > 0;
}

// Generate all RPN expressions for 4 numbers (a,b,c,d) using the 5 bracket structures
// 5 C_n structures for n=4 (Catalan number C_3 = 5)
// Patterns (in terms of operators applied to leaves):
// 1: ((a op1 b) op2 c) op3 d   -> RPN: a b op1 c op2 d op3
// 2: (a op1 (b op2 c)) op3 d   -> RPN: a b c op2 op1 d op3
// 3: (a op1 b) op2 (c op3 d)   -> RPN: a b op1 c d op3 op2
// 4: a op1 ((b op2 c) op3 d)   -> RPN: a b c op2 d op3 op1
// 5: a op1 (b op2 (c op3 d))   -> RPN: a b c d op3 op2 op1

void generate_all(const vector<int>& nums, unordered_set<int>& targets) {
    // 5 RPN patterns
    vector<vector<int>> patterns = {
        {0, 1, -1, 2, -2, 3, -3},           // ((a op1 b) op2 c) op3 d
        {0, 1, 2, -2, -1, 3, -3},           // (a op1 (b op2 c)) op3 d
        {0, 1, -1, 2, 3, -3, -2},           // (a op1 b) op2 (c op3 d)
        {0, 1, 2, -2, 3, -3, -1},           // a op1 ((b op2 c) op3 d)
        {0, 1, 2, 3, -3, -2, -1}            // a op1 (b op2 (c op3 d))
    };

    // 4 numbers
    int a = nums[0], b = nums[1], c = nums[2], d = nums[3];
    
    // 24 permutations
    vector<vector<int>> perms;
    vector<int> p = {a, b, c, d};
    sort(p.begin(), p.end());
    do {
        perms.push_back(p);
    } while (next_permutation(p.begin(), p.end()));

    // 4^3 = 64 operator combinations
    for (int op1 = 0; op1 < 4; op1++) {
        for (int op2 = 0; op2 < 4; op2++) {
            for (int op3 = 0; op3 < 4; op3++) {
                vector<int> ops = {op1, op2, op3}; // 0:+, 1:-, 2:*, 3:/
                
                for (auto& perm : perms) {
                    for (auto& pattern : patterns) {
                        // Build the expression by substituting numbers and ops
                        vector<int> expr;
                        int op_idx = 0;
                        vector<int> nums_avail = perm;
                        int num_idx = 0;
                        
                        for (int tok : pattern) {
                            if (tok >= 0) {
                                expr.push_back(nums_avail[num_idx++]);
                            } else {
                                int op = ops[op_idx++];
                                expr.push_back(-(op + 1)); // encode op as negative: -1, -2, -3, -4
                            }
                        }
                        
                        double val = eval_rpn(expr);
                        if (is_int(val)) {
                            targets.insert((int)round(val));
                        }
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int best_len = 0;
    int best_abcd = 0;

    // C(10,4) = 210 combinations
    for (int a = 0; a <= 9; a++) {
        for (int b = a + 1; b <= 9; b++) {
            for (int c = b + 1; c <= 9; c++) {
                for (int d_ = c + 1; d_ <= 9; d_++) {
                    unordered_set<int> targets;
                    generate_all({a, b, c, d_}, targets);

                    // Find longest consecutive from 1
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
