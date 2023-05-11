#include "store.hpp"

Store::Store(int _qtyOfFabric)
{
    // Initializes the class' attributes.
    this->qtyOfFabric = _qtyOfFabric;
    this->fabricPrices = nullptr;
}

Store::~Store()
{
    // Deallocates all the allocated memory.
    delete[] this->fabricPrices;
}

void Store::inputFabricPrices()
{
    // Allocates the necessary memory.
    this->fabricPrices = new int[this->qtyOfFabric];

    // Gathers the information from the standard input.
    for (int i = 0; i < this->qtyOfFabric; i++)
    {
        std::cin >> this->fabricPrices[i];
    }
}

int Store::maximizeDisplayItems()
{
    // Defines auxiliary structures.
    int fabricDisplayLeft[this->qtyOfFabric];
    int fabricDisplayRight[this->qtyOfFabric];
    for (int i = 0; i < this->qtyOfFabric; i++)
    {
        fabricDisplayLeft[i] = 1;
        fabricDisplayRight[i] = 1;
    }

    // Maximizes the number of choices from both sides.
    for (int i = this->qtyOfFabric; i >= 0; i--)
    {
        int maxValue = 0;
        for (int j = i + 1; j < this->qtyOfFabric; j++)
        {
            if (fabricDisplayLeft[j] > maxValue && this->fabricPrices[j] < this->fabricPrices[i])
            {
                maxValue = fabricDisplayLeft[j];
            }
        }
        fabricDisplayLeft[i] += maxValue;
    }

    for (int i = this->qtyOfFabric; i >= 0; i--)
    {
        int maxValue = 0;
        for (int j = i + 1; j < this->qtyOfFabric; j++)
        {
            if (fabricDisplayRight[j] > maxValue && this->fabricPrices[j] > this->fabricPrices[i])
            {
                maxValue = fabricDisplayRight[j];
            }
        }
        fabricDisplayRight[i] += maxValue;
    }

    // Chooses the pivot which maximizes the combination of both sides.
    int maximizedQuantity = 0;
    for (int i = 0; i < this->qtyOfFabric; i++)
    {
        int combinedValue = fabricDisplayLeft[i] + fabricDisplayRight[i] - 1;

        if (combinedValue > maximizedQuantity)
        {
            maximizedQuantity = combinedValue;
        }
    }

    // Returns the maximized quantity.
    return maximizedQuantity;
}