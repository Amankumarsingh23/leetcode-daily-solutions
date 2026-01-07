# LeetCode 1339 — Maximum Product of Splitted Binary Tree

**Difficulty:** Medium  
**Topic:** Tree, DFS

---

## Problem Summary

You are given the root of a binary tree.  
By removing **exactly one edge**, the tree splits into two subtrees.

Let:
- `subSum` = sum of one subtree  
- `totalSum - subSum` = sum of the remaining tree  

The product is:

    subSum * (totalSum - subSum)


Return the **maximum possible product**, modulo `1e9 + 7`.

---

## Core Idea

1. **First DFS** → compute the total sum of the tree.
2. **Second DFS** → compute every subtree sum.
3. For every subtree, consider cutting above it and update the maximum product.
4. Apply modulo **only at the end**.

---

## Important Fix (Compilation Issue)

LeetCode already defines a method named `maxProduct`.  
Using the same name for a class variable causes **redefinition errors**.

**Fix:**  
Rename the variable to something else (e.g. `best`).

---

## Corrected C++ Solution (No Redefinition Issue)

```cpp
class Solution {
public:
    static const int MOD = 1e9 + 7;
    long long total = 0;
    long long best = 0;

    // First DFS: compute total sum
    long long computeSum(TreeNode* root) {
        if (!root) return 0;
        return root->val + computeSum(root->left) + computeSum(root->right);
    }

    // Second DFS: compute subtree sums and update answer
    long long dfs(TreeNode* root) {
        if (!root) return 0;

        long long left = dfs(root->left);
        long long right = dfs(root->right);

        long long sub = root->val + left + right;
        best = max(best, sub * (total - sub));

        return sub;
    }

    int maxProduct(TreeNode* root) {
        total = computeSum(root);
        dfs(root);
        return best % MOD;
    }
};


