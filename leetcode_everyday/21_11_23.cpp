
¶þ²æÊ÷µÄ¿í¶È
 struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
#include<queue>

 class Solution {
 public:
     int widthOfBinaryTree(TreeNode* root) {
         if (!root)
             return 0;
         queue<TreeNode*> nodeQueue;
         nodeQueue.push(root);
         int ans = 0;

         while (!nodeQueue.empty()) {
             int size = nodeQueue.size();
             int curLevelSize = 0;
             while (size--) {
                 TreeNode* cur = nodeQueue.front();
                 nodeQueue.pop();
                 if (cur->left) {
                     nodeQueue.push(cur->left);
                 }
                 if (cur->right) {
                     nodeQueue.push(cur->right);
                 }
             }
             ans = max(ans, (int)nodeQueue.size());
         }
         return ans;
     }
 };

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root)
            return 0;
        queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        TreeNode* nodeCurEnd = root;
        TreeNode* nextEnd = nullptr;
        int curLevelNode = 0, ans = 0;

        while (!nodeQueue.empty()) {
            TreeNode* cur = nodeQueue.front();
            nodeQueue.pop();
            curLevelNode++;
            if (cur->left) {
                nodeQueue.push(cur->left);
                nextEnd = cur->left;
            }
            if (cur->right) {
                nodeQueue.push(cur->right);
                nextEnd = cur->right;
            }
            if (cur == nodeCurEnd) {
                ans = max(ans, curLevelNode);
                curLevelNode = 0;
                nodeCurEnd = nextEnd;
                nextEnd = nullptr;
            }
        }
        return ans;

    }
};


int main(void)
{

    TreeNode* root = new TreeNode{ 0 };
    TreeNode* real = root;
    root->left = new TreeNode{ 1 };
    root->right = new TreeNode{ 2 };

    TreeNode* tmp = root->right;
    root = root->left;
    root->left = new TreeNode{ 3 };
    root->right = new TreeNode{ 4 };

    root = tmp;
    root->left = new TreeNode{ 5 };
    root->right = new TreeNode{ 6 };
    root = real;
    
    Solution s;
    cout<<s.widthOfBinaryTree(root);


    return 0;
}
