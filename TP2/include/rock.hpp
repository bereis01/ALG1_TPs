#ifndef ROCK_H
#define ROCK_H

#include <iostream>

// Class which models the friends' app.
class ShowApp
{
public:
    // Class's constructor and destructor.
    ShowApp(int _numOfFriends, int _numOfShows);
    ~ShowApp();

    // Class's methods.
    void initializeEvaluations();
    void generateSchedule();

private:
    // Class's attributes.
    int numOfFriends;
    int numOfShows;
    float **friendsEvaluation;
    float *showsEvaluation;

    // Auxiliary methods.
    float generateScheduleRecursive(int &startShow, int &endShow, int leftIndex, int rightIndex);
};

#endif