// LeetCode problem 18. Remove Nth Node from End of List.
//
// Given the head of a linked list, remove the nth node from the end of the list and return its head.
//
// Examples:
//     Input: head = [1,2,3,4,5], n = 2
//     Output: [1,2,3,5]
//
//     Input: head = [1], n = 1
//     Output: []
//
//     Input: head = [1,2], n = 1
//     Output: [1]
//
// Constraints:
//  * The number of nodes in the list is sz.
//  * 1 <= sz <= 30
//  * 0 <= Node.val <= 100
//  * 1 <= n <= sz
#include <iostream>
#include <sstream>
#include <vector>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode()
        : val(0)
        , next(nullptr)
    {
    }
    ListNode(int x)
        : val(x)
        , next(nullptr)
    {
    }
    ListNode(int x, ListNode* next)
        : val(x)
        , next(next)
    {
    }
};

void delete_nodes(ListNode* head)
{
    while (head != nullptr) {
        head = std::move(head->next);
    }
}

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (n <= 0 || head == nullptr) {
            return head;
        }

        // Send a scout n nodes ahead.
        ListNode* scout = head;
        for (int x = 0; x < n; ++x) {
            if (scout == nullptr) {
                // n > greater than size of list.
                return head;
            }
            scout = scout->next;
        }

        // Special case for removing head node.
        if (scout == nullptr) {
            ListNode* ret = head->next;
            delete head;
            return ret;
        }

        // Follow along behind the scout.
        scout = scout->next;
        ListNode* prev = head;
        while (scout != nullptr) {
            scout = scout->next;
            prev = prev->next;
        }

        // Remove node.
        ListNode* tmp = prev->next;
        prev->next = prev->next->next;
        delete tmp;

        return head;
    }
};

std::string ln2str(const ListNode* l)
{
    std::ostringstream oss;
    oss << '{';
    while (l != nullptr) {
        oss << l->val << ',';
        l = l->next;
    }
    oss << "\b}";
    return oss.str();
}

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

int test_removeNthFromEnd()
{
    struct TestCase {
        std::vector<int> vals;
        int n;
        std::vector<int> expected;
    };

    TestCase testCases[] = {
        { {}, 1, {} },
        { { 5 }, 0, { 5 } },
        { { 5 }, 1, {} },
        { { 5 }, 2, { 5 } },
        { { 7, 8 }, 0, { 7, 8 } },
        { { 7, 8 }, 1, { 7 } },
        { { 7, 8 }, 2, { 8 } },
        { { 7, 8 }, 3, { 7, 8 } },
        { { 7, 8, 9 }, 0, { 7, 8, 9 } },
        { { 7, 8, 9 }, 1, { 7, 8 } },
        { { 7, 8, 9 }, 2, { 7, 9 } },
        { { 7, 8, 9 }, 3, { 8, 9 } },
        { { 7, 8, 9 }, 4, { 7, 8, 9 } },
    };
    int num_fails = 0;
    Solution s;
    for (const auto& tc : testCases) {
        auto head = vec2Ln(tc.vals);
        const auto actual = s.removeNthFromEnd(head, tc.n);
        auto expected = vec2Ln(tc.expected);

        if (!equals(expected, actual)) {
            ++num_fails;
            auto original_head = vec2Ln(tc.vals);
            std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__
                      << "(vals: " << ln2str(original_head) << ", n: " << tc.n
                      << "), expected: " << ln2str(expected) << ", actual: " << ln2str(actual) << "\n";
            delete_nodes(original_head);
        }
        delete_nodes(head);
        delete_nodes(expected);
    }
    return num_fails;
}

int main()
{
    return test_removeNthFromEnd() == 0 ? 0 : 1;
}
