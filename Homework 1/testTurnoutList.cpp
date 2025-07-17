#include "TurnoutList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    TurnoutList t;
    assert(t.size() == 0);

    assert(t.add(1001));
    assert(t.add(1234));
    assert(t.add(0));
    assert(t.add(134));
    assert(t.add(535));
    assert(t.add(1800));
    
    assert(!t.add(2232));
    assert(t.size() == 6);

    assert(t.minimum() == 0);
    assert(t.maximum() == 1800);

    assert(t.remove(1001));
    assert(!t.remove(2433));
    assert(t.remove(1234));
    assert(!t.remove(1234));
    assert(t.size() == 4);

    cout << "Passed all tests for TurnoutList" << endl;
    return 0;
}
