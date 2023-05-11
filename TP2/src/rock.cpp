#include "rock.hpp"

// Constructor. Initializes the class's variables.
ShowApp::ShowApp(int _numOfFriends, int _numOfShows)
{
    this->numOfFriends = _numOfFriends;
    this->numOfShows = _numOfShows;
    this->friendsEvaluation = nullptr;
    this->showsEvaluation = nullptr;
}

// Destructor. Utilized to deallocate all the memory allocated.
ShowApp::~ShowApp()
{
    for (int i = 0; i < this->numOfFriends; i++)
    {
        delete[] this->friendsEvaluation[i];
    }
    delete[] this->friendsEvaluation;

    delete[] this->showsEvaluation;
}

// Initializes the data structures containing each friend's evaluation of every show and each show's total evaluation.
void ShowApp::initializeEvaluations()
{
    // Allocates the memory.
    this->friendsEvaluation = new float *[this->numOfFriends];
    for (int i = 0; i < this->numOfFriends; i++)
    {
        this->friendsEvaluation[i] = new float[this->numOfShows];
    }

    this->showsEvaluation = new float[this->numOfShows];

    // Reads the information about each friend's evaluation from the input.
    for (int i = 0; i < this->numOfFriends; i++)
    {
        for (int j = 0; j < this->numOfShows; j++)
        {
            std::cin >> this->friendsEvaluation[i][j];
        }
    }

    // Calculates each show's total evaluation based on the group's evaluations.
    for (int i = 0; i < this->numOfShows; i++)
    {
        this->showsEvaluation[i] = 0;
        for (int j = 0; j < this->numOfFriends; j++)
        {
            this->showsEvaluation[i] += this->friendsEvaluation[j][i];
        }
    }
}

// Based on the shows' evaluation, generates the schedule which maximizes satisfaction.
void ShowApp::generateSchedule()
{
    // Calculates and outputs the first and last shows of the maximized schedule.
    int startShow, endShow;
    this->generateScheduleRecursive(startShow, endShow, 0, this->numOfShows - 1);
    std::cout << startShow + 1 << " " << endShow + 1 << std::endl;
}

// Auxiliary recursive call for the generateSchedule method.
float ShowApp::generateScheduleRecursive(int &startShow, int &endShow, int leftIndex, int rightIndex)
{
    // Case in which the subarray has only one element.
    if (leftIndex == rightIndex)
    {
        startShow = leftIndex;
        endShow = leftIndex;
        return this->showsEvaluation[leftIndex];
    }

    // Cases in which there is more than one element.
    // Calculates the middle of the array.
    int middlePoint = leftIndex + ((rightIndex - leftIndex) / 2);

    // Calculates the maximum subarray on the left half.
    int leftStartShow, leftEndShow;
    float leftSum = this->generateScheduleRecursive(leftStartShow, leftEndShow, leftIndex, middlePoint);

    // Calculates the maximum subarray on the right half.
    int rightStartShow, rightEndShow;
    float rightSum = this->generateScheduleRecursive(rightStartShow, rightEndShow, middlePoint + 1, rightIndex);

    // Calculates the maximum subarray passing through the middle point.
    float sumAux;
    int middleStartShow, middleEndShow;

    float leftHalfSum = this->showsEvaluation[middlePoint];
    middleStartShow = middlePoint;
    sumAux = leftHalfSum;
    for (int i = middlePoint - 1; i >= leftIndex; i--)
    {
        sumAux += this->showsEvaluation[i];

        if (sumAux >= leftHalfSum)
        {
            leftHalfSum = sumAux;
            middleStartShow = i;
        }
    }

    float rightHalfSum = this->showsEvaluation[middlePoint + 1];
    middleEndShow = middlePoint + 1;
    sumAux = rightHalfSum;
    for (int i = middlePoint + 2; i <= rightIndex; i++)
    {
        sumAux += this->showsEvaluation[i];

        if (sumAux >= rightHalfSum)
        {
            rightHalfSum = sumAux;
            middleEndShow = i;
        }
    }

    float middleSum = leftHalfSum + rightHalfSum;

    // Calculates the size of every subarray as a tiebreaker criteria.
    int middleSize = middleEndShow - middleStartShow + 1;
    int leftSize = leftEndShow - leftStartShow + 1;
    int rightSize = rightEndShow - rightStartShow + 1;

    // Compares all three (left subarray, right subarray, middle subarray) and returns the maximum one.
    if (middleSum > rightSum)
    {
        if (middleSum > leftSum)
        {
            // Middle subarray has the highest sum.
            startShow = middleStartShow;
            endShow = middleEndShow;
            return middleSum;
        }
        else if (middleSum < leftSum)
        {
            // Left subarray has the highest sum.
            startShow = leftStartShow;
            endShow = leftEndShow;
            return leftSum;
        }
        else // Middle sum = left sum.
        {
            if (middleSize > leftSize)
            {
                // Middle has most shows.
                startShow = middleStartShow;
                endShow = middleEndShow;
                return middleSum;
            }
            else if (middleSize < leftSize)
            {
                // Left has most shows.
                startShow = leftStartShow;
                endShow = leftEndShow;
                return leftSum;
            }
            else
            {
                // Middle size = left size. Left sequence (the earliest) is returned as default.
                startShow = leftStartShow;
                endShow = leftEndShow;
                return leftSum;
            }
        }
    }
    else if (middleSum < rightSum)
    {
        if (rightSum > leftSum)
        {
            // Right subarray has the highest sum.
            startShow = rightStartShow;
            endShow = rightEndShow;
            return rightSum;
        }
        else if (rightSum < leftSum)
        {
            // Left subarray has the highest sum.
            startShow = leftStartShow;
            endShow = leftEndShow;
            return leftSum;
        }
        else // Right sum = left sum.
        {
            if (rightSize > leftSize)
            {
                // Right has most shows.
                startShow = rightStartShow;
                endShow = rightEndShow;
                return rightSum;
            }
            else if (rightSize < leftSize)
            {
                // Left has most shows.
                startShow = leftStartShow;
                endShow = leftEndShow;
                return leftSum;
            }
            else
            {
                // Right size = left size. Left sequence (the earliest) is returned as default.
                startShow = leftStartShow;
                endShow = leftEndShow;
                return leftSum;
            }
        }
    }
    else // Middle sum = right sum.
    {
        if (middleSum < leftSum)
        {
            // Left subarray has the highest sum.
            startShow = leftStartShow;
            endShow = leftEndShow;
            return leftSum;
        }
        else if (middleSum > leftSum)
        {
            if (middleSize < rightSize)
            {
                // Right has most shows.
                startShow = rightStartShow;
                endShow = rightEndShow;
                return rightSum;
            }
            else if (middleSize > rightSize)
            {
                // Middle has most shows.
                startShow = middleStartShow;
                endShow = middleEndShow;
                return middleSum;
            }
            else
            {
                // Middle size = right size. Middle sequence (the earliest) is returned as default.
                startShow = middleStartShow;
                endShow = middleEndShow;
                return middleSum;
            }
        }
        else // Left sum = middle sum = right sum.
        {
            if (middleSize > rightSize)
            {
                if (middleSize > leftSize)
                {
                    // Middle has most shows.
                    startShow = middleStartShow;
                    endShow = middleEndShow;
                    return middleSum;
                }
                else if (middleSize < leftSize)
                {
                    // Left has most shows.
                    startShow = leftStartShow;
                    endShow = leftEndShow;
                    return leftSum;
                }
                else
                {
                    // Middle size = left size. Left sequence (the earliest) is returned as default.
                    startShow = leftStartShow;
                    endShow = leftEndShow;
                    return leftSum;
                }
            }
            else if (middleSize < rightSize)
            {
                if (rightSize > leftSize)
                {
                    // Right has most shows.
                    startShow = rightStartShow;
                    endShow = rightEndShow;
                    return rightSum;
                }
                else if (rightSize < leftSize)
                {
                    // Left has most shows.
                    startShow = leftStartShow;
                    endShow = leftEndShow;
                    return leftSum;
                }
                else
                {
                    // Right size = left size. Left sequence (the earliest) is returned as default.
                    startShow = leftStartShow;
                    endShow = leftEndShow;
                    return leftSum;
                }
            }
            else // Middle size = right size.
            {
                if (middleSize < leftSize)
                {
                    // Left has most shows.
                    startShow = leftStartShow;
                    endShow = leftEndShow;
                    return leftSum;
                }
                else if (middleSize > leftSize)
                {
                    // Middle size = right size > left size. Middle sequence (the earliest) is returned as default.
                    startShow = middleStartShow;
                    endShow = middleEndShow;
                    return middleSum;
                }
                else
                {
                    // Middle size = right size = left size. Left sequence (the earliest) is returned as default.
                    startShow = leftStartShow;
                    endShow = leftEndShow;
                    return leftSum;
                }
            }
        }
    }
}