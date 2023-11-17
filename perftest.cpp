#include <assert.h>
#include <iostream>
#include <chrono>
using std::cout;
using std::ostream;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

#define DOUBLY_LINKED_IMPLEMENTED

#include "FixedArrayList.h"
#include "VariableArrayList.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "perf.h"

long MeasurePrependSpeed(List<size_t>* L, size_t numberOfItems);
long MeasureAppendSpeed(List<size_t>* L, size_t numberOfItems);
long MeasureRemoveFromStartSpeed(List<size_t>* L, size_t numberOfItems);
long MeasureRemoveFromEndSpeed(List<size_t>* L, size_t numberOfItems);
long MeasureGetFromStartSpeed(List<size_t>* L, size_t numberOfItems);
long MeasureGetFromEndSpeed(List<size_t>* L, size_t numberOfItems);
double MeasureAverageFindSpeed(List<size_t>* L, size_t numberOfItems);
double MeasureAverageGetSpeed(List<size_t>* L, size_t numberOfItems);

void TestPerf(PerfType perfType) {
    const size_t NUMBER_TESTS = 20;
    long long totalTime;

    if (InsertStart == perfType) {
        cout << "Insert at Start Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 18000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems+1);
                totalTime += MeasurePrependSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasurePrependSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasurePrependSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasurePrependSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }

    else if (InsertEnd == perfType) {
        cout << "Insert at End Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 20000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems+1);
                totalTime += MeasureAppendSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasureAppendSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasureAppendSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasureAppendSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }

    else if (RemoveStart == perfType) {
        cout << "Remove First Item Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 20000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems);
                totalTime += MeasureRemoveFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasureRemoveFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasureRemoveFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasureRemoveFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }

    else if (RemoveEnd == perfType) {
        cout << "Remove Last Item Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 20000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems);
                totalTime += MeasureRemoveFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasureRemoveFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasureRemoveFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasureRemoveFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }

    else if (GetStart == perfType) {
        cout << "Get First Item Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 20000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems);
                totalTime += MeasureGetFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasureGetFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasureGetFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasureGetFromStartSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }

    else if (GetEnd == perfType) {
        cout << "Get Last Item Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 20000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems);
                totalTime += MeasureGetFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasureGetFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasureGetFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasureGetFromEndSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }

    else if (AverageFind == perfType) {
        cout << "Average Find Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 20000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems);
                totalTime += MeasureAverageFindSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasureAverageFindSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasureAverageFindSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasureAverageFindSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }

    else if (AverageGet == perfType) {
        cout << "Average Get Performance" << endl;
#if defined(DOUBLY_LINKED_IMPLEMENTED)
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList\tDoublyLinkedList" << endl;
#else
        cout << "#Items\tFixedArrayList\tVariableArrayList\tSinglyLinkedList" << endl;
#endif
        for (size_t numberOfItems = 1000; numberOfItems <= 20000; numberOfItems += 1000) {
            cout << numberOfItems;

            //FixedArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                FixedArrayList<size_t> L(numberOfItems);
                totalTime += MeasureAverageGetSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //VariableArrayList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                VariableArrayList<size_t> L;
                totalTime += MeasureAverageGetSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

            //SinglyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                SinglyLinkedList<size_t> L;
                totalTime += MeasureAverageGetSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;

#if defined(DOUBLY_LINKED_IMPLEMENTED)
            //DoublyLinkedList
            totalTime = 0;
            for (size_t test = 0; test < NUMBER_TESTS; test++) {
                DoublyLinkedList<size_t> L;
                totalTime += MeasureAverageGetSpeed(&L, numberOfItems);
            }
            cout <<  "\t" << totalTime / NUMBER_TESTS;
#endif
            cout << endl;
        }
    }
}

long MeasurePrependSpeed(List<size_t>* L, size_t numberOfItems) {
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(0, i);
    }
    steady_clock::time_point begin = steady_clock::now();
    L->Insert(0, numberOfItems+1);
    steady_clock::time_point end = steady_clock::now();
    return duration_cast<nanoseconds>(end-begin).count();
}

long MeasureAppendSpeed(List<size_t>* L, size_t numberOfItems) {
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(L->Size(), i);
    }
    steady_clock::time_point begin = steady_clock::now();
    L->Insert(L->Size(), numberOfItems+1);
    steady_clock::time_point end = steady_clock::now();
    return duration_cast<nanoseconds>(end-begin).count();
}

long MeasureRemoveFromStartSpeed(List<size_t>* L, size_t numberOfItems) {
    size_t item;

    // Create list of items
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(0, i);
    }
    steady_clock::time_point begin = steady_clock::now();
    L->Remove(0, item);
    steady_clock::time_point end = steady_clock::now();
    return duration_cast<nanoseconds>(end-begin).count();
}

long MeasureRemoveFromEndSpeed(List<size_t>* L, size_t numberOfItems) {
    size_t item;

    // Create list of items
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(0, i);
    }
    steady_clock::time_point begin = steady_clock::now();
    L->Remove(numberOfItems-1, item);
    steady_clock::time_point end = steady_clock::now();
    return duration_cast<nanoseconds>(end-begin).count();
}

long MeasureGetFromStartSpeed(List<size_t>* L, size_t numberOfItems) {
    size_t item;

    // Create list of items
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(0, i);
    }
    steady_clock::time_point begin = steady_clock::now();
    L->Get(0, item);
    steady_clock::time_point end = steady_clock::now();
    return duration_cast<nanoseconds>(end-begin).count();
}

long MeasureGetFromEndSpeed(List<size_t>* L, size_t numberOfItems) {
    size_t item;

    // Create list of items
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(0, i);
    }
    steady_clock::time_point begin = steady_clock::now();
    L->Get(numberOfItems-1, item);
    steady_clock::time_point end = steady_clock::now();
    return duration_cast<nanoseconds>(end-begin).count();
}

double MeasureAverageFindSpeed(List<size_t>* L, size_t numberOfItems) {
    // Create list of items
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(0, i);
    }

    // Try finding each item
    steady_clock::time_point begin = steady_clock::now();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Find(i);
    }
    steady_clock::time_point end = steady_clock::now();

    //Return average time for a Find call
    return ((double)duration_cast<nanoseconds>(end-begin).count())/numberOfItems;
}

double MeasureAverageGetSpeed(List<size_t>* L, size_t numberOfItems) {
    size_t item;

    // Create list of items
    L->Clear();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Insert(0, i);
    }

    // Try getting from each position
    steady_clock::time_point begin = steady_clock::now();
    for (size_t i = 0; i < numberOfItems; i ++) {
        L->Get(i, item);
    }
    steady_clock::time_point end = steady_clock::now();

    //Return average time for a Fet call
    return ((double)duration_cast<nanoseconds>(end-begin).count())/numberOfItems;
}

