/* reports.c - Reports module (reads data through each module's accessor functions) */
#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "utilities.h"

void displayEmployeeReport(void)
{
    int count = getEmployeeCount();
    int i;
    int highestIndex = 0;
    int lowestIndex = 0;
    double totalGross = 0.0;
    double totalNet = 0.0;
    char name[TEXT_LENGTH];

    printHeader("EMPLOYEE REPORT");

    if (count == 0)
    {
        printf("No employee data available.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        totalGross += getEmployeeGross(i);
        totalNet += getEmployeeNet(i);

        if (getEmployeeGross(i) > getEmployeeGross(highestIndex))
        {
            highestIndex = i;
        }
        if (getEmployeeGross(i) < getEmployeeGross(lowestIndex))
        {
            lowestIndex = i;
        }
    }

    printf("Total Employees      : %d\n", count);
    printf("Average Salary       : N$%.2f\n", totalGross / count);

    getEmployeeName(highestIndex, name);
    printf("Highest Salary       : N$%.2f (%s)\n", getEmployeeGross(highestIndex), name);

    getEmployeeName(lowestIndex, name);
    printf("Lowest Salary        : N$%.2f (%s)\n", getEmployeeGross(lowestIndex), name);

    printf("Total Gross Payroll  : N$%.2f\n", totalGross);
    printf("Total Net Payroll    : N$%.2f\n", totalNet);
    printf("(Salary figures are gross salaries.)\n");
}

void displayBudgetReport(void)
{
    int count = getDepartmentCount();
    int i;
    int overCount = 0;
    double totalAllocated = 0.0;
    double totalSpent = 0.0;
    char name[TEXT_LENGTH];

    printHeader("BUDGET REPORT");

    if (count == 0)
    {
        printf("No budget data available.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        totalAllocated += getDepartmentAllocated(i);
        totalSpent += getDepartmentSpent(i);
    }

    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure     : N$%.2f\n", totalSpent);
    printf("Remaining Budget      : N$%.2f\n", calculateBudget(totalAllocated, totalSpent));

    printf("\nDepartments exceeding budget:\n");
    for (i = 0; i < count; i++)
    {
        if (!isWithinBudget(getDepartmentAllocated(i), getDepartmentSpent(i)))
        {
            getDepartmentName(i, name);
            printf("  - %s (over by N$%.2f)\n", name,
                   -calculateBudget(getDepartmentAllocated(i), getDepartmentSpent(i)));
            overCount++;
        }
    }
    if (overCount == 0)
    {
        printf("  None. All departments are within budget.\n");
    }
}

void displaySupplierReport(void)
{
    /* Reuses the supplier display function */
    displaySuppliers();
}

void displayAssetReport(void)
{
    int i;
    int count = getAssetCount();
    double total = 0.0;

    for (i = 0; i < count; i++)
    {
        total += getAssetValue(i);
    }

    displayAssets();
    if (count > 0)
    {
        printf("Average asset value: N$%.2f\n", total / count);
    }
}

void reportsMenu(void)
{
    int choice;

    do
    {
        printHeader("REPORTS");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1: displayEmployeeReport(); break;
            case 2: displayBudgetReport(); break;
            case 3: displaySupplierReport(); break;
            case 4: displayAssetReport(); break;
            case 5: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}
