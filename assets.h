#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 30

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);

/* Accessors used by the Reports module */
int getAssetCount(void);
double getAssetValue(int index);

#endif
