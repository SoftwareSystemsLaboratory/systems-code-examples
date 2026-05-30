#include "debug.hh"
#include "list.hh"
#include "tests.hh"

bool test_add()
{
    List *list = new List();

    int pass = 0;

    pass += assert_equals(0, list->count(), "");
    list->add(1);
    pass += assert_equals(1, list->count(), "");
    list->add(2);
    pass += assert_equals(2, list->count(), "");

    delete list;
    return pass == 3;
}

bool test_remove()
{
    List *list = new List();

    int pass = 0;
    list->add(1);
    pass += assert_equals(1, list->count(), "");
    list->remove(0);
    pass += assert_equals(0, list->count(), "");

    delete list;
    return pass == 2;
}

bool test_get()
{
    List* list = new List();

    int pass = 0;

    list->add(1);
    list->add(2);
    int value1 = list->get(0);
    int value2 = list->get(1);

    delete list;

    pass += assert_equals(1, value1);
    pass += assert_equals(2, value2);

    return pass;
}

int run_tests()
{
    int pass_count = 0;

    pass_count += test_add() ? 1 : 0;
    pass_count += test_remove() ? 1 : 0;
    pass_count += test_get() ? 1 : 0;

    return pass_count;
}
