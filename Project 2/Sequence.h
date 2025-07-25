#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence();    // Create an empty sequence (i.e., one whose size() is 0).
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);
    
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    int insert(int pos, const ItemType& value);
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item in position pos and those that
    // follow it end up at positions one greater than they were at before.
    // Return pos if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // e.g., because it's implemented using a fixed-size array.)  Otherwise,
    // leave the sequence unchanged and return -1.  Notice that
    // if pos is equal to size(), the value is inserted at the end.
    
    int insert(const ItemType& value);
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item in position
    // p.  The original item in position p and those that follow it end
    // up at positions one greater than before.  Return p if the value
    // was actually inserted.  Return -1 if the value was not inserted
    // (perhaps because the sequence has a fixed capacity and is full).
    
    bool erase(int pos);
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed that item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the sequence unchanged and return false.
    
    int remove(const ItemType& value);
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item in position pos
    // of the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    
    bool set(int pos, const ItemType& value);
    // If 0 <= pos < size(), replace the item at position pos in the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.
    
    int find(const ItemType& value) const;
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.
    
    void swap(Sequence& other);
    // Exchange the contents of this sequence with the other one.
    
private:
    // A Node object holds a value and a pointer to the previous and next Node
    struct Node {
        ItemType val;
        Node* prev;
        Node* next;
        Node() : prev(nullptr), next(nullptr) {}
        Node(ItemType val) : val(val), prev(nullptr), next(nullptr) {}
    };
    
    Node* m_head; // Sentinel node
    int m_size;
    
    // Helper to get pointer to the node at position pos
    Node* nodeAtPos(int pos) const;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void zipper(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif
