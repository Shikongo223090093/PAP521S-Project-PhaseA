/* budget.c - Budget Management module */
#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utilities.h"

static char departmentNames[MAX_DEPARTMENTS][TEXT_LENGTH];
static double allocatedBudgets[MAX_DEPARTMENTS];
static double expenditures[MAX_DEPARTMENTS];
static int departmentCount = 0;

/* Remaining budget: positive = money left, negative = overspent. */
double calculateBudget(double allocated, double expenditure)
{
    return allocated - expenditure;
}

/* Returns 1 if expenditure does not exceed the allocated budget. */
int isWithinBudget(double allocated, double expenditure)
{
    return expenditure <= allocated;
}

int findDepartmentIndex(const char name[])
{
    int i;

    for (i = 0; i < departmentCount; i++)
    {
        if (equalsIgnoreCase(departmentNames[i], name))
        {
            return i;
        }
    }
    return -1;
}

void addDepartmentBudget(void)
{
    char name[TEXT_LENGTH];

    printHeader("ADD DEPARTMENT BUDGET");

    if (departmentCount >= MAX_DEPARTMENTS)
    {
        printf("The budget register is full (%d departments).\n", MAX_DEPARTMENTS);
        return;
    }

    readString("Department name: ", name, TEXT_LENGTH);
    if (findDepartmentIndex(name) != -1)
    {
        printf("A budget for \"%s\" already exists.\n", name);
        return;
    }

    strcpy(departmentNames[departmentCount], name);
    allocatedBudgets[departmentCount] = readDouble("Allocated budget (N$): ", 0.01);
    expenditures[departmentCount] = readDouble("Expenditure so far (N$): ", 0.0);

    departmentCount++;
    printf("\nDepartment budget added successfully.\n");
}

void recordExpenditure(void)
{
    char name[TEXT_LENGTH];
    int index;
    double amount;
    double remaining;

    printHeader("RECORD EXPENDITURE");

    if (departmentCount == 0)
    {
        printf("No department budgets have been captured yet.\n");
        return;
    }

    readString("Department name: ", name, TEXT_LENGTH);
    index = findDepartmentIndex(name);

    if (index == -1)
    {
        printf("Department \"%s\" was not found.\n", name);
        return;
    }

    amount = readDouble("Expenditure amount to add (N$): ", 0.01);
    expenditures[index] += amount;

    remaining = calculateBudget(allocatedBudgets[index], expenditures[index]);
    printf("\nExpenditure recorded. Remaining budget: N$%.2f\n", remaining);

    if (!isWithinBudget(allocatedBudgets[index], expenditures[index]))
    {
        printf("WARNING: %s has exceeded its budget by N$%.2f!\n",
               departmentNames[index], -remaining);
    }
}

void displayBudgets(void)
{
    int i;
    double remaining;

    printHeader("DEPARTMENT BUDGETS");

    if (departmentCount == 0)
    {
        printf("No department budgets have been captured yet.\n");
        return;
    }

    for (i = 0; i < departmentCount; i++)
    {
        remaining = calculateBudget(allocatedBudgets[i], expenditures[i]);

        printf("\nDepartment       : %s\n", departmentNames[i]);
        printf("Allocated Budget : N$%.2f\n", allocatedBudgets[i]);
        printf("Expenditure      : N$%.2f\n", expenditures[i]);
        printf("Remaining Budget : N$%.2f\n", remaining);
        printf("Status           : %s\n",
               isWithinBudget(allocatedBudgets[i], expenditures[i]) ? "WITHIN BUDGET" : "OVER BUDGET");
    }
}

void displayOverBudgetDepartments(void)
{
    int i;
    int count = 0;

    printHeader("DEPARTMENTS OVER BUDGET");

    for (i = 0; i < departmentCount; i++)
    {
        if (!isWithinBudget(allocatedBudgets[i], expenditures[i]))
        {
            printf("%-20.20s over by N$%.2f\n", departmentNames[i],
                   -calculateBudget(allocatedBudgets[i], expenditures[i]));
            count++;
        }
    }

    if (count == 0)
    {
        printf("No department has exceeded its budget.\n");
    }
}

void budgetMenu(void)
{
    int choice;

    do
    {
        printHeader("BUDGET MANAGEMENT");
        printf("1. Add Department Budget\n");
        printf("2. Record Expenditure\n");
        printf("3. Display Budget Information\n");
        printf("4. Show Departments Over Budget\n");
        printf("5. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1: addDepartmentBudget(); break;
            case 2: recordExpenditure(); break;
            case 3: displayBudgets(); break;
            case 4: displayOverBudgetDepartments(); break;
            case 5: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

/* ---------- Accessors for the Reports module ---------- */

int getDepartmentCount(void)
{
    return departmentCount;
}

double getDepartmentAllocated(int index)
{
    return allocatedBudgets[index];
}

double getDepartmentSpent(int index)
{
    return expenditures[index];
}

void getDepartmentName(int index, char destination[])
{
    strcpy(destination, departmentNames[index]);
}
