/* suppliers.c - Supplier Management module (strings and character arrays) */
#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utilities.h"

#define ID_LENGTH 10
#define PHONE_LENGTH 30

static char supplierIds[MAX_SUPPLIERS][ID_LENGTH];
static char supplierNames[MAX_SUPPLIERS][TEXT_LENGTH];
static char supplierEmails[MAX_SUPPLIERS][TEXT_LENGTH];
static char supplierPhones[MAX_SUPPLIERS][PHONE_LENGTH];
static char supplierTowns[MAX_SUPPLIERS][TEXT_LENGTH];
static int supplierCount = 0;

/* Checks whether a supplier name is already registered (uses strcmp). */
static int supplierNameExists(const char name[])
{
    int i;

    for (i = 0; i < supplierCount; i++)
    {
        if (equalsIgnoreCase(supplierNames[i], name))
        {
            return 1;
        }
    }
    return 0;
}

/* Uses strcpy() and strcat() to construct a description. */
void buildSupplierDescription(int index, char description[])
{
    strcpy(description, supplierNames[index]);
    strcat(description, " operates in ");
    strcat(description, supplierTowns[index]);
    strcat(description, ".");
}

static void printSupplierDetails(int index)
{
    char description[TEXT_LENGTH * 2 + 20];

    buildSupplierDescription(index, description);

    printf("\n  Supplier ID: %s\n", supplierIds[index]);
    printf("  Name       : %s\n", supplierNames[index]);
    printf("  Email      : %s\n", supplierEmails[index]);
    printf("  Phone      : %s\n", supplierPhones[index]);
    printf("  Town       : %s\n", supplierTowns[index]);
    printf("  Summary    : %s\n", description);
}

void addSupplier(void)
{
    char name[TEXT_LENGTH];

    printHeader("ADD SUPPLIER");

    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("The supplier register is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

    readString("Supplier name: ", name, TEXT_LENGTH);
    if (supplierNameExists(name))
    {
        printf("A supplier named \"%s\" is already registered.\n", name);
        return;
    }
    strcpy(supplierNames[supplierCount], name);

    /* Keep asking until the email has a valid format */
    do
    {
        readString("Email: ", supplierEmails[supplierCount], TEXT_LENGTH);
        if (!isValidEmail(supplierEmails[supplierCount]))
        {
            printf("  Invalid email. Use a format such as sales@abc.com\n");
        }
    } while (!isValidEmail(supplierEmails[supplierCount]));

    /* Keep asking until the phone number is valid */
    do
    {
        readString("Telephone number: ", supplierPhones[supplierCount], PHONE_LENGTH);
        if (!isValidPhone(supplierPhones[supplierCount]))
        {
            printf("  Invalid phone. Use 7-15 digits (a leading + is allowed).\n");
        }
    } while (!isValidPhone(supplierPhones[supplierCount]));

    readString("Town/Location: ", supplierTowns[supplierCount], TEXT_LENGTH);

    sprintf(supplierIds[supplierCount], "SUP%03d", supplierCount + 1);
    printf("\nSupplier added with ID %s.\n", supplierIds[supplierCount]);
    supplierCount++;
}

void displaySuppliers(void)
{
    int i;

    printHeader("REGISTERED SUPPLIERS");

    if (supplierCount == 0)
    {
        printf("No suppliers have been registered yet.\n");
        return;
    }

    printf("%-7s %-22s %-24s %-13s %-12s\n", "ID", "Name", "Email", "Phone", "Town");
    printLine('-', 80);

    for (i = 0; i < supplierCount; i++)
    {
        printf("%-7s %-22.22s %-24.24s %-13.13s %-12.12s\n",
               supplierIds[i], supplierNames[i], supplierEmails[i],
               supplierPhones[i], supplierTowns[i]);
    }
    printLine('-', 80);
    printf("Total suppliers: %d\n", supplierCount);
}

void searchSupplier(void)
{
    int option;
    int i;
    int found = 0;
    char searchText[TEXT_LENGTH];

    printHeader("SEARCH SUPPLIER");
    printf("1. Search by supplier name (full or part)\n");
    printf("2. Search by town/location\n");
    printf("3. Search by Supplier ID\n");
    option = readInt("Enter choice: ", 1, 3);

    readString("Enter search text: ", searchText, TEXT_LENGTH);

    for (i = 0; i < supplierCount; i++)
    {
        int match = 0;

        switch (option)
        {
            case 1: match = containsIgnoreCase(supplierNames[i], searchText); break;
            case 2: match = equalsIgnoreCase(supplierTowns[i], searchText); break;
            case 3: match = equalsIgnoreCase(supplierIds[i], searchText); break;
            default: break;
        }

        if (match)
        {
            printSupplierDetails(i);
            found++;
        }
    }

    if (found == 0)
    {
        printf("Supplier not found.\n");
    }
    else
    {
        printf("\n%d supplier(s) found.\n", found);
    }
}

void supplierMenu(void)
{
    int choice;

    do
    {
        printHeader("SUPPLIER MANAGEMENT");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1: addSupplier(); break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

int getSupplierCount(void)
{
    return supplierCount;
}
