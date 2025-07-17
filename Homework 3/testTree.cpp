#include <cassert>
#include <iostream>
using namespace std;

// Return the number of ways that all n1 elements of a1 appear in
// the n2 element array a2 in the same order (though not necessarily
// consecutively).  We decree that the empty sequence (i.e. one where
// n1 is 0) appears in a sequence of length n2 in 1 way, even if n2
// is 0.  For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then for this value of a1     the function must return
//    10 20 40                        1
//    10 40 30                        2
//    20 10 40                        0
//    50 40 30                        3
int countIsIn(const double a1[], int n1, const double a2[], int n2)
{
    if (n1 <= 0) {
        return 1;
    }
    
    if (n2 <= 0) {
        return 0;
    }
    
    int count = 0;
    if (a1[0] == a2[0]) {
        count += countIsIn(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    return count + countIsIn(a1, n1, a2 + 1, n2 - 1);
}

// Exchange two doubles
void exchange(double& x, double& y)
{
  double t = x;
  x = y;
  y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
                                     int& firstNotGreater, int& firstLess)
{
  if (n < 0)
      n = 0;

    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator

  firstNotGreater = 0;
  firstLess = n;
  int firstUnknown = 0;
  while (firstUnknown < firstLess)
  {
      if (a[firstUnknown] < separator)
      {
          firstLess--;
          exchange(a[firstUnknown], a[firstLess]);
      }
      else
      {
          if (a[firstUnknown] > separator)
          {
              exchange(a[firstNotGreater], a[firstUnknown]);
              firstNotGreater++;
          }
          firstUnknown++;
      }
  }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    if (n <= 1) {
        return;
    }
    
    int firstNotGreater;
    int firstLess;
    
    double pivot = a[n / 2];
    
    separate(a, n, pivot, firstNotGreater, firstLess);
    
    order(a, firstNotGreater);
    order(a + firstLess, n - firstLess);
}


// Test the countIsIn function.
void testCountIsIn() {
    // a2 is the 7-element array.
    double a2[] = {10, 50, 40, 20, 50, 40, 30};
    int n2 = 7;
    
    {
        double a1[] = {10, 20, 40};
        int n1 = 3;
        int result = countIsIn(a1, n1, a2, n2);
        cout << "countIsIn({10,20,40}) should be 1: " << result << endl;
    }
    {
        double a1[] = {10, 40, 30};
        int n1 = 3;
        int result = countIsIn(a1, n1, a2, n2);
        cout << "countIsIn({10,40,30}) should be 2: " << result << endl;
    }
    {
        double a1[] = {20, 10, 40};
        int n1 = 3;
        int result = countIsIn(a1, n1, a2, n2);
        cout << "countIsIn({20,10,40}) should be 0: " << result << endl;
    }
    {
        double a1[] = {50, 40, 30};
        int n1 = 3;
        int result = countIsIn(a1, n1, a2, n2);
        cout << "countIsIn({50,40,30}) should be 3: " << result << endl;
    }
    {
        // Testing the empty sequence: when n1 == 0, the result should be 1.
        int result = countIsIn(a2, 0, a2, n2);
        cout << "countIsIn(empty sequence) should be 1: " << result << endl;
    }
}

// Test the order function.
void testOrder() {
    // Example array to be sorted into descending order.
    double arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Before order: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    order(arr, n);
    
    cout << "After order (descending): ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // Expected descending order: 9 6 5 5 4 3 2 1 1
}

int main() {
    cout << "Testing countIsIn:" << endl;
    testCountIsIn();
    
    cout << "\nTesting order:" << endl;
    testOrder();
    
    return 0;
}
