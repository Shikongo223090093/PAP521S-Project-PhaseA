#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 10

void budgetMenu(void);
void addDepartmentBudget(void);
void recordExpenditure(void);
void displayBudgets(void);
void displayOverBudgetDepartments(void);

/* Reusable calculation functions */
double calculateBudget(double allocated, double expenditure);
int isWithinBudget(double allocated, double expenditure);

/* Returns the array position of a department, or -1 if not found */
int findDepartmentIndex(const char name[]);

/* Accessors used by the Reports module */
int getDepartmentCount(void);
double getDepartmentAllocated(int index);
double getDepartmentSpent(int index);
void getDepartmentName(int index, char destination[]);

#endif
