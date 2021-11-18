
//563. 二叉树的坡度
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};

//dfs
//使用深度优先搜索，在遍历每个结点时，累加其左子树结点之和与右子树结点之和的差的绝对值，并返回以其为根结点的树的结点之和。

class Solution {
public:
    //记录差值，最后返回
    int cnt = 0;
    int findTilt(TreeNode* root) {
        dfs(root);
        return cnt;
    }


    int dfs(TreeNode* node) {
        if (node == nullptr)
            return 0;
        
        //左右再深入
        int sumLeft = dfs(node->left);
        int sumRight = dfs(node->right);
        cnt += abs(sumLeft - sumRight);
        //返回当前根节点树所有节点之和
        return sumLeft + sumRight + node->val;
    }
};


//75. 颜色分类(荷兰国旗）
//双指针
//通过L,R两个指针维护左右区间的边界，左右边界不断向中间扩充，直到遍历到的元素到达了右区间的边界
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

//官解
// 
//单指针
//第一次for,先排0，第二次for,再排1
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
