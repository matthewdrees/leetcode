"""www.leetcode.com problem 687.

Longest Univalue Path.

Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

The length of path between two nodes is represented by the number of edges between them.

Examples:

Input: [5, 4, 5, 1, 1, 5]         Input: [1, 4, 5, 4, 4, 5]

              5                                 1
             / \                               / \
            4   5                             4   5
           / \   \                           / \   \
          1   1   5                         4   4   5
Output: 2                         Output: 2
"""

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def list_to_treenodes(numbers: [int]):
    """Transform a list of numbers to a TreeNode structure.

    :param numbers: list of numbers
    :return: root of TreeNode binary tree structure
    """
    if len(numbers) == 0:
        return None

    nodes = [TreeNode(val=x) for x in numbers]

    for x in range(len(nodes)):

        left_index = x + x + 1
        if left_index < len(nodes):
            nodes[x].left = nodes[left_index]

        right_index = x + x + 2
        if right_index < len(nodes):
            nodes[x].right = nodes[right_index]

    return nodes[0]


class Solution:
    def __init__(self):
        self.longest_univalue_path = 0

    def do_longest_path(self, root: TreeNode) -> int:
        """Return run of current number."""
        if not root:
            return 0
        left_run_same_val = 0
        if root.left:
            left_run = self.do_longest_path(root.left)
            if root.left.val == root.val:
                left_run_same_val = 1 + left_run

        right_run_same_val = 0
        if root.right:
            right_run = self.do_longest_path(root.right)
            if root.right.val == root.val:
                right_run_same_val = 1 + right_run

        temp_longest_univalue_path = left_run_same_val + right_run_same_val
        if self.longest_univalue_path < temp_longest_univalue_path:
            self.longest_univalue_path = temp_longest_univalue_path

        return max(left_run_same_val, right_run_same_val)

    def longestUnivaluePath(self, root: TreeNode) -> int:

        self.longest_univalue_path = 0
        self.do_longest_path(root)
        return self.longest_univalue_path


if __name__ == "__main__":

    s = Solution()
    tests = (
        ([], 0),
        ([1], 0),
        ([1, 1], 1),
        ([1, 1, 1], 2),
        ([1, 2, 2], 0),
        ([5, 4, 5, 1, 1, 5], 2),
        ([1, 4, 5, 4, 4, 5], 2),
    )

    for test in tests:
        root = list_to_treenodes(test[0])
        exp = test[1]
        ans = s.longestUnivaluePath(root)
        if exp != ans:
            print(f"FAIL. exp: {exp}, ans: {ans}")
