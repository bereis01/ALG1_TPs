#include <iostream>

#include "rock.hpp"

// Main function.
int main()
{
    // Initializes the problem's variables.
    int numOfFriends, numOfShows;
    std::cin >> numOfFriends >> numOfShows;

    // Evaluates each instance of the problem.
    while (numOfFriends || numOfShows)
    {
        // Simulates the app and prints the best shows' interval.
        ShowApp rockInRio(numOfFriends, numOfShows);
        rockInRio.initializeEvaluations();
        rockInRio.generateSchedule();

        // Gathers the information for the next instance.
        std::cin >> numOfFriends >> numOfShows;
    }

    return 0;
}