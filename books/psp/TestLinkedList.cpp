// Unit tests.
#include "LinkedList.h"

#include <iostream>

#define FAIL(msg, val)                                                                                      \
    (                                                                                                       \
        (std::cerr << __FILE__ << ":" << __LINE__ << ", FAIL, " << __FUNCTION__ << (msg) << (val) << '\n'), \
        (++num_fails),                                                                                      \
        (void)0)

int main()
{
    struct DataPoint
    {
        int i1;
        int i2;
    };

    int num_fails = 0;

    // Empty list.
    {
        LinkedList<DataPoint> l;
        if (l.size() != 0)
        {
            FAIL("Expected l.size(): 0, found: ", l.size());
        }
    }

    // List with 1 element.
    {
        LinkedList<DataPoint> l;
        DataPoint dp;
        dp.i1 = 1;
        dp.i2 = 2;
        l.push_front(dp);
        if (l.size() != 1)
        {
            FAIL("Expected l.size(): 1, found: ", l.size());
        }
        if (l[0].i1 != 1)
        {
            FAIL("Expected l[0].i1: 1, found: ", l[0].i1);
        }
        if (l[0].i2 != 2)
        {
            FAIL("Expected l[0].i2: 2, found: ", l[0].i2);
        }
    }

    // List with 2 elements.
    {
        LinkedList<DataPoint> l;
        DataPoint dp;
        dp.i1 = 3;
        dp.i2 = 4;
        l.push_front(dp);
        dp.i1 = 1;
        dp.i2 = 2;
        l.push_front(dp);
        if (l.size() != 2)
        {
            FAIL("Expected l.size(): 2, found: ", l.size());
        }
        if (l[1].i1 != 3)
        {
            FAIL("Expected l[1].i1: 3, found: ", l[1].i1);
        }
        if (l[1].i2 != 4)
        {
            FAIL("Expected l[1].i2: 4, found: ", l[1].i2);
        }
    }
    return num_fails == 0 ? 0 : 1;
}
