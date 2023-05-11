#include "campaign.h"

// Associated procedures' implementation.
// Initializes the data structure containing the campaign's information.
void initializeCampaign(Campaign *campaign, int numOfElectors, int numOfProposals)
{
    campaign->numOfElectors = numOfElectors;
    campaign->numOfProposals = numOfProposals + 1;
    campaign->electorsPreferences = inputElectorsPreferences(numOfElectors);
    campaign->surveyGraph = generateSurveyGraph(campaign->electorsPreferences, campaign->numOfElectors, campaign->numOfProposals);
}

// Initializes the data structure containing each elector's preferences.
int **inputElectorsPreferences(int numOfElectors)
{
    // Allocates the necessary memory.
    int **electorsPreferences;
    electorsPreferences = (int **)malloc(numOfElectors * sizeof(int *));
    for (int i = 0; i < numOfElectors; i++)
    {
        electorsPreferences[i] = (int *)malloc(4 * sizeof(int));
    }

    // Inputs each elector's preference from the standard input.
    for (int i = 0; i < numOfElectors; i++)
    {
        scanf("%d %d %d %d", &electorsPreferences[i][0], &electorsPreferences[i][1], &electorsPreferences[i][2], &electorsPreferences[i][3]);
    }

    return electorsPreferences;
}

// Initializes the data structure (graph) containing the information regarding the survey.
int **generateSurveyGraph(int **electorsPreferences, int numOfElectors, int numOfProposals)
{
    // Allocates the necessary memory.
    int **surveyGraph;
    surveyGraph = (int **)calloc((2 * numOfProposals), sizeof(int *));
    for (int i = 0; i < (2 * numOfProposals); i++)
    {
        surveyGraph[i] = (int *)calloc((2 * numOfProposals), sizeof(int));
    }

    // Models the survey as a 2-SAT problem.
    for (int i = 0; i < numOfElectors; i++)
    {
        int x1 = electorsPreferences[i][0];
        int notx1 = x1 + numOfProposals;

        int x2 = electorsPreferences[i][1];
        int notx2 = x2 + numOfProposals;

        if (x1 != 0 && x2 != 0)
        {
            surveyGraph[notx1][x2] = 1;
            surveyGraph[notx2][x1] = 1;
        }
        else if (x1 != 0 && x2 == 0)
        {
            surveyGraph[notx1][0] = 1;
            surveyGraph[numOfProposals][x1] = 1;

            surveyGraph[notx1][numOfProposals] = 1;
            surveyGraph[0][x1] = 1;
        }
        else if (x1 == 0 && x2 != 0)
        {
            surveyGraph[notx2][0] = 1;
            surveyGraph[numOfProposals][x2] = 1;

            surveyGraph[notx2][numOfProposals] = 1;
            surveyGraph[0][x2] = 1;
        }

        int y1 = electorsPreferences[i][2];
        int noty1 = y1 + numOfProposals;

        int y2 = electorsPreferences[i][3];
        int noty2 = y2 + numOfProposals;

        if (y1 != 0 && y2 != 0)
        {
            surveyGraph[y1][noty2] = 1;
            surveyGraph[y2][noty1] = 1;
        }
        else if (y1 != 0 && y2 == 0)
        {
            surveyGraph[y1][0] = 1;
            surveyGraph[numOfProposals][noty1] = 1;

            surveyGraph[y1][numOfProposals] = 1;
            surveyGraph[0][noty1] = 1;
        }
        else if (y1 == 0 && y2 != 0)
        {
            surveyGraph[y2][0] = 1;
            surveyGraph[numOfProposals][noty2] = 1;

            surveyGraph[y2][numOfProposals] = 1;
            surveyGraph[0][noty2] = 1;
        }
    }

    return surveyGraph;
}

// Evaluates the modelled graph and determines if there is a proposal assignment that satisfies the established contiditions.
void processCampaign(Campaign *campaign)
{
    for (int i = 0; i < campaign->numOfProposals; i++)
    {
        int node = BFS(campaign->surveyGraph, (2 * campaign->numOfProposals), i);
        int notNode = BFS(campaign->surveyGraph, (2 * campaign->numOfProposals), i + campaign->numOfProposals);

        if (node == 1 && notNode == 1)
        {
            printf("nao\n");
            return;
        }
    }
    printf("sim\n");
    return;
}

// BFS algorithm. Used to process the campaign.
int BFS(int **graph, int numOfNodes, int start)
{
    // Creates the auxiliary variables, which will control both lists.
    int explorePointer, exploredCount;

    // Creates the list which will hold the reachable nodes.
    int nodeList[numOfNodes];
    for (int i = 0; i < numOfNodes; i++)
    {
        nodeList[i] = -1;
    }

    // Creates the list which will record which node has already been reached.
    int exploredNodes[numOfNodes];
    for (int i = 0; i < numOfNodes; i++)
    {
        exploredNodes[i] = 0;
    }

    // Adds the start node to both lists.
    nodeList[0] = start;
    explorePointer = 0;
    exploredCount = 1;
    exploredNodes[start] = 1;

    // Executes the BFS search over the graph.
    while (explorePointer < numOfNodes && nodeList[explorePointer] != -1)
    {
        for (int i = 0; i < numOfNodes; i++)
        {
            if (graph[nodeList[explorePointer]][i] == 1 && exploredNodes[i] == 0)
            {
                nodeList[exploredCount] = i;
                exploredCount++;
                exploredNodes[i] = 1;

                // If notStart is reachable from start or vice-versa, returns 1.
                if (start < numOfNodes / 2)
                {
                    if (i == start + (numOfNodes / 2))
                    {
                        return 1;
                    }
                }
                else
                {
                    if (i == start - (numOfNodes / 2))
                    {
                        return 1;
                    }
                }
            }
        }

        explorePointer++;
    }

    // Else, returns 0.
    return 0;
}

// Deallocates all the memory allocated.
void deleteCampaign(Campaign *campaign)
{
    // Deallocates the data structure containing the electors' preferences.
    for (int i = 0; i < campaign->numOfElectors; i++)
    {
        free(campaign->electorsPreferences[i]);
    }
    free(campaign->electorsPreferences);

    // Deallocates the data structure containing the survey's information.
    for (int i = 0; i < (2 * campaign->numOfProposals); i++)
    {
        free(campaign->surveyGraph[i]);
    }
    free(campaign->surveyGraph);
}