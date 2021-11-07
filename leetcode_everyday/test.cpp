#define _CRT_SECURE_NO_WARNINGS 1

//598. ��Χ��� II
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<unordered_set>
//��һ��ģ��,��ʱ
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

//�������ҹ��ɣ�ÿ�ζ��Ǵӣ�0��0������m,n)��Ѱ���ص����򣬼�����Сa*��Сb
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
                
            //��
            /*a = i[0] < a ? i[0] : a;
            b = i[1] < b ? i[1] : b;*/

            //��
            a = min(a, i[0]);
            b = min(b, i[1]);

        }
        return a * b;
    }
};


//268. ��ʧ������

//��һ���������ε�����������
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

//�������ۼ����,����ȥnums����Ԫ�أ�����ֵ��Ϊȱ���Ǹ�
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

//��������ϣ����
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

//�����ģ�λ����
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
