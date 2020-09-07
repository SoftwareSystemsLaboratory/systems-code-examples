#include "debug.hh"
#include "list.hh"
#include "tests.hh"

bool testAdd() {
    List *list = new List();

    int pass = 0;

    pass += assertEquals(0, list->Count(), "");
    list->Add(1);
    pass += assertEquals(1, list->Count(), "");
    list->Add(2);
    pass += assertEquals(2, list->Count(), "");

    delete list;
    return pass == 3;
}

bool testRemove() {
    List *list = new List();

    int pass = 0;
    list->Add(1);
    pass += assertEquals(1, list->Count(), "");
    list->Remove(0);
    pass += assertEquals(0, list->Count(), "");

    delete list;
    return pass == 2;
}

bool testGet() {
    List* list = new List();

    int pass = 0;

    list->Add(1);
    list->Add(2);
    int value1 = list->Get(0);
    int value2 = list->Get(1);

    delete list;

    pass += assertEquals(1, value1);
    pass += assertEquals(2, value2);

    return pass;
}

int runTests() {
    int passCount = 0;

    passCount += testAdd() ? 1 : 0;
    passCount += testRemove() ? 1 : 0;
    passCount += testGet() ? 1 : 0;

    return passCount;
}
