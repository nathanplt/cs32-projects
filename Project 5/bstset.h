#ifndef BSET_H_
#define BSET_H_

template <typename T>
class BSTSet {
private:
    struct Node {
        T m_data;
        Node* m_left;
        Node* m_right;
        Node* m_parent;
        
        Node(T data, Node* parent = nullptr)
        : m_data(data), m_left(nullptr), m_right(nullptr), m_parent(parent) {}
    };
    
    Node* m_root;
    
    void clearData(Node* curr) {
        if (curr) {
            clearData(curr->m_left);
            clearData(curr->m_right);
            delete curr;
        }
    }

public:
    BSTSet() : m_root(nullptr) {}
    
    ~BSTSet() {
        clearData(m_root);
    }
    
    // Inserts value into the BST
    void insert(const T& value) {
        if (!m_root) {
            m_root = new Node(value);
            return;
        }
        
        Node* p = m_root;
        while (p) {
            if (value < p->m_data) {
                if (p->m_left) {
                    p = p->m_left;
                } else {
                    p->m_left = new Node(value, p);
                    return;
                }
            } else if (p->m_data < value) {
                if (p->m_right) {
                    p = p->m_right;
                } else {
                    p->m_right = new Node(value, p);
                    return;
                }
            } else {
                p->m_data = value;
                return;
            }
        }
    }
    
    class SetIterator {
    public:
        SetIterator(Node* curr) : m_curr(curr) {}
        
        const T* get_and_advance() {
            if (!m_curr) return nullptr;
            
            const T* value = &(m_curr->m_data);
            
            // If we are currently on this node, we should now try searching right
            if (m_curr->m_right) {
                m_curr = m_curr->m_right;
                
                // Once we get to the right node, we must go all the way left (following inorder traversal)
                while (m_curr->m_left) {
                    m_curr = m_curr->m_left;
                }
            } else {
                // If there's nothing to the right, we need to backtrack to the next step
                while (m_curr->m_parent && m_curr == m_curr->m_parent->m_right) {
                    m_curr = m_curr->m_parent;
                }
                m_curr = m_curr->m_parent;
            }
            return value;
        }
    private:
        Node* m_curr;
    };
    
    // Returns iterator equal to value
    SetIterator find(const T& value) const {
        if (!m_root) return SetIterator(nullptr);
        
        Node* p = m_root;
        while (p) {
            if (value < p->m_data) {
                p = p->m_left;
            } else if (p->m_data < value) {
                p = p->m_right;
            } else {
                break;
            }
        }
        
        return SetIterator(p);
    }
    
    // Returns iterator to first node >= value
    SetIterator find_first_not_smaller(const T& value) const {
        Node* p = m_root;
        Node* candidate = nullptr;
        
        while (p) {
            if (p->m_data < value) {
                p = p->m_right;
            } else {
                candidate = p;
                p = p->m_left;
            }
        }
        
        return SetIterator(candidate);
    }
};

#endif // BSET_H_
