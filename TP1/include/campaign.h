#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include <stdio.h>
#include <stdlib.h>

// Data structure to store all the campaign's related information.
typedef struct campaignType
{
    // Basic variables.
    int numOfElectors;
    int numOfProposals;
    int **electorsPreferences;

    // Graph used to store the survey's results.
    int **surveyGraph;
} Campaign;

// Associated procedures' signature.
void initializeCampaign(Campaign *campaign, int numOfElectors, int numOfProposals);
int **inputElectorsPreferences(int numOfElectors);
int **generateSurveyGraph(int **electorsPreferences, int numOfElectors, int numOfProposals);
void processCampaign(Campaign *campaign);
int BFS(int **graph, int numOfNodes, int start);
void deleteCampaign(Campaign *campaign);

#endif