/* main.c - Municipal Financial Management System (MFMS) - Project A
 * Entry point: displays the main menu and calls each module.
 * Compile: gcc -std=c99 -Wall -Wextra -o mfms main.c utilities.c employees.c budget.c suppliers.c assets.c reports.c
 */
#include <stdio.h>
#include "utilities.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

static void displayMenu(void)
{
    printf("\n");
    printLine('=', 40);
    printf("MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printLine('=', 40);
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

int main(void)
{
    int choice;

    do
    {
        displayMenu();
        choice = readInt("Enter your choice: ", 1, 6);

        switch (choice)
        {
            case 1: employeeMenu(); break;
            case 2: budgetMenu(); break;
            case 3: supplierMenu(); break;
            case 4: assetMenu(); break;
            case 5: reportsMenu(); break;
            case 6: printf("\nThank you for using the MFMS. Goodbye.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}
