/* employees.c - Employee Management module (uses parallel arrays) */
#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utilities.h"

/* Employee data: element i of every array belongs to the same employee */
static int employeeIds[MAX_EMPLOYEES];
static char employeeNames[MAX_EMPLOYEES][TEXT_LENGTH];
static char employeeDepartments[MAX_EMPLOYEES][TEXT_LENGTH];
static double basicSalaries[MAX_EMPLOYEES];
static double housingAllowances[MAX_EMPLOYEES];
static double transportAllowances[MAX_EMPLOYEES];
static double grossSalaries[MAX_EMPLOYEES];
static double taxAmounts[MAX_EMPLOYEES];
static double netSalaries[MAX_EMPLOYEES];
static int employeeCount = 0;

/* ---------- Calculation functions ---------- */

double calculateSalary(double basic, double housing, double transport)
{
    return basic + housing + transport;
}

/* Simplified tax bands for this exercise (not official tax rates). */
double calculateTax(double grossSalary)
{
    double rate;

    if (grossSalary <= 5000.0)
    {
        rate = 0.0;
    }
    else if (grossSalary <= 15000.0)
    {
        rate = 0.18;
    }
    else if (grossSalary <= 30000.0)
    {
        rate = 0.28;
    }
    else
    {
        rate = 0.35;
    }
    return grossSalary * rate;
}

double calculateNetSalary(double grossSalary, double tax)
{
    return grossSalary - tax;
}

/* ---------- Searching ---------- */

int findEmployeeIndex(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employeeIds[i] == id)
        {
            return i;
        }
    }
    return -1;
}

/* Prints all details of one employee. */
static void printEmployeeDetails(int index)
{
    printf("\n  Employee ID      : %d\n", employeeIds[index]);
    printf("  Name             : %s\n", employeeNames[index]);
    printf("  Department       : %s\n", employeeDepartments[index]);
    printf("  Basic salary     : N$%.2f\n", basicSalaries[index]);
    printf("  Housing allowance: N$%.2f\n", housingAllowances[index]);
    printf("  Transport allow. : N$%.2f\n", transportAllowances[index]);
    printf("  Gross salary     : N$%.2f\n", grossSalaries[index]);
    printf("  Tax              : N$%.2f\n", taxAmounts[index]);
    printf("  Net salary       : N$%.2f\n", netSalaries[index]);
}

/* ---------- Operations ---------- */

void addEmployee(void)
{
    int id;

    printHeader("ADD EMPLOYEE");

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("The employee register is full (%d employees).\n", MAX_EMPLOYEES);
        return;
    }

    id = readInt("Employee ID (1-999999): ", 1, 999999);
    if (findEmployeeIndex(id) != -1)
    {
        printf("An employee with ID %d already exists.\n", id);
        return;
    }

    employeeIds[employeeCount] = id;
    readString("Full name: ", employeeNames[employeeCount], TEXT_LENGTH);
    readString("Department: ", employeeDepartments[employeeCount], TEXT_LENGTH);
    basicSalaries[employeeCount] = readDouble("Basic salary (N$): ", 0.01);
    housingAllowances[employeeCount] = readDouble("Housing allowance (N$): ", 0.0);
    transportAllowances[employeeCount] = readDouble("Transport allowance (N$): ", 0.0);

    grossSalaries[employeeCount] = calculateSalary(basicSalaries[employeeCount],
                                                   housingAllowances[employeeCount],
                                                   transportAllowances[employeeCount]);
    taxAmounts[employeeCount] = calculateTax(grossSalaries[employeeCount]);
    netSalaries[employeeCount] = calculateNetSalary(grossSalaries[employeeCount],
                                                    taxAmounts[employeeCount]);

    employeeCount++;
    printf("\nEmployee added successfully.\n");
}

void displayEmployees(void)
{
    int i;

    printHeader("EMPLOYEE LIST");

    if (employeeCount == 0)
    {
        printf("No employees have been captured yet.\n");
        return;
    }

    printf("%-7s %-20s %-14s %12s %11s %12s\n",
           "ID", "Name", "Department", "Gross (N$)", "Tax (N$)", "Net (N$)");
    printLine('-', 80);

    for (i = 0; i < employeeCount; i++)
    {
        printf("%-7d %-20.20s %-14.14s %12.2f %11.2f %12.2f\n",
               employeeIds[i], employeeNames[i], employeeDepartments[i],
               grossSalaries[i], taxAmounts[i], netSalaries[i]);
    }
    printLine('-', 80);
    printf("Total employees: %d\n", employeeCount);
}

void searchEmployee(void)
{
    int option;
    int id;
    int index;
    int found = 0;
    char searchText[TEXT_LENGTH];
    int i;

    printHeader("SEARCH EMPLOYEE");
    printf("1. Search by Employee ID\n");
    printf("2. Search by name (full or part of name)\n");
    printf("3. Search by department\n");
    option = readInt("Enter choice: ", 1, 3);

    switch (option)
    {
        case 1:
            id = readInt("Enter Employee ID: ", 1, 999999);
            index = findEmployeeIndex(id);
            if (index == -1)
            {
                printf("Employee not found.\n");
            }
            else
            {
                printf("\nEmployee found at position %d.", index);
                printEmployeeDetails(index);
            }
            break;

        case 2:
            readString("Enter name to search: ", searchText, TEXT_LENGTH);
            for (i = 0; i < employeeCount; i++)
            {
                if (containsIgnoreCase(employeeNames[i], searchText))
                {
                    printEmployeeDetails(i);
                    found++;
                }
            }
            if (found == 0)
            {
                printf("No employee matches \"%s\".\n", searchText);
            }
            else
            {
                printf("\n%d employee(s) found.\n", found);
            }
            break;

        case 3:
            readString("Enter department: ", searchText, TEXT_LENGTH);
            for (i = 0; i < employeeCount; i++)
            {
                if (equalsIgnoreCase(employeeDepartments[i], searchText))
                {
                    printEmployeeDetails(i);
                    found++;
                }
            }
            if (found == 0)
            {
                printf("No employees found in \"%s\".\n", searchText);
            }
            else
            {
                printf("\n%d employee(s) found.\n", found);
            }
            break;

        default:
            printf("Invalid choice.\n");
    }
}

void displayPayslip(void)
{
    int id;
    int index;

    printHeader("EMPLOYEE SALARY INFORMATION");

    if (employeeCount == 0)
    {
        printf("No employees have been captured yet.\n");
        return;
    }

    id = readInt("Enter Employee ID: ", 1, 999999);
    index = findEmployeeIndex(id);

    if (index == -1)
    {
        printf("Employee not found.\n");
        return;
    }
    printEmployeeDetails(index);
}

void employeeMenu(void)
{
    int choice;

    do
    {
        printHeader("EMPLOYEE MANAGEMENT");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate / View Salary Information\n");
        printf("5. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice)
        {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: displayPayslip(); break;
            case 5: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

/* ---------- Accessors for the Reports module ---------- */

int getEmployeeCount(void)
{
    return employeeCount;
}

double getEmployeeGross(int index)
{
    return grossSalaries[index];
}

double getEmployeeNet(int index)
{
    return netSalaries[index];
}

void getEmployeeName(int index, char destination[])
{
    strcpy(destination, employeeNames[index]);
}
