"""leetcode.com 17, letter combinations of a phone number.

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]

Constraints:
* 0 <= digits.length <= 4
* digits[i] is a digit in the range ['2', '9']
"""

from typing import List

import itertools


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        """Return combinations of phone pad letters based on digits.

        :param digits: string of numbers corresponding to a phone number
        :return: combination of letters
        """
        assert len(digits) <= 4

        if len(digits) == 0:
            return []

        digit_mapping = {
            "2": "abc",
            "3": "def",
            "4": "ghi",
            "5": "jkl",
            "6": "mno",
            "7": "pqrs",
            "8": "tuv",
            "9": "wxyz",
        }

        return [
            "".join(y) for y in itertools.product(*[digit_mapping[d] for d in digits])
        ]


def test_letterCombinations():
    tests = (
        ("", []),
        ("2", ["a", "b", "c"]),
        ("23", ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]),
    )

    s = Solution()
    for t in tests:
        expected = t[1]
        actual = s.letterCombinations(t[0])
        if expected != actual:
            print(f"FAIL. letterCombinations({t[0]}), exp: {expected}, ans: {actual}")


if __name__ == "__main__":
    test_letterCombinations()
