# LeetCode problem 1028. Recover a Tree From Preorder Traversal.
from typing import List

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# Convert TreeNode tree to a depth-first list.
def to_list(root: TreeNode) -> List:
    if not root:
        return []
    return [root.val] + to_list(root.left) + to_list(root.right)

class Solution:
    def recoverFromPreorder(self, S: str) -> TreeNode:
        if len(S) == 0:
            return None

        dash_index_begin = S.find('-')
        if dash_index_begin < 0:
            return TreeNode(int(S))

        tn = TreeNode(int(S[0:dash_index_begin]))

        dash_index_end = dash_index_begin + 1
        while dash_index_end < len(S) and S[dash_index_end] == '-':
            dash_index_end += 1
        num_dashes = dash_index_end - dash_index_begin

        next_dash_index_begin = -1
        for x in range(dash_index_end, len(S)):
            if S[x] == '-':
                if next_dash_index_begin == -1:
                    next_dash_index_begin = x
            elif next_dash_index_begin >= 0:
                if x - next_dash_index_begin == num_dashes:
                    tn.left = self.recoverFromPreorder(S[dash_index_end:next_dash_index_begin])
                    tn.right = self.recoverFromPreorder(S[x:])
                    return tn
                else:
                    next_dash_index_begin = -1
        tn.left = self.recoverFromPreorder(S[dash_index_end:])
        return tn

tests = (
    ["",[]],
    ["1", [1]],
    ["1-2--3--4-5--6--7",[1,2,3,4,5,6,7]],
    ["1-2--3---4-5--6---7",[1,2,3,4,5,6,7]],
    ["1-401--349---90--88",[1,401,349,90,88]]
)

s = Solution()
for t in tests:
    ans = to_list(s.recoverFromPreorder(t[0]))
    if ans != t[1]:
        print(f"FAIL, {ans} != {t[1]}")
