#include<bits/stdc++.h>
using namespace std;

// 大整数加法：逐位相加100个50位数字，输出前10位
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sum = "0";

    for (int i = 0; i < 100; i++) {
        string num;
        cin >> num;

        // 大整数加法：sum = sum + num
        string result;
        int p = sum.length() - 1;
        int q = num.length() - 1;
        int carry = 0;

        while (p >= 0 || q >= 0 || carry > 0) {
            int digitSum = carry;
            if (p >= 0) digitSum += sum[p--] - '0';
            if (q >= 0) digitSum += num[q--] - '0';
            result = char(digitSum % 10 + '0') + result;
            carry = digitSum / 10;
        }

        sum = result;
    }

    // 输出前10位数字
    cout << sum.substr(0, 10) << endl;

    return 0;
}
