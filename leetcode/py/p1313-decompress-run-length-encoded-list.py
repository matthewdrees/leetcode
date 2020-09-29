from typing import List


class Solution:
    def decompressRLElist(self, nums: List[int]) -> List[int]:
        '''Decompressing a run-length encoded list.

        Constraints:
         - 2 <= len(nums) <= 100
         - len(nums) % 2 == 0
         - All values in nums are 1 <= num <= 100

        :param nums: run-length encoded list of numbers.
        :returns: Decompressed list of values.
        '''
        assert len(nums) >= 2 and len(nums) <= 100 and len(nums) % 2 == 0
        for num in nums:
            assert num >= 1 and num <= 100
        decompressedList = []
        for x in range(0, len(nums), 2):
            decompressedList.extend([nums[x + 1]] * nums[x])
        return decompressedList


if __name__ == '__main__':

    s = Solution()
    tests = (
        ([1, 1], [1]),
        ([1, 2], [2]),
        ([2, 1], [1, 1]),
        ([1, 2, 3, 4], [2, 4, 4, 4]),
    )

    for test in tests:
        encodedList = test[0]
        exp = test[1]
        ans = s.decompressRLElist(encodedList)
        if exp != ans:
            print(f'FAIL. encoded list: {encodedList}, exp: {exp}, ans: {ans}')
