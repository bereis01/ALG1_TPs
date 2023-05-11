#include <iostream>

#include "store.hpp"

int main()
{
    // Inputs the quantity of test cases and executes each one.
    int numOfTestCases;
    for (std::cin >> numOfTestCases; numOfTestCases > 0; numOfTestCases--)
    {
        // Inputs the amount of fabric for the current instance and initializes the Store object accordingly.
        int qtdOfFabric;
        std::cin >> qtdOfFabric;
        Store storeInstance(qtdOfFabric);

        // Inputs the vector of prices, organized in order of arrival in the store.
        storeInstance.inputFabricPrices();

        // Computes and outputs the maximum amount of display items for this instance.
        std::cout << storeInstance.maximizeDisplayItems() << std::endl;
    }

    return 0;
}