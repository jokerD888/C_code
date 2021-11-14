
//199. ������������ͼ
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
//�����ҳ�ÿ�������ұߵ�Ԫ��
//ͨ����¼��ǰ������ڵ�������ݼ�ֱ��Ϊ0�������ڶ������ҵ���һ�����ұߵĽڵ㣬Ч�������·��ٽ�
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

//�ٽ�
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
                // ά����������������
                max_depth = max(max_depth, depth);

                // ����ÿһ�����һ�����ʵ��Ľڵ��������Ҫ�Ĵ𰸣���˲��ϸ��¶�Ӧ��ȵ���Ϣ����
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
//�����������У����������ȷ�������������ô����ÿһ����˵���������������ĵ�һ�����һ�������ұߵĽ�㡣
//���������޷�ֱ�ӵõ����ĸ߶ȣ����Զ���һ��stack��¼�ڵ�Ĳ���
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
                // ά����������������
                max_depth = max(max_depth, depth);

                // ��������ڶ�Ӧ��ȵĽڵ����ǲŲ���
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
