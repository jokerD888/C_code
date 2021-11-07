#define _CRT_SECURE_NO_WARNINGS 1

//598. 范围求和 II
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<unordered_set>
//法一：模拟,超时
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        vector<vector<int>> ret(m, vector<int>(n,0));
        for (auto v : ops) {
            for(int i=0;i<v[0];i++)
                for (int j = 0; j < v[1]; j++) {
                    ret[i][j]++;
                }
        }
        int maxn = 0, cnt = 0;
        for (auto i : ret) {
            for (auto j : i) {
                if (j > maxn) {
                    maxn = j;
                    cnt = 1;
                } else if (j == maxn) {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

//法二：找规律，每次都是从（0，0）到（m,n)，寻找重叠区域，即找最小a*最小b
class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        int a = m;
        int b = n;
        for (auto i : ops) {

            /* if (i[0] < a)
                a = i[0];
            if (i[1] < b)
                b = i[1];*/
                
            //或
            /*a = i[0] < a ? i[0] : a;
            b = i[1] < b ? i[1] : b;*/

            //或
            a = min(a, i[0]);
            b = min(b, i[1]);

        }
        return a * b;
    }
};


//268. 丢失的数字

//法一：排序，依次递增遍历对照
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int i = 0;
        sort(nums.begin(), nums.end());
        while (i == nums[i]) {
            i++;
            if (i == nums.size())
                break;
        }
        return i;
    }
};

//法二：累加求和,到减去nums所有元素，最后的值即为缺的那个
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long long sum = n * (n + 1) / 2;
        for (auto i : nums) {
            sum -= i;
        }
        return (int)sum;
    }
};

//法三：哈希集合
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        unordered_set<int> set;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            set.insert(nums[i]);
        }
        int missing = -1;
        for (int i = 0; i <= n; i++) {
            if (!set.count(i)) {
                missing = i;
                break;
            }
        }
        return missing;
    }
};

//方法四，位运算
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            res ^= nums[i];
        }
        for (int i = 0; i <= n; i++) {
            res ^= i;
        }
        return res;
    }
};
