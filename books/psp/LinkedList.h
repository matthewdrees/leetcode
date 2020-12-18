// Generic singly-linked list class.
//
// Used for PSP exercises. (Caution: Never use.)

#include <cassert>
template <class T>
struct Node
{
    T t;
    Node<T> *next;
};

template <class T>
class LinkedList
{
    Node<T> *head;

public:
    LinkedList() noexcept : head(nullptr) {}
    ~LinkedList() noexcept
    {
        while (head != nullptr)
        {
            Node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void push_front(const T &t)
    {
        Node<T> *n = new Node<T>;
        n->t = t;
        n->next = head;
        head = n;
    }
    // Get the number of nodes in this linked list.
    // Note: Terrible. This was faster than figuring out how to do a custom iterator.
    std::size_t size() const noexcept
    {
        std::size_t num = 0;
        Node<T> *n = head;
        while (n != nullptr)
        {
            n = n->next;
            num += 1;
        }
        return num;
    }

    // Index operator.
    // Note: Terrible. This was faster than figuring out how to do a custom iterator.
    const T &operator[](std::size_t idx) const
    {
        assert(idx < size());
        Node<T> *n = head;
        for (; idx-- > 0;)
        {
            n = n->next;
        }
        return n->t;
    }
};
