#ifndef STORE_H
#define STORE_H

#include <iostream>

class Store
{
public:
    // Constructor and destructor.
    Store(int _qtdOfFabric);
    ~Store();

    // Inputs the prices of each fabric.
    void inputFabricPrices();

    // Returns the maximum amount of items that can be displayed.
    int maximizeDisplayItems();

private:
    // Class' attributes.
    int qtyOfFabric;
    int *fabricPrices;
};

#endif