#include<bits/stdc++.h>
using namespace std;

// 暴力解法：直接使用大整数
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 使用boost::multiprecision::cpp_int来避免溢出
    // 或者使用字符串模拟大整数加法
    string num;
    vector<string> numbers;

    for (int i = 0; i < 100; i++) {
        cin >> num;
        numbers.push_back(num);
    }

    // 计算总和
    string sum = "0";
    for (const string& n : numbers) {
        // 简单的字符串加法
        string result;
        int i = sum.length() - 1;
        int j = n.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int digitSum = carry;
            if (i >= 0) digitSum += sum[i--] - '0';
            if (j >= 0) digitSum += n[j--] - '0';
            result = char(digitSum % 10 + '0') + result;
            carry = digitSum / 10;
        }

        sum = result;
    }

    // 输出前10位
    cout << sum.substr(0, 10) << endl;

    return 0;
}