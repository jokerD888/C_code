//594. ���г������
#include<map>
#include<unordered_map>
//map��¼���ּ�����ִ���������map�Զ�������������ν��������Ƚϣ��ҳ���ֵΪ1.�ٽ��бȽ�cnt
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

//��ϣ��
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

//����ö��
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




