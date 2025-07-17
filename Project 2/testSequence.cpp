#include "Sequence.h"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
    // default constructor, empty, and size
    {
        Sequence seq;
        assert(seq.size() == 0); // test size
        assert(seq.empty()); // test empty
    }

    // get and set
    {
        Sequence seq;
        seq.insert(0, "a");
        seq.insert(1, "b");
        seq.insert(2, "c");

        // test get
        std::string s;
        assert(seq.get(0, s) && s == "a");
        assert(seq.get(1, s) && s == "b");
        assert(seq.get(2, s) && s == "c");
        
        // test get out of range
        assert(!seq.get(3, s));
        assert(!seq.get(-1, s));

        // test set
        assert(seq.set(0, "d"));
        assert(seq.set(2, "e"));
        seq.get(0, s); assert(s == "d");
        seq.get(2, s); assert(s == "e");
        
        // test set out of range
        assert(!seq.set(-1, "aaa"));
        assert(!seq.set(999, "bbb"));
    }

    // find
    {
        Sequence seq;
        seq.insert(0, "a");
        seq.insert(1, "b");
        seq.insert(2, "c");
        seq.insert(3, "a");
        seq.insert(4, "b");

        // test if find returns first occurence
        assert(seq.find("a") == 0);
        assert(seq.find("c") == 2);
        assert(seq.find("b") == 1);

        // test if it's not found
        assert(seq.find("g") == -1);
    }

    // insert
    {
        Sequence seq1;
        assert(seq1.insert(0, "a") == 0); // test insert into empty list
        assert(seq1.size() == 1 && !seq1.empty()); // test size and empty

        assert(seq1.insert(0, "b") == 0); // test insert into front of list
        
        assert(seq1.insert(seq1.size(), "c") == 2); // test insert at end

        assert(seq1.insert(1, "d") == 1); // test insert in middle

        // test out of range insert
        assert(seq1.insert(-1, "f") == -1);
        assert(seq1.insert(999, "g") == -1);
        
        Sequence seq2;
        
        // Test if inserting does so in sorted order
        assert(seq2.insert("g") == 0);
        assert(seq2.insert("e") == 0);
        assert(seq2.insert("s") == 2);
        assert(seq2.insert("a") == 0);

        std::string s;
        seq2.get(0, s);
        assert(s == "a");
        seq2.get(1, s);
        assert(s == "e");
        seq2.get(2, s);
        assert(s == "g");
        seq2.get(3, s);
        assert(s == "s");
    }

    // erase and remove
    {
        Sequence seq;
        seq.insert(0, "a");
        seq.insert(1, "b");
        seq.insert(2, "c");
        seq.insert(3, "d");

        assert(seq.erase(0)); // test erasing the first element
        string s;
        seq.get(0, s); assert(s == "b");

        assert(seq.erase(2)); // test erasing the last element
        assert(seq.size() == 2);

        // test erasing out of range
        assert(!seq.erase(2));
        assert(!seq.erase(-1));

        // test remove
        seq.insert("b");
        seq.insert("a");
        seq.insert("b");
        assert(seq.remove("b") == 3);
        assert(seq.size() == 2);
        assert(seq.find("b") == -1);

        assert(seq.remove("a") == 1);
        assert(seq.remove("c") == 1);
        
        // test erase and remove on empty sequence
        assert(seq.remove("s") == 0);
        assert(seq.erase(0) == 0);
    }

    // swap
    {
        Sequence seq1;
        seq1.insert(0, "a");
        seq1.insert(1, "b");
        seq1.insert(2, "c");
        
        Sequence seq2;
        seq2.insert(0, "d");
        seq2.insert(1, "e");
        seq2.insert(2, "f");
        seq2.insert(3, "g");

        seq1.swap(seq2);

        assert(seq1.size() == 4);
        assert(seq2.size() == 3);

        std::string s;
        seq1.get(0, s);  assert(s == "d");
        seq1.get(1, s);  assert(s == "e");
        seq1.get(2, s);  assert(s == "f");
        seq1.get(3, s);  assert(s == "g");
        
        seq2.get(0, s);  assert(s == "a");
        seq2.get(1, s);  assert(s == "b");
        seq2.get(2, s);  assert(s == "c");

        // test swap with empty
        Sequence seq3;
        seq2.swap(seq3);

        assert(seq2.empty());
        assert(seq3.size() == 3);
    }

    // assignment operator and copy constructor
    {
        // test copy
        Sequence seq1;
        seq1.insert(0, "a");
        seq1.insert(1, "b");
        seq1.insert(2, "c");
        seq1.insert(3, "d");

        Sequence seq2(seq1);
        assert(seq2.size() == 4);
        std::string s;
        seq2.get(0, s); assert(s == "a");
        seq2.get(1, s); assert(s == "b");
        seq2.get(2, s); assert(s == "c");
        seq2.get(3, s); assert(s == "d");

        seq1.set(0, "e");
        seq2.get(0, s);
        assert(s == "a");  // test to make sure they aren't aliases

        // test assignemtn
        Sequence seq3;
        seq3.insert(0, "a");
        seq3.insert(1, "b");

        seq3 = seq1; // now s3 is a copy of s1
        assert(seq3.size() == 4);
        seq3.get(0, s); assert(s == "e");
        seq3.get(1, s); assert(s == "b");
        seq3.get(2, s); assert(s == "c");
        seq3.get(3, s); assert(s == "d");
    }

    // subsequence
    {
        Sequence seq1;
        seq1.insert(0, "a");
        seq1.insert(1, "b");
        seq1.insert(2, "c");
        seq1.insert(3, "d");

        Sequence seq2;
        assert(subsequence(seq1, seq2) == -1); // test empty subsequence

        seq2.insert("a");
        seq2.insert("b");
        assert(subsequence(seq1, seq2) == 0); // test first index start
        
        seq2.remove("a");
        seq2.insert("c");
        assert(subsequence(seq1, seq2) == 1); // test middle index start

        seq2.remove("b");
        seq2.insert("a");
        assert(subsequence(seq1, seq2) == -1); // test no match
    }

    // zipper
    {
        // test equal length
        Sequence seq1;
        seq1.insert("a");
        seq1.insert("c");
        seq1.insert("e");
        
        Sequence seq2;
        seq2.insert("b");
        seq2.insert("d");
        seq2.insert("f");

        Sequence zipped;
        zipper(seq1, seq2, zipped);
        assert(zipped.size() == 6);
        std::string s;
        zipped.get(0, s); assert(s == "a");
        zipped.get(1, s); assert(s == "b");
        zipped.get(2, s); assert(s == "c");
        zipped.get(3, s); assert(s == "d");
        zipped.get(4, s); assert(s == "e");
        zipped.get(5, s); assert(s == "f");


        // test seq1 longer
        seq1.insert("g");
        zipper(seq1, seq2, zipped);
        zipped.get(0, s); assert(s == "a");
        zipped.get(1, s); assert(s == "b");
        zipped.get(2, s); assert(s == "c");
        zipped.get(3, s); assert(s == "d");
        zipped.get(4, s); assert(s == "e");
        zipped.get(5, s); assert(s == "f");
        zipped.get(6, s); assert(s == "g");

        // test seq2 longer
        seq2.insert("h");
        seq2.insert("i");
        zipper(seq1, seq2, zipped);
        zipper(seq1, seq2, zipped);
        zipped.get(0, s); assert(s == "a");
        zipped.get(1, s); assert(s == "b");
        zipped.get(2, s); assert(s == "c");
        zipped.get(3, s); assert(s == "d");
        zipped.get(4, s); assert(s == "e");
        zipped.get(5, s); assert(s == "f");
        zipped.get(6, s); assert(s == "g");
        zipped.get(7, s); assert(s == "h");
        zipped.get(8, s); assert(s == "i");
    }
    
    cout << "All tests passed!" << '\n';
}
