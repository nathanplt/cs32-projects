#include <cassert>
#include <iostream>
using namespace std;

bool somePredicate(double x)
{
    return x == 0;
}

// Return true if the somePredicate function returns true for at
// least one of the array elements; return false otherwise.
bool anyTrue(const double a[], int n)
{
    if (n <= 0) {
        return false;
    }
    return somePredicate(a[0]) || anyTrue(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n <= 0) {
        return 0;
    }
    return somePredicate(a[0]) + countTrue(a + 1, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (n <= 0) {
        return -1;
    }
    
    int first = firstTrue(a, n - 1);
    if (first != -1) {
        return first;
    }
    
    if (somePredicate(a[n - 1])) {
        return n - 1;
    }
    return -1;
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told that no doubles are to
// be considered in the array, return -1.
int positionOfMinimum(const double a[], int n)
{
    if (n <= 0) {
        return -1;
    }
    int mn = positionOfMinimum(a, n - 1);
    if (mn == -1 || a[n-1] < a[mn]) {
        mn = n - 1;
    }
    return mn;
}

// If all n1 elements of a1 appear in the n2 element array a2, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 is not a
// not-necessarily-contiguous subsequence of a2), return false.
// (Of course, if a1 is empty (i.e., n1 is 0), return true.)
// For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a1 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a1 is
//    50 30 20
// or
//    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n1 <= 0) {
        return true;
    }
    
    if (n2 <= 0) {
        return false;
    }
    
    if (a1[n1-1] == a2[n2-1]) {
        return isIn(a1, n1 - 1, a2, n2 - 1);
    }
    return isIn(a1, n1, a2, n2 - 1);
}

int main() {
    {
        double a[] = {1, 0, 2};
        assert(anyTrue(a, 3) == true);
        
        double b[] = {1, 1, 2};
        assert(anyTrue(b, 3) == false);
    }
    {
        double a[] = {0, 0, 1, 2};
        assert(countTrue(a, 4) == 2);
        
        double b[] = {1, 0, 1, 0, 1, 0, 1, 0};
        assert(countTrue(b, 8) == 4);
    }
    {
        double a[] = {0, 1, 1, 2};
        assert(firstTrue(a, 4) == 0);
        
        assert(positionOfMinimum(a, 4) == 0);
        double b[] = {1, 2, 0, 3, 4};
        assert(firstTrue(b, 5) == 2);
        assert(positionOfMinimum(b, 5) == 2);

        double c[] = {5, 2, 3, 1, 4};
        assert(firstTrue(c, 5) == -1);
        assert(positionOfMinimum(c, 5) == 3);
    }
    {
        double a[] = {10, 50, 40, 20, 50, 40, 30};
        double b[] = {50, 20, 30};
        assert(isIn(b, 3, a, 7) == true);
        
        double c[] = {50, 40, 40};
        assert(isIn(c, 3, a, 7) == true);
        
        double d[] = {50, 30, 20};
        assert(isIn(d, 3, a, 7) == false);
    }
    cout << "Passed all tests!" << endl;
}
