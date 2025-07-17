#include "newSequence.h"
#include <iostream>

Sequence::Sequence() : m_size(0), m_capacity(DEFAULT_MAX_ITEMS) {
    m_sequence = new ItemType[m_capacity];
}

Sequence::Sequence(int capacity) : m_size(0), m_capacity(capacity) {
    if (m_capacity < 0) {
        std::cerr << "Capacity must not be negative" << std::endl;
        exit(1);
    }
    
    m_sequence = new ItemType[m_capacity];
}

Sequence::~Sequence() {
    delete [] m_sequence;
}

Sequence::Sequence(const Sequence& other) {
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_sequence = new ItemType(m_capacity);
    
    for (int i=0; i<m_size; i++) {
        m_sequence[i] = other.m_sequence[i];
    }
}

Sequence& Sequence::operator=(const Sequence& other) {
    if (this != &other) {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        
        delete[] m_sequence;
        m_sequence = new ItemType[m_capacity];
        
        for (int i=0; i<m_size; i++) {
            m_sequence[i] = other.m_sequence[i];
        }
    }
    return *this;
}

bool Sequence::empty() const {
    return m_size == 0;
}

int Sequence::size() const {
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value) {
    if (pos < 0 || pos > m_size || m_size == m_capacity) {
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
    if (m_size == m_capacity) {
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
    ItemType* temp_sequence = m_sequence;
    m_sequence = other.m_sequence;
    other.m_sequence = temp_sequence;
    
    int temp_capacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = temp_capacity;
    
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}
