#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读取并忽略输入
    string s; cin >> s;

    // 暴力独立实现：枚举所有排列
    vector<int> nums = {1,2,3,4,5,6,7,8,9,10};
    string best = "";
    
    do {
        int a = nums[0], b = nums[1], c = nums[2], d = nums[3], e = nums[4];
        int f = nums[5], g = nums[6], h = nums[7], i = nums[8], j = nums[9];
        
        int sum = a + f + g;
        if(b + g + h != sum) continue;
        if(c + h + i != sum) continue;
        if(d + i + j != sum) continue;
        if(e + j + f != sum) continue;
        
        int arr[5] = {a, b, c, d, e};
        int minv = arr[0], minp = 0;
        for(int k = 1; k < 5; k++){
            if(arr[k] < minv){ minv = arr[k]; minp = k; }
        }
        
        string cur = "";
        // 顺时针构造
        int p = minp;
        for(int k = 0; k < 5; k++){
            int v0 = arr[p];
            int v1 = nums[5 + p];
            int v2 = nums[5 + (p+1)%5];
            cur += to_string(v0) + to_string(v1) + to_string(v2);
            p = (p + 1) % 5;
        }
        
        if(cur.length() == 16 && cur > best){
            best = cur;
        }
    } while(next_permutation(nums.begin(), nums.end()));
    
    cout << best << "\n";
    return 0;
}
