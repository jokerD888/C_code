
//199. 二叉树的右视图
#include<vector>
#include<stack>
#include<queue>
#include<unordered_map>
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//bfs
//依次找出每层中最右边的元素
//通过记录当前层的最大节点个数，递减直到为0，即可在队列中找到下一层最右边的节点，效率优于下方官解
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root)
            return{};
        vector<int> ans;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        size_t flag = 1;
        while (!nodeQueue.empty()) {
            TreeNode* cur = nodeQueue.front();
            nodeQueue.pop();
            flag--;
        
            if (cur->left)
                nodeQueue.push(cur->left);
            if (cur->right)
                nodeQueue.push(cur->right);
            if (flag == 0) {
                ans.push_back(cur->val);
                flag = nodeQueue.size();
            }
        }

        return ans;
    }
};

//官解
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        unordered_map<int, int> rightmostValueAtDepth;
        int max_depth = -1;

        queue<TreeNode*> nodeQueue;
        queue<int> depthQueue;
        nodeQueue.push(root);
        depthQueue.push(0);

        while (!nodeQueue.empty()) {
            TreeNode* node = nodeQueue.front(); nodeQueue.pop();
            int depth = depthQueue.front(); depthQueue.pop();

            if (node != NULL) {
                // 维护二叉树的最大深度
                max_depth = max(max_depth, depth);

                // 由于每一层最后一个访问到的节点才是我们要的答案，因此不断更新对应深度的信息即可
                rightmostValueAtDepth[depth] = node->val;

                nodeQueue.push(node->left);
                nodeQueue.push(node->right);
                depthQueue.push(depth + 1);
                depthQueue.push(depth + 1);
            }
        }
        vector<int> rightView;
        for (int depth = 0; depth <= max_depth; ++depth) {
            rightView.push_back(rightmostValueAtDepth[depth]);
        }

        return rightView;
    }
};

//dfs
//在搜索过程中，我们总是先访问右子树。那么对于每一层来说，我们在这层见到的第一个结点一定是最右边的结点。
//由于我们无法直接得到树的高度，所以多用一个stack记录节点的层数
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        
        unordered_map<int, int> rightmostValueAtDepth;
        int max_depth = -1;

        stack<TreeNode*> nodeStack;
        stack<int> depthStack;
        nodeStack.push(root);
        depthStack.push(0);

        while (!nodeStack.empty()) {
            TreeNode* node = nodeStack.top(); nodeStack.pop();
            int depth = depthStack.top(); depthStack.pop();

            if (node != NULL) {
                // 维护二叉树的最大深度
                max_depth = max(max_depth, depth);

                // 如果不存在对应深度的节点我们才插入
                if (rightmostValueAtDepth.find(depth) == rightmostValueAtDepth.end()) {
                    rightmostValueAtDepth[depth] = node->val;
                }

                nodeStack.push(node->left);
                nodeStack.push(node->right);
                depthStack.push(depth + 1);
                depthStack.push(depth + 1);
            }
        }

        vector<int> rightView;
        for (int depth = 0; depth <= max_depth; ++depth) {
            rightView.push_back(rightmostValueAtDepth[depth]);
        }

        return rightView;
    }
};
