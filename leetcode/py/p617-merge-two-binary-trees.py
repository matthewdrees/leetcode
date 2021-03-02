# LeetCode 617. Merge Two Binary Trees.
#
# Imagine that when you put one of them to cover the other, some nodes of the
# two trees are overlapped while the others are not. You need to merge the two
# trees into a new binary tree. The merge rule is that if two nodes overlap,
# then sum node values up as the new value of the merged node. Otherwise, the
# NOT null node will be used as the node of the new tree.
#
# Return the merged tree.
from typing import List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Convert TreeNode tree to a depth-first list.
def to_list(root: TreeNode) -> List:
    if not root:
        return [None]
    return [root.val] + to_list(root.left) + to_list(root.right)


class Solution:
    # Merge two trees into one binary tree.
    #
    # This plunders the nodes from both input trees, and likely changes their
    # values in the process, and can no longer be used/trusted after the call.
    def mergeTrees(self, root1: TreeNode, root2: TreeNode) -> TreeNode:
        if not root1:
            return root2
        if root2:
            root1.val += root2.val
            root1.left = self.mergeTrees(root1.left, root2.left)
            root1.right = self.mergeTrees(root1.right, root2.right)
        return root1


if __name__ == "__main__":
    s = Solution()

    tests = (
        [
            TreeNode(1, TreeNode(3, TreeNode(5)), TreeNode(2)),
            TreeNode(2, TreeNode(1, None, TreeNode(4)), TreeNode(3, None, TreeNode(7))),
            [3, 4, 5, None, None, 4, None, None, 5, None, 7, None, None],
        ],
        [TreeNode(1), TreeNode(1, TreeNode(2)), [2, 2, None, None, None]],
    )
    test_num = 1
    for test in tests:
        root1 = test[0]
        root2 = test[1]
        expected = test[2]
        actual = s.mergeTrees(root1, root2)
        actual_list = to_list(actual)
        if expected != actual_list:
            print("FAIL")
            print(f"expected: {expected}")
            print(f"found: {actual_list}")
