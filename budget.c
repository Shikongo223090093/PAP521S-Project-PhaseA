#include <stdio.h>
#include <string.h>
#include "budget.h"

/* Arrays used to store budget information */
char departmentNames[MAX_DEPARTMENTS][50];
double allocatedBudgets[MAX_DEPARTMENTS];
double expenditures[MAX_DEPARTMENTS];

/* Keeps track of the number of departments */
int departmentCount = 0;


/* Displays the Budget Management menu */
void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          BUDGET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Department Budget\n");
        printf("2. Display All Budgets\n");
        printf("3. Search Department\n");
        printf("4. Show Departments Over Budget\n");
        printf("5. Return to Main Menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addBudget();
                break;

            case 2:
                displayBudgets();
                break;

            case 3:
                searchBudget();
                break;

            case 4:
                displayOverBudget();
                break;

            case 5:
                printf("\nReturning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid choice. Please enter 1 to 5.\n");
        }

    } while(choice != 5);
}


/* Adds a department and its budget information */
void addBudget(void)
{
    if(departmentCount >= MAX_DEPARTMENTS)
    {
        printf("\nMaximum number of departments reached.\n");
        return;
    }

    printf("\n========== ADD DEPARTMENT BUDGET ==========\n");

    printf("Enter department name: ");
    scanf(" %49[^\n]", departmentNames[departmentCount]);

    /* Validate allocated budget */
    do
    {
        printf("Enter allocated budget: N$");
        scanf("%lf", &allocatedBudgets[departmentCount]);

        if(allocatedBudgets[departmentCount] < 0)
        {
            printf("Invalid budget. Budget cannot be negative.\n");
        }

    } while(allocatedBudgets[departmentCount] < 0);


    /* Validate expenditure */
    do
    {
        printf("Enter expenditure: N$");
        scanf("%lf", &expenditures[departmentCount]);

        if(expenditures[departmentCount] < 0)
        {
            printf("Invalid expenditure. Expenditure cannot be negative.\n");
        }

    } while(expenditures[departmentCount] < 0);

    printf("\nBudget successfully added for %s!\n",
           departmentNames[departmentCount]);

    departmentCount++;
}


/* Calculates the remaining budget */
double calculateRemaining(double budget, double expenditure)
{
    return budget - expenditure;
}


/* Displays all departmental budget information */
void displayBudgets(void)
{
    int i;
    double remaining;

    if(departmentCount == 0)
    {
        printf("\nNo budget information available.\n");
        return;
    }

    printf("\n================ BUDGET INFORMATION ================\n");

    for(i = 0; i < departmentCount; i++)
    {
        remaining = calculateRemaining(
            allocatedBudgets[i],
            expenditures[i]
        );

        printf("\nDepartment: %s\n", departmentNames[i]);
        printf("Allocated Budget: N$%.2f\n", allocatedBudgets[i]);
        printf("Expenditure: N$%.2f\n", expenditures[i]);
        printf("Remaining Budget: N$%.2f\n", remaining);

        if(expenditures[i] > allocatedBudgets[i])
        {
            printf("Status: OVER BUDGET\n");
        }
        else
        {
            printf("Status: WITHIN BUDGET\n");
        }

        printf("----------------------------------------------------\n");
    }
}


/* Searches for a department */
void searchBudget(void)
{
    char searchName[50];
    int i;
    int found = 0;
    double remaining;

    if(departmentCount == 0)
    {
        printf("\nNo departments have been added yet.\n");
        return;
    }

    printf("\nEnter department name to search: ");
    scanf(" %49[^\n]", searchName);

    for(i = 0; i < departmentCount; i++)
    {
        if(strcmp(departmentNames[i], searchName) == 0)
        {
            remaining = calculateRemaining(
                allocatedBudgets[i],
                expenditures[i]
            );

            printf("\n========== DEPARTMENT FOUND ==========\n");
            printf("Department: %s\n", departmentNames[i]);
            printf("Allocated Budget: N$%.2f\n", allocatedBudgets[i]);
            printf("Expenditure: N$%.2f\n", expenditures[i]);
            printf("Remaining Budget: N$%.2f\n", remaining);

            if(expenditures[i] > allocatedBudgets[i])
            {
                printf("Status: OVER BUDGET\n");
            }
            else
            {
                printf("Status: WITHIN BUDGET\n");
            }

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nDepartment '%s' was not found.\n", searchName);
    }
}


/* Displays departments that exceeded their budgets */
void displayOverBudget(void)
{
    int i;
    int found = 0;
    double remaining;

    if(departmentCount == 0)
    {
        printf("\nNo budget information available.\n");
        return;
    }

    printf("\n========== DEPARTMENTS OVER BUDGET ==========\n");

    for(i = 0; i < departmentCount; i++)
    {
        if(expenditures[i] > allocatedBudgets[i])
        {
            remaining = calculateRemaining(
                allocatedBudgets[i],
                expenditures[i]
            );

            printf("\nDepartment: %s\n", departmentNames[i]);
            printf("Allocated Budget: N$%.2f\n", allocatedBudgets[i]);
            printf("Expenditure: N$%.2f\n", expenditures[i]);
            printf("Amount Over Budget: N$%.2f\n", -remaining);

            found = 1;
        }
    }

    if(found == 0)
    {
        printf("\nNo departments have exceeded their budgets.\n");
    }
}