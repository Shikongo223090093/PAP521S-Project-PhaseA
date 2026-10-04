#ifndef BUDGET_H
#define BUDGET_H

#define MAX_DEPARTMENTS 20

void budgetMenu(void);
void addBudget(void);
void displayBudgets(void);
void searchBudget(void);
void displayOverBudget(void);
double calculateRemaining(double budget, double expenditure);

#endif