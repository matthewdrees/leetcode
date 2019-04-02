class Solution:
    def maxProfit(self, prices) -> int:
        curLo = 9999999999
        maxProfit = 0
        for price in prices:
            if curLo > price:
                curLo = price
            else:
                profit = price - curLo
                if maxProfit < profit:
                    maxProfit = profit
        return maxProfit


if __name__ == '__main__':

    s = Solution()
    tests = (
        ([], 0),
        ([7], 0),
        ([1, 2], 1),
        ([1, 4, 2], 3),
        ([7, 1, 5, 3, 6, 4], 5),
        ([7, 6, 4, 3, 1], 0),
    )

    for test in tests:

        prices = test[0]
        exp = test[1]
        ans = s.maxProfit(prices)
        if exp != ans:
            print(f'FAIL. prices: {prices}, exp: {exp}, ans: {ans}')
