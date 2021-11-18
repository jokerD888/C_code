
//563. ���������¶�
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};

//dfs
//ʹ����������������ڱ���ÿ�����ʱ���ۼ������������֮�������������֮�͵Ĳ�ľ���ֵ������������Ϊ���������Ľ��֮�͡�

class Solution {
public:
    //��¼��ֵ����󷵻�
    int cnt = 0;
    int findTilt(TreeNode* root) {
        dfs(root);
        return cnt;
    }


    int dfs(TreeNode* node) {
        if (node == nullptr)
            return 0;
        
        //����������
        int sumLeft = dfs(node->left);
        int sumRight = dfs(node->right);
        cnt += abs(sumLeft - sumRight);
        //���ص�ǰ���ڵ������нڵ�֮��
        return sumLeft + sumRight + node->val;
    }
};


//75. ��ɫ����(�������죩
//˫ָ��
//ͨ��L,R����ָ��ά����������ı߽磬���ұ߽粻�����м����䣬ֱ����������Ԫ�ص�����������ı߽�
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int i = 0, L = 0, R = nums.size() - 1;
		while (i <= R) {
			if (nums[i] > 1) {
				swap(nums[i], nums[R--]);
			} else if (nums[i] < 1) {
				swap(nums[i++], nums[L++]);
			} else {
				i++;
			}
		}
	}
};

//�ٽ�
// 
//��ָ��
//��һ��for,����0���ڶ���for,����1
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int ptr = 0;
		for (int i = 0; i < n; ++i) {
			if (nums[i] == 0) {
				swap(nums[i], nums[ptr]);
				++ptr;
			}
		}
		for (int i = ptr; i < n; ++i) {
			if (nums[i] == 1) {
				swap(nums[i], nums[ptr]);
				++ptr;
			}
		}
	}
};



class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int p0 = 0, p1 = 0;
		for (int i = 0; i < n; ++i) {
			if (nums[i] == 1) {
				swap(nums[i], nums[p1]);
				++p1;
			} else if (nums[i] == 0) {
				swap(nums[i], nums[p0]);
				if (p0 < p1) {
					swap(nums[i], nums[p1]);
				}
				++p0;
				++p1;
			}
		}
	}
};

class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int p0 = 0, p2 = n - 1;
		for (int i = 0; i <= p2; ++i) {
			while (i <= p2 && nums[i] == 2) {
				swap(nums[i], nums[p2]);
				--p2;
			}
			if (nums[i] == 0) {
				swap(nums[i], nums[p0]);
				++p0;
			}
		}
	}
};
