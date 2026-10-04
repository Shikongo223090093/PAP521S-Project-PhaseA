#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SUPPLIERS 20

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);

/* Builds a sentence such as "ABC Supplies operates in Windhoek." */
void buildSupplierDescription(int index, char description[]);

int getSupplierCount(void);

#ifdef __cplusplus
}
#endif

#endif
