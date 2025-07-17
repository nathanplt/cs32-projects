#include "Sequence.h"

Sequence::Sequence() : m_size(0) {}

bool Sequence::empty() const {
    return m_size == 0;
}

int Sequence::size() const {
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value) {
    if (pos < 0 || pos > m_size || m_size == DEFAULT_MAX_ITEMS) {
        return -1;
    }
    
    for (int i=m_size; i>pos; i--) {
        m_sequence[i] = m_sequence[i-1];
    }
    
    m_sequence[pos] = value;
    m_size++;
    return pos;
}

int Sequence::insert(const ItemType& value) {
    if (m_size == DEFAULT_MAX_ITEMS) {
        return -1;
    }
    
    for (int i=0; i<m_size; i++) {
        if (value <= m_sequence[i]) {
            return insert(i, value);
        }
    }
    
    return insert(m_size, value);
}

bool Sequence::erase(int pos) {
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    
    for (int i=pos; i<m_size-1; i++) {
        m_sequence[i] = m_sequence[i+1];
    }
    
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value) {
    int count = 0;
    for (int i=0; i<m_size; i++) {
        if (m_sequence[i] == value) {
            erase(i);
            count++;
            i--;
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const {
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    
    value = m_sequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    
    m_sequence[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const {
    for (int i=0; i<m_size; i++) {
        if (m_sequence[i] == value) {
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other) {
    Sequence temp = *this;
    *this = other;
    other = temp;
}
