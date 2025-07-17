#include "TurnoutList.h"

TurnoutList::TurnoutList() : m_list() {}

bool TurnoutList::add(unsigned long turnout) {
    if (!validTurnout(turnout)) {
        return false;
    }
    
    int pos = m_list.insert(m_list.size(), turnout);
    return pos != -1;
}

bool TurnoutList::remove(unsigned long turnout) {
    int pos = m_list.find(turnout);
    return m_list.erase(pos);
}

int TurnoutList::size() const {
    return m_list.size();
}

unsigned long TurnoutList::minimum() const {
    if (m_list.empty()) {
        return NO_TURNOUTS;
    }
    
    unsigned long min_val;
    m_list.get(0, min_val);
    
    for (int i=1; i<m_list.size(); i++) {
        unsigned long curr_val;
        m_list.get(i, curr_val);
        
        if (curr_val < min_val) {
            min_val = curr_val;
        }
    }
    return min_val;
}

unsigned long TurnoutList::maximum() const {
    if (m_list.empty()) {
        return NO_TURNOUTS;
    }
    
    unsigned long max_val;
    m_list.get(0, max_val);
    
    for (int i=1; i<m_list.size(); i++) {
        unsigned long curr_val;
        m_list.get(i, curr_val);
        
        if (curr_val > max_val) {
            max_val = curr_val;
        }
    }
    return max_val;
}
