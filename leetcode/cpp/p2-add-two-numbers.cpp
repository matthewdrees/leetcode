// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(NULL)
    {
    }
};

/** Convert a number to the reverse ListNode representation. */
ListNode* num2Ln(int num)
{
    ListNode* head = nullptr;
    for
        c in str(num)
            : ln = ListNode(int(c))
                       ln.next
            = head
                head
            = ln return head
}

/** Convert a ListNode list to a number. */
int ln2num(ListNode* head)
{
    l = [] while ln != None : l.append(str(ln.val)) ln = ln.next return int(''.join(reversed(l)))
}

class Solution : def addTwoNumbers(self, l1
                                   : ListNode, l2
                                   : ListNode)
                     ->ListNode :
        '''My first effort at this, which seemed easy to reason with.''' n1 = ln2num(l1)
    n2 = ln2num(l2) return num2Ln(n1 + n2)

        class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        const int n1 = ln2num(l1);
        const int n2 = ln2num(l2);
    }
};
