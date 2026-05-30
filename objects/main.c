#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct employee {
    char name[30];
    int age;
    int number_of_teammates;
    struct employee **teammates;
} employee_t;

employee_t *employee_new(char *name, const int age) {
    employee_t *new_employee = (employee_t *) calloc(1, sizeof(employee_t));
    memcpy(new_employee->name, name, strlen(name) + 1);
    new_employee->age = age;
    new_employee->teammates = NULL;
    new_employee->number_of_teammates = 0;
    return new_employee;
}

void employee_print(employee_t *employee) {
    printf("Name: %s\n", employee->name);
    printf("Age:  %d\n", employee->age);
    printf("Number of teammates: %d\n", employee->number_of_teammates);
    if (employee->number_of_teammates > 0) {
        printf("\t");
    }
    for (int i = 0; i < employee->number_of_teammates; i++) {
        employee_t *teammate = (employee_t *) employee->teammates[i];
        printf("%s, ", teammate->name);
    }
    printf("\n");
}

void employee_add_teammate(employee_t *employee, employee_t *teammate) {
    employee->number_of_teammates += 1;
    employee->teammates = (struct employee **) realloc(
            employee->teammates,
            sizeof(employee_t *) * employee->number_of_teammates);
    employee->teammates[employee->number_of_teammates - 1] = teammate;
}

int main(int argc, char *argv[]) {
    employee_t *joe = employee_new("Joe", 29);
    employee_t *tom = employee_new("Tom", 32);
    employee_t *bill = employee_new("Bill", 35);

    employee_print(joe);

    employee_add_teammate(joe, tom);
    employee_add_teammate(joe, bill);

    employee_print(joe);

    return 0;
}


