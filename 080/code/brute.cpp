#include<bits/stdc++.h>
using namespace std;
#define ll long long

string mul_small(const string &a, int b) {
    if (b == 0) return "0";
    string res;
    int carry = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        int val = (a[i] - '0') * b + carry;
        res += char('0' + (val % 10));
        carry = val / 10;
    }
    while (carry) {
        res += char('0' + (carry % 10));
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string mul20(const string &a) {
    return mul_small(a, 20);
}

string add_small(const string &a, int b) {
    string res;
    int carry = b;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        int val = (a[i] - '0') + carry;
        res += char('0' + (val % 10));
        carry = val / 10;
    }
    while (carry) {
        res += char('0' + (carry % 10));
        carry /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string concat_digit(const string &a, int d) {
    if (a == "0") return to_string(d);
    return a + char('0' + d);
}

int cmp_str(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    }
    return 0;
}

string sub_str(const string &a, const string &b) {
    string res;
    int carry = 0;
    int i = (int)a.size() - 1, j = (int)b.size() - 1;
    while (i >= 0) {
        int va = a[i] - '0' - carry;
        int vb = (j >= 0) ? b[j] - '0' : 0;
        if (va < vb) {
            va += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        res += char('0' + (va - vb));
        i--; j--;
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

string strip_zeros(const string &s) {
    size_t pos = s.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return s.substr(pos);
}

string big_sqrt_digits(int S, int digits) {
    string num = to_string(S) + string(2 * digits, '0');
    if (num.length() % 2 == 1) num = "0" + num;
    
    string result = "0";
    string remainder = "0";
    
    for (size_t i = 0; i < num.length(); i += 2) {
        string bring_down = num.substr(i, 2);
        remainder = strip_zeros(remainder + bring_down);
        
        string twenty_p = mul20(result);
        
        int d = 0;
        for (int trial = 9; trial >= 0; trial--) {
            string candidate = add_small(twenty_p, trial);
            string prod = mul_small(candidate, trial);
            if (cmp_str(prod, remainder) <= 0) {
                d = trial;
                break;
            }
        }
        
        result = concat_digit(result, d);
        string candidate = add_small(twenty_p, d);
        string prod = mul_small(candidate, d);
        remainder = sub_str(remainder, prod);
    }
    
    return strip_zeros(result);
}

int sum_digits(const string &s) {
    int sum = 0;
    for (char c : s) sum += (c - '0');
    return sum;
}

bool is_perfect_square(int n) {
    int r = (int)sqrt(n);
    return r * r == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll total = 0;
    for (int i = 1; i <= N; i++) {
        if (is_perfect_square(i)) continue;
        string digits = big_sqrt_digits(i, 100);
        if (digits.length() > 100) digits = digits.substr(0, 100);
        total += sum_digits(digits);
    }

    cout << total << "\n";

    return 0;
}
