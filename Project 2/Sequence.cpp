#include "Sequence.h"

Sequence::Sequence() : m_head(nullptr), m_size(0) {}

Sequence::~Sequence() {
    // Delete all nodes of sequence, not just head
    Node* p = m_head;
    while (p) {
        Node* nextNode = p->next;
        delete p;
        p = nextNode;
    }
}

Sequence::Sequence(const Sequence& other)
 : m_head(nullptr), m_size(0) {
     // Insert at the end of list for each item
     for (int i=0; i<other.size(); i++) {
         ItemType val;
         other.get(i, val); // get the i-th item from other
         insert(m_size, val); // insert at the end of this list
     }
}

Sequence& Sequence::operator=(const Sequence& other) {
    if (this != &other) {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}

bool Sequence::empty() const {
    return m_size == 0;
}

int Sequence::size() const {
    return m_size;
}

Sequence::Node* Sequence::nodeAtPos(int pos) const {
    if (pos < 0 || pos >= m_size) {
        return nullptr;
    }
    
    Node* p = m_head;
    for (int i=0; i<pos; i++) {
        p = p->next;
    }
    return p;
}

int Sequence::insert(int pos, const ItemType& value) {
    if (pos < 0 || pos > m_size) {
        return -1;
    }
    
    Node* newNode = new Node(value);

    // Inserting at the front
    if (pos == 0) {
        // Case where list is empty
        if (m_size == 0) {
            m_head = newNode;
        } else {
            newNode->next = m_head;
            m_head->prev = newNode;
            m_head = newNode;
        }
    } else {
        // Inserting at the end
        if (pos == m_size) {
            Node* p = nodeAtPos(pos - 1); // Get last node
            p->next = newNode;
            newNode->prev = p;
        } else {
            Node* p = nodeAtPos(pos);
            
            // Create newNode's connections
            newNode->next = p;
            newNode->prev = p->prev;
            
            // Change the previous node's connection
            p->prev->next = newNode;
            
            // Change the current node's connection
            p->prev = newNode;
        }
    }
    
    m_size++;
    return pos;
}

int Sequence::insert(const ItemType& value) {
    Node* p = m_head;
    int pos = 0;
    
    // Find position that satisfies conditions (or simply insert at the end of the list)
    while (p && value > p->val) {
        p = p->next;
        pos++;
    }
    return insert(pos, value);
}

bool Sequence::erase(int pos) {
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    
    Node* currNode = nodeAtPos(pos);
    Node* prevNode = currNode->prev;
    Node* nextNode = currNode->next;
    
    // If the node being erased is the head, prevNode is nullptr, so the new head is nextNode
    if (prevNode == nullptr) {
        m_head = nextNode;
    } else {
        prevNode->next = nextNode;
    }

    // If the erased node isn't the tail, we need to change the prev of the nextNode
    // This works even if prevNode is nullptr, because that would just mean nextNode is the new head
    if (nextNode) {
        nextNode->prev = prevNode;
    }
    
    delete currNode;
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value) {
    int count = 0;
    
    Node* p = m_head;
    int pos = 0;
    while (p) {
        Node* nextNode = p->next;
        
        if (p->val == value) {
            count++;
            erase(pos);
        } else {
            // Only increment pos if a node is erased
            // because if a node is erased, the next node is now in the position of the erased node
            pos++;
        }
        p = nextNode;
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const {
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    value = nodeAtPos(pos)->val;
    return true;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    nodeAtPos(pos)->val = value;
    return true;
}

int Sequence::find(const ItemType& value) const {
    int pos = 0;
    Node* p = m_head;
    
    while (p) {
        if (p->val == value) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    return -1;
}

void Sequence::swap(Sequence& other) {
    Node* tempHead = m_head;
    m_head = other.m_head;
    other.m_head = tempHead;
    
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    // If seq2 is empty, it can't form a subsequence
    if (seq2.empty()) {
        return -1;
    }
    
    // Goes up to seq1.size() - seq2.size() because that is the last index in seq1 with enough room for seq2
    // We don't have to worry about the size being unsigned because we implemented the size functions to return ints
    for (int i=0; i<=seq1.size()-seq2.size(); i++) {
        bool works = true;
        for (int j=0; j<seq2.size(); j++) {
            ItemType val1, val2;
            
            seq1.get(i + j, val1);
            seq2.get(j, val2);
            
            // If any of the corresponding values is not equal, then this subsequence does not work
            if (val1 != val2) {
                works = false;
            }
        }
        
        if (works) {
            return i;
        }
    }
    return -1;
}

void zipper(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    Sequence temp;
    int i = 0;
    int j = 0;
    
    while (i < seq1.size() || j < seq2.size()) {
        ItemType val;
        if (i < seq1.size()) {
            seq1.get(i, val);
            temp.insert(temp.size(), val);
            i++;
        }
        if (j < seq2.size()) {
            seq2.get(j, val);
            temp.insert(temp.size(), val);
            j++;
        }
    }
    
    // Temp holds the zipped sequence, so we can simply copy that into result
    // Whatever is currently stored in result will be copied into temp and destructed
    result.swap(temp);
}
