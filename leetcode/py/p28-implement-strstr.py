"""LeetCode problem 28. Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().


Example 1:
Input: haystack = "hello", needle = "ll"
Output: 2

Example 2:
Input: haystack = "aaaaa", needle = "bba"
Output: -1

Example 3:
Input: haystack = "", needle = ""
Output: 0

Constraints:
* 0 <= haystack.length, needle.length <= 5 * 10⁴
* haystack and needle consist of only lower-case English characters.
"""


class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        for x in range(len(haystack) - len(needle) + 1):
            s1 = haystack[x : x + len(needle)]
            if s1 == needle:
                return x
        return -1


if __name__ == "__main__":

    s = Solution()
    tests = (
        ("hello", "ll", 2),
        ("aaaaa", "bba", -1),
        ("", "", 0),
        ("a", "", 0),
        ("a", "a", 0),
        ("ab", "a", 0),
        ("ab", "b", 1),
        ("aa", "aa", 0),
        ("baa", "aa", 1),
        ("aba", "aa", -1),
    )

    for test in tests:
        haystack = test[0]
        needle = test[1]
        exp = test[2]
        ans = s.strStr(haystack, needle)
        if exp != ans:
            print(
                f"FAIL. haystack: {haystack}, needle: {needle}, exp: {exp}, ans: {ans}"
            )
