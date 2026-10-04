#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 50

/* Menu and operations */
void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void displayPayslip(void);

/* Reusable calculation functions */
double calculateSalary(double basic, double housing, double transport);
double calculateTax(double grossSalary);
double calculateNetSalary(double grossSalary, double tax);

/* Returns the array position of an employee ID, or -1 if not found */
int findEmployeeIndex(int id);

/* Accessors used by the Reports module */
int getEmployeeCount(void);
double getEmployeeGross(int index);
double getEmployeeNet(int index);
void getEmployeeName(int index, char destination[]);

#endif
