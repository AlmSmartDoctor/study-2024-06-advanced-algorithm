/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#define pii pair<int, int>
#define fi first
#define se second
class Solution {
public:


    pii get(TreeNode* root){
        if(root==0)return {0,0};
        auto [l0,l1]=get(root->left);
        auto [r0,r1]=get(root->right);
        int v0=l1+r1+(root->val);
        int v1=l0+r0;
        v0=max(v0,v1);
        return {v0,v1};
    }

    int rob(TreeNode* root) {
        auto [v0,v1]=get(root);
        return max(v0,v1);
    }
};