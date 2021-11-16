//113. 路径总和 II
#include<queue>
 struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
//
////dfs 
//利用深度遍历和回溯，依次遍历到每个叶子，到叶子后比较所走路劲是否等于targetSum
 class Solution {
 public:
     vector<vector<int>> ret;
     vector<int> path;

     void dfs(TreeNode* root, int targetSum) {
         if (root == nullptr) {
             return;
         }
         path.emplace_back(root->val);
         targetSum -= root->val;
         //遍历到叶子节点，并且经过路径符合题目要求
         if (root->left == nullptr && root->right == nullptr && targetSum == 0) {
             //将此路径插入到答案数组
             ret.emplace_back(path);
         }
         dfs(root->left, targetSum);
         dfs(root->right, targetSum);
         path.pop_back();
     }

     vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
         dfs(root, targetSum);
         return ret;
     }
 };

 //bfs
 //利用unordered_map parent记录节点关系，子为key,父为value
 //利用que_sum记录每个节点及其之前路径上的节点value总和，一但遍历到叶子节点，就对照想对于的que_sum于目标数量的大小，进行判断插入
 //由于是从尾到头进行插入，所以在插入ret之前还需对tmp进行翻转
#include<unordered_map>
 class Solution {
 public:
     vector<vector<int>> ret;
     unordered_map<TreeNode*, TreeNode*> parent;

     void getPath(TreeNode* node) {
         vector<int> tmp;
         while (node != nullptr) {
             tmp.emplace_back(node->val);
             node = parent[node];
         }
         reverse(tmp.begin(), tmp.end());
         ret.emplace_back(tmp);
     }

     vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
         if (root == nullptr) {
             return ret;
         }

         queue<TreeNode*> que_node;
         queue<int> que_sum;
         que_node.emplace(root);
         que_sum.emplace(0);

         while (!que_node.empty()) {
             TreeNode* node = que_node.front();
             que_node.pop();
             int rec = que_sum.front() + node->val;
             que_sum.pop();

             if (node->left == nullptr && node->right == nullptr) {
                 if (rec == targetSum) {
                     getPath(node);
                 }
             } else {
                 if (node->left != nullptr) {
                     parent[node->left] = node;
                     que_node.emplace(node->left);
                     que_sum.emplace(rec);
                 }
                 if (node->right != nullptr) {
                     parent[node->right] = node;
                     que_node.emplace(node->right);
                     que_sum.emplace(rec);
                 }
             }
         }
         return ret;
     }
 };

 