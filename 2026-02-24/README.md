# 1022. Sum of Root To Leaf Binary Numbers 🌳🔢

## 🧩 Problem Summary
You are given the `root` of a binary tree where each node has a value of either `0` or `1`. Each root-to-leaf path represents a binary number.

**Goal:** Return the sum of all these binary numbers.

### Example Path:
If a path is `1 → 0 → 1`:
* Binary: `101`
* Decimal: $(1 \times 2^2) + (0 \times 2^1) + (1 \times 2^0) = 5$

---

## 🧠 Key Idea: Bit Manipulation
As we traverse down the tree from the root, we can build the number incrementally. For every new node we visit, we:
1.  **Shift** the existing number to the left by 1 (which is equivalent to multiplying by 2).
2.  **Add** the current node's value (0 or 1) using a bitwise `OR` or addition.

**The Formula:**
$$current\_val = (current\_val \ll 1) \mid node \rightarrow val$$



---

## 🌳 Approach: Depth First Search (DFS)
We use a recursive DFS to explore every path from the root to the leaves.

1.  **Start** at the root with an initial value of `0`.
2.  **Update** the value at each node using the bit manipulation formula.
3.  **Base Case:** If we reach a leaf node (both left and right children are null), return the current accumulated value.
4.  **Recursive Step:** Sum the results from the left and right subtrees.

### 💻 C++ Solution (Recursive)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * TreeNode *left;
 * TreeNode *right;
 * TreeNode() : val(0), left(nullptr), right(nullptr) {}
 * TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int dfs(TreeNode* node, int current) {
        if (!node) return 0;

        // Step 1: Append current bit to the number
        current = (current << 1) | node->val;

        // Step 2: If leaf node, return the completed path value
        if (!node->left && !node->right) {
            return current;
        }

        // Step 3: Accumulate sum from both branches
        return dfs(node->left, current) + dfs(node->right, current);
    }

    int sumRootToLeaf(TreeNode* root) {
        return dfs(root, 0);
    }
};
