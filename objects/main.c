#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char Name[30];
    int Age;
    int NumberOfTeamMates;
    struct Employee** TeamMates;
} Employee;

Employee* Employee_New(char* name, const int age)
{
    Employee* newEmp = (Employee*)calloc(1, sizeof(Employee));
    memcpy(newEmp->Name, name, strlen(name)+1);
    newEmp->Age = age;
    newEmp->TeamMates = NULL;
    newEmp->NumberOfTeamMates = 0;
    return newEmp;
}

void Employee_Print(Employee* employee)
{
    printf("Name: %s\n", employee->Name);
    printf("Age:  %d\n", employee->Age);
    printf("Number of TeamMates: %d\n", employee->NumberOfTeamMates);
    if(employee->NumberOfTeamMates > 0)
    {
        printf("\t");
    }
    for(int i = 0; i < employee->NumberOfTeamMates; i++)
    {
        Employee* teamMate = (Employee*) employee->TeamMates[i];
        printf("%s, ", teamMate->Name);
    }
    printf("\n");
}

void Employee_AddTeamMate(Employee* employee, Employee* teamMate)
{
    employee->NumberOfTeamMates += 1;
    employee->TeamMates = (struct Employee**)realloc(
                              employee->TeamMates,
                              sizeof(Employee*) * employee->NumberOfTeamMates);
    employee->TeamMates[employee->NumberOfTeamMates-1] = (struct Employee *)teamMate;
}

int main(int argc, char* argv[])
{
    Employee *joe = Employee_New("Joe", 29);
    Employee *tom = Employee_New("Tom", 32);
    Employee *bill = Employee_New("Bill", 35);

    Employee_Print(joe);

    Employee_AddTeamMate(joe, tom);
    Employee_AddTeamMate(joe, bill);

    Employee_Print(joe);

    return 0;
}



