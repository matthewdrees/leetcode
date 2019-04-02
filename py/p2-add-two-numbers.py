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
                s += ' -> '
            ln = ln.next
        s += ')'
        return s

def ln2Tuple(listNode):
    
    l = []
    ln = listNode
    while ln != None:
        l.append(ln.val) 
        ln = ln.next
    return tuple(l)

def num2Ln(num):
    '''Convert a number to the reverse ListNode representation.
    >>> num2Ln(342)
    (2 -> 4 -> 3)
    >>> num2Ln(0)
    (0)
    '''
    head = None
    for c in str(num):
        ln = ListNode(int(c))
        ln.next = head
        head = ln
    return head

def ln2num(ln):
    '''Convert a ListNode list to a number.'''
    l = []
    while ln != None:
        l.append(str(ln.val))
        ln = ln.next
    return int(''.join(reversed(l)))

class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        '''My first effort at this, which seemed easy to reason with.'''
        n1 = ln2num(l1)
        n2 = ln2num(l2)
        return num2Ln(n1+n2)

if __name__ == '__main__':
    import doctest
    doctest.testmod()

    s = Solution()
    tests = (
        (342, 465, '(7 -> 0 -> 8)'),
        (0, 0, '(0)'),
        (34, 100, '(4 -> 3 -> 1)'),
        (0, 10, '(0 -> 1)'),
        (20, 9, '(9 -> 2)'),
    )

    for test in tests:

        listNode1Head = num2Ln(test[0])
        listNode2Head = num2Ln(test[1])
        exp = test[2]
        ans = repr(s.addTwoNumbers(listNode1Head, listNode2Head))
        if exp != ans:
            print(f'FAIL. n1: {test[0]}, n2: {test[1]}, exp: "{exp}", ans: "{ans}"')

