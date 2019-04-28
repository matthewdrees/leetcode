class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

    def __repr__(self):
        s = f'('
        ln = self
        while ln != None:
            s += str(ln.val)
            if ln.next != None:
                s += '->'
            ln = ln.next
        s += ')'
        return s


class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        '''Merge two sorted lists in sorted order. Reuses the input nodes.

        The returned list is made up of nodes from the input l1 and l2 lists.
        (The 'next' references in each node are re-assigned.)

        :param l1: first list to merge.
        :param l2: second list to merge.
        :returns: Nodes from l1 and l2 in sorted order.
        '''
        if l1 is None:
            return l2
        elif l2 is None:
            return l1
        if l1.val > l2.val:
            l1, l2 = l2, l1
        n1 = l1
        n2 = l2

        # Look for runs of numbers in each list, then swap the 'next' members.
        while True:
            while n1.next != None and n1.next.val <= n2.val:
                n1 = n1.next
            tmp = n1.next
            n1.next = n2
            if tmp == None:
                break
            else:
                n1 = tmp

            # Swap to look for a run in the other list.
            n1, n2 = n2, n1
        return l1


def tuple2Ln(t):
    '''Convert a tuple of numbers to ListNode representation.
    >>> tuple2Ln(())
    >>> tuple2Ln((1,))
    (1)
    >>> tuple2Ln((1, 2))
    (1->2)
    >>> tuple2Ln((1, 2, 3))
    (1->2->3)
    '''
    head = None
    if len(t) > 0:
        n = t[0]
        head = ListNode(n)
    last = head
    for x in range(1, len(t)):
        n = t[x]
        ln = ListNode(n)
        last.next = ln
        last = ln
    return head


if __name__ == '__main__':
    import doctest
    doctest.testmod()

    s = Solution()
    tests = (
        ((), (), 'None'),
        ((1, ), (), '(1)'),
        ((), (1, ), '(1)'),
        ((1, ), (2, ), '(1->2)'),
        ((2, ), (1, ), '(1->2)'),
        ((1, ), (2, 3), '(1->2->3)'),
        ((2, ), (1, 3), '(1->2->3)'),
        ((3, ), (1, 2), '(1->2->3)'),
        ((1, 2, 4), (1, 3, 4), '(1->1->2->3->4->4)'),
        ((1, 2, 2, 3), (1, 1, 2, 4), '(1->1->1->2->2->2->3->4)'),
    )

    for test in tests:
        ln1 = tuple2Ln(test[0])
        ln2 = tuple2Ln(test[1])
        exp = test[2]
        ans = repr(s.mergeTwoLists(ln1, ln2))
        if exp != ans:
            print(
                f'FAIL. n1: {test[0]}, n2: {test[1]}, exp: "{exp}", ans: "{ans}"'
            )
