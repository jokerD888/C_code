//594. 最长和谐子序列
#include<map>
#include<unordered_map>
//map记录数字及其出现次数，根据map自动排序的特征依次进行两两比较，找出差值为1.再进行比较cnt
class Solution {
public:
	int findLHS(vector<int>& nums) {
		map<int, int> hash;
		for (auto i : nums) {
			hash[i]++;
		}
		int cnt = 0;
		pair<int, int> last;
		for (auto m : hash) {
			if (last.second && m.first - last.first == 1 && m.second + last.second > cnt) {
				cnt = m.second + last.second;
			}
			last = m;
		}
		return cnt;
	}
};

//哈希表
class Solution {
public:
	int findLHS(vector<int>& nums) {
		unordered_map<int, int> cnt;
		int res = 0;
		for (int num : nums) {
			cnt[num]++;
		}
		for (auto [key, val] : cnt) {
			if (cnt.count(key + 1)) {
				res = max(res, val + cnt[key + 1]);
			}
		}
		return res;
	}
};

//排序枚举
class Solution {
public:
	int findLHS(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int begin = 0;
		int res = 0;
		for (int end = 0; end < nums.size(); end++) {
			while (nums[end] - nums[begin] > 1) {
				begin++;
			}
			if (nums[end] - nums[begin] == 1) {
				res = max(res, end - begin + 1);
			}
		}
		return res;
	}
};




