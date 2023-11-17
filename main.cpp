//
// Test Program for the the DoublyLinkedList Class
// Author: Max Benson
// Date: 08/05/2021
//

#include <assert.h>
#include <string.h>

#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

#include "FixedArrayList.h"
#include "VariableArrayList.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "perf.h"

#define DOUBLY_LINKED_IMPLEMENTED

// These must be sequential because we loop over them
#define    FIXED_ARRAY 0
#define    VARIABLE_ARRAY  1
#define    SINGLY_LINKED  2
#define    DOUBLY_LINKED 3

#if defined(DOUBLY_LINKED_IMPLEMENTED)
#define     MAX_VARIANT DOUBLY_LINKED
#else
#define     MAX_VARIANT SINGLY_LINKED
#endif

struct Insertion {
    string value;
    size_t positionToInsert;
};

void TestInsert(int variant, const Insertion arrayOfInsertions[], const string resultingValues[], size_t numberOfValues, const string& itemNotInList);
void TestSwap(List<int>*);
void TestReplace(List<string>*);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (2 == argc && strcmp(argv[1], "-perf:InsertStart") == 0) {
            TestPerf(InsertStart);
        }
        else if (2 == argc && strcmp(argv[1], "-perf:InsertEnd") == 0) {
            TestPerf(InsertEnd);
        }
        else if (2 == argc && strcmp(argv[1], "-perf:RemoveStart") == 0) {
            TestPerf(RemoveStart);
        }
        else if (2 == argc && strcmp(argv[1], "-perf:RemoveEnd") == 0) {
            TestPerf(RemoveEnd);
        }
        else if (2 == argc && strcmp(argv[1], "-perf:GetStart") == 0) {
            TestPerf(GetStart);
        }
        else if (2 == argc && strcmp(argv[1], "-perf:GetEnd") == 0) {
            TestPerf(GetEnd);
        }
        else if (2 == argc && strcmp(argv[1], "-perf:AverageFind") == 0) {
            TestPerf(AverageFind);
        }
        else if (2 == argc && strcmp(argv[1], "-perf:AverageGet") == 0) {
            TestPerf(AverageGet);
        }
        else {
            cout << "Usage: DoublyLinkedList [-perf:InsertStart|-perf:InsertEnd|-perf:RemoveStart|-perf:RemoveEnd|-perf:GetStart|-perf:GetEnd|-perf:AverageFind|-perf:AverageGet]" << endl;
            exit(1);
        }
    }
    else {
        Insertion empty[] = {};
        string resultForEmpty[] = {};
        Insertion append[] = {{"In",        0},
                              {"the",       1},
                              {"beginning", 2},
                              {"God",       3}};
        string resultForAppend[] = {"In", "the", "beginning", "God"};
        Insertion prepend[] = {{"In",        0},
                               {"the",       0},
                               {"beginning", 0},
                               {"God",       0}};
        string resultForPrepend[] = {"God", "beginning", "the", "In"};
        Insertion jumbled[] = {{"the",       0},
                               {"God",       1},
                               {"beginning", 1},
                               {"In",        0}};
        string resultForJumbled[] = {"In", "the", "beginning", "God"};

        cout << "Starting Validation Tests" << endl;
        for (int variant = FIXED_ARRAY; variant <= MAX_VARIANT; variant ++) {
            TestInsert(variant, empty, resultForEmpty, sizeof(empty) / sizeof(empty[0]), "not-in-list");
            cout << "empty  " << variant << endl;
            TestInsert(variant, append, resultForAppend, sizeof(append) / sizeof(append[0]), "not-in-list");
            cout << "append " << variant << endl;
            TestInsert(variant, prepend, resultForPrepend, sizeof(prepend) / sizeof(prepend[0]), "not-in-list");
            cout << "Prepend  " << variant << endl;
            TestInsert(variant, jumbled, resultForJumbled, sizeof(jumbled) / sizeof(jumbled[0]), "not-in-list");
            cout << "jumbled  " << variant << endl;
            if (variant == FIXED_ARRAY) {
                FixedArrayList<int> L1(10);
                FixedArrayList<string> L2(10);
                FixedArrayList<string> L3(10);

                TestSwap(&L1);
                TestReplace(&L2);
            }
            else if (variant == VARIABLE_ARRAY) {
                VariableArrayList<int> L1;
                VariableArrayList<string> L2;
                VariableArrayList<string> L3;

                TestSwap(&L1);
                TestReplace(&L2);
            }
            else if (variant == SINGLY_LINKED) {
                SinglyLinkedList<int> L1;
                SinglyLinkedList<string> L2;
                SinglyLinkedList<string> L3;

                TestSwap(&L1);
                TestReplace(&L2);
            }
#if defined(DOUBLY_LINKED_IMPLEMENTED)
            else if (variant == DOUBLY_LINKED) {
                 DoublyLinkedList<int> L1;
                 DoublyLinkedList<string> L2;
                 DoublyLinkedList<string> L3;

                 TestSwap(&L1);
                 TestReplace(&L2);
            }
#endif
        }
        cout << "Validation Tests Passed" << endl;
    }

    return 0;
}

void TestInsert(int variant, const Insertion arrayOfInsertions[], const string resultingValues[], size_t numberOfValues, const string& itemNotInList) {
    string item;
    stringstream sstr1;
    stringstream sstr2;

    List<string>* pointerToList;
    List<string>* pointerToCopiedList;

    if (variant == FIXED_ARRAY) {
        pointerToList = new FixedArrayList<string>(numberOfValues);
    }
    else if (variant == VARIABLE_ARRAY) {
        pointerToList = new VariableArrayList<string>;
    }
    else if (variant == SINGLY_LINKED) {
        pointerToList = new SinglyLinkedList<string>;
    }
#if defined(DOUBLY_LINKED_IMPLEMENTED)
    else if (variant == DOUBLY_LINKED) {
        pointerToList = new DoublyLinkedList<string>;
    }
#endif

    assert(pointerToList->CheckConsistency());
    for (size_t i = 0; i < numberOfValues; i ++) {
        assert(pointerToList->Insert(arrayOfInsertions[i].positionToInsert, arrayOfInsertions[i].value));
        assert(pointerToList->CheckConsistency());
    }
cout << 23 << endl;
    assert(pointerToList->Size() == numberOfValues);
    for (size_t i = 0; i < numberOfValues; i ++) {
cout << 24 << endl;
        assert(pointerToList->Find(resultingValues[i]) == i);
        assert(pointerToList->Find(resultingValues[i],i+1) == -1);
        assert(pointerToList->Get(i, item));
        assert(item == resultingValues[i]);
    }

    cout << 25 << endl;

    assert(pointerToList->Find(itemNotInList) == -1);
    assert(!pointerToList->Get(numberOfValues,item));
    assert(!pointerToList->Get(numberOfValues+1,item));

    for (size_t i = 0; i < numberOfValues; i ++) {
        cout << i << endl;
        assert(pointerToList->Remove(i, item));
        assert(item == resultingValues[i]);
        assert(pointerToList->CheckConsistency());
        assert(pointerToList->Insert(i, resultingValues[i]));
        assert(pointerToList->CheckConsistency());
        assert(pointerToList->Size() == numberOfValues);
    }
    assert(!pointerToList->Insert(numberOfValues+1, "bad-position"));
    assert(!pointerToList->Remove(numberOfValues, item));
    assert(!pointerToList->Remove(numberOfValues+1, item));
    assert(pointerToList->Size() == numberOfValues);

    sstr1 << "[";
    for (size_t i = 0; i < numberOfValues; i ++) {
        if (i > 0) {
            sstr1 << ", ";
        }
        sstr1 << resultingValues[i];
    }
    sstr1 << "]";

    sstr2 << *pointerToList;

    assert(sstr1.str() == sstr2.str());

    assert(pointerToList->CheckConsistency());

    // Test Copy Constructor
    if (variant == FIXED_ARRAY) {
        pointerToCopiedList = new FixedArrayList<string>(*(FixedArrayList<string> *)pointerToList);
    }
    else if (variant == VARIABLE_ARRAY) {
        pointerToCopiedList = new VariableArrayList<string>(*(VariableArrayList<string> *)pointerToList);
    }
    else if (variant == SINGLY_LINKED) {
        pointerToCopiedList = new SinglyLinkedList<string>(*(SinglyLinkedList<string> *)pointerToList);
    }
#if defined(DOUBLY_LINKED_IMPLEMENTED)
    else {
        pointerToCopiedList = new DoublyLinkedList<string>(*(DoublyLinkedList<string> *)pointerToList);
    }
#endif
    assert(pointerToList->CheckConsistency());
    assert(pointerToCopiedList->CheckConsistency());
    sstr1 << *pointerToList;
    sstr2 << *pointerToCopiedList;
    assert(sstr1.str() == sstr2.str());
    assert(pointerToList->CheckConsistency());
    assert(pointerToCopiedList->CheckConsistency());

    // Test Copy Assignment Operator
    if (variant == FIXED_ARRAY) {
        FixedArrayList<string> LAssign(1);

        assert(LAssign.CheckConsistency());
        LAssign = *((FixedArrayList<string> *)pointerToList);
        sstr1 << *pointerToList;
        sstr2 << LAssign;
        assert(sstr1.str() == sstr2.str());
        assert(pointerToList->CheckConsistency());
        assert(LAssign.CheckConsistency());
    }
    else if (variant == VARIABLE_ARRAY) {
        VariableArrayList<string> LAssign;

        assert(LAssign.CheckConsistency());
        LAssign = *((VariableArrayList<string> *)pointerToList);
        sstr1 << *pointerToList;
        sstr2 << LAssign;
        assert(sstr1.str() == sstr2.str());
        assert(pointerToList->CheckConsistency());
        assert(LAssign.CheckConsistency());
    }
    else if (variant == SINGLY_LINKED) {
        SinglyLinkedList<string> LAssign;

        assert(LAssign.CheckConsistency());
        LAssign = *((SinglyLinkedList<string> *)pointerToList);
        sstr1 << *pointerToList;
        sstr2 << LAssign;
        assert(sstr1.str() == sstr2.str());
        assert(pointerToList->CheckConsistency());
        assert(LAssign.CheckConsistency());
    }
#if defined(DOUBLY_LINKED_IMPLEMENTED)
    else if (variant == DOUBLY_LINKED) {
        DoublyLinkedList<string> LAssign;

        assert(LAssign.CheckConsistency());
        LAssign = *((DoublyLinkedList<string> *)pointerToList);
        sstr1 << *pointerToList;
        sstr2 << LAssign;
        assert(sstr1.str() == sstr2.str());
        assert(pointerToList->CheckConsistency());
        assert(LAssign.CheckConsistency());
    }
#endif
    pointerToList->Clear();
    assert(pointerToList->Size() == 0);
    assert(pointerToList->CheckConsistency());
    delete pointerToList;
    delete pointerToCopiedList;
}


void TestSwap(List<int>* L) {
    stringstream sstr;

    L->Clear();
    L->Insert(L->Size(), 1);
    L->Insert(L->Size(), 2);
    L->Insert(L->Size(), 3);
    assert(L->Swap(0,1));
    assert(L->Swap(1,2));
    assert(!L->Swap(4, 0));
    sstr << *L;
    assert(sstr.str() == "[2, 3, 1]");
}

void TestReplace(List<string> *L) {
    stringstream sstr;

    L->Clear();
    L->Insert(L->Size(), "A");
    L->Insert(L->Size(), "B");
    L->Insert(L->Size(), "C");
    assert(L->Replace(1, "D"));
    assert(!L->Replace(4, "D"));
    sstr << *L;
    assert(sstr.str() == "[A, D, C]");
}
