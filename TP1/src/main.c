#include <stdio.h>
#include <stdlib.h>

#include "campaign.h"

// Main function.
int main()
{
    // Initializes the variables containing the problem's parameters.
    int numOfElectors, numOfProposals;
    scanf("%d %d", &numOfElectors, &numOfProposals);

    // Iterates through all the instances of the problem.
    while (numOfElectors != 0 || numOfProposals != 0)
    {
        // Initializes the structure to storage the campaign's data.
        Campaign campaign;
        initializeCampaign(&campaign, numOfElectors, numOfProposals);

        // Executes the algorithm which will decide if the problem is satisfiable.
        processCampaign(&campaign);

        // Terminates the initialized campaign.
        deleteCampaign(&campaign);

        // Inputs the instance's parameters for the next iteration.
        scanf("%d %d", &numOfElectors, &numOfProposals);
    }

    return 0;
}