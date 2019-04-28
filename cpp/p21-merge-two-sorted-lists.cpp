#include <algorithm>
#include <iostream>
#include <vector>

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(nullptr)
    {
    }
};

class Solution
{
public:
    /// Merge two sorted lists in sorted order. Reuses the input nodes.
    ///
    /// The returned list is made up of nodes from the input l1 and l2 lists.
    /// (The 'next' references in each node are re-assigned.)
    ///
    /// \param l1: first list to merge.
    /// \param l2: second list to merge.
    /// \return: Nodes from l1 and l2 in sorted order.
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        if (l1->val > l2->val) {
            std::swap(l1, l2);
        }
        ListNode* n1 = l1;
        ListNode* n2 = l2;

        // Look for runs of numbers in each list, then swap the 'next' pointers.
        while (true) {
            while (n1->next != nullptr && n1->next->val <= n2->val) {
                n1 = n1->next;
            }
            ListNode* tmp = n1->next;
            n1->next = n2;
            if (tmp == nullptr) {
                break;
            }
            n1 = tmp;

            // Swap to look for a run in the other list.
            std::swap(n1, n2);
        }
        return l1;
    }
};

/** Convert a vector of ints to the ListNode representation. */
ListNode* vec2Ln(const std::vector<int>& v)
{
    ListNode* head = nullptr;

    if (!v.empty()) {
        head = new ListNode(v[0]);
        ListNode* last = head;
        for (size_t i = 1; i < v.size(); ++i) {
            last->next = new ListNode(v[i]);
            last = last->next;
        }
    }
    return head;
}

bool equals(const ListNode* l1, const ListNode* l2)
{
    for (; l1 != nullptr && l2 != nullptr; l1 = l1->next, l2 = l2->next) {
        if (l1->val != l2->val) {
            return false;
        }
    }
    return l1 == l2;
}

void dumpLn(const ListNode* l)
{
    for (; l != nullptr; l = l->next) {
        std::cout << l->val << ",";
    }
}

int main(int argc, char* argv[])
{
    struct TestCase {
        std::vector<int> l1;
        std::vector<int> l2;
        std::vector<int> expVec;
    };
    const TestCase testCases[] = {
        { {}, {}, {} },
        { { 1 }, {}, { 1 } },
        { {}, { 1 }, { 1 } },
        { { 1 }, { 2 }, { 1, 2 } },
        { { 2 }, { 1 }, { 1, 2 } },
        { { 1 }, { 2, 3 }, { 1, 2, 3 } },
        { { 2 }, { 1, 3 }, { 1, 2, 3 } },
        { { 3 }, { 1, 2 }, { 1, 2, 3 } },
        { { 1, 2, 4 }, { 1, 3, 4 }, { 1, 1, 2, 3, 4, 4 } },
        { { 1, 2, 2, 3 }, { 1, 1, 2, 4 }, { 1, 1, 1, 2, 2, 2, 3, 4 } },
    };

    Solution s;
    for (const auto& tc : testCases) {
        const auto ans = s.mergeTwoLists(vec2Ln(tc.l1), vec2Ln(tc.l2));
        const auto exp = vec2Ln(tc.expVec);
        if (!equals(exp, ans)) {
            std::cout << "FAIL. l1: ";
            const auto l1 = vec2Ln(tc.l1);
            dumpLn(l1);
            std::cout << " l2: ";
            const auto l2 = vec2Ln(tc.l2);
            dumpLn(l2);
            std::cout << "\n exp: ";
            dumpLn(exp);
            std::cout << "\n ans: \n";
        }
    }
    return 0;
}
