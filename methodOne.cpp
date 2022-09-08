#include <iostream>
#include <vector>
#include <time.h>
// #include "helper.cpp"

using std::cout;
using std::vector;

vector<double> methodOne(vector<double> best, vector<double> mean, int currentIteration, int maxIter, int i)
{
    // pop the last elements of the best and the mean...

    // when you have gotten X(t+1)... you can get the new f(x), push it and send to main
    vector<double> newLocation;
    double random{};
    double performance{};

    best.pop_back();
    mean.pop_back();

    //--------------------
    if (i == 0)
    {
        cout << "Testing Best after popping back\n";
        for (auto j : best)
        {
            cout << j << " ";
        }
    }
    cout << std::endl;
    // ----------------------------

    srand((unsigned)time(NULL));
    random = (float)rand() / RAND_MAX;

    if (i == 0)
        cout << "Random Number: " << random << std::endl;

    // separating the Expanded Exploration into two parts a & b
    vector<double> a = best;
    vector<double> b = mean;

    for (size_t i{0}; i < a.size(); i++)
    {
        a.at(i) = a.at(i) * (1 - (currentIteration / (double)maxIter));
    }

    //--------------------
    // cout << "Testing a after math computations\n";
    // for (auto k : a)
    // {
    //     cout << k << " ";
    // }
    // cout << std::endl;
    // ----------------------------

    for (size_t i{0}; i < mean.size(); i++)
    {
        b.at(i) = b.at(i) - (best.at(i) * random);
    }

    //--------------------
    // cout << "Testing b\n";
    // for (auto j : b)
    // {
    //     cout << j << " ";
    // }
    // cout << std::endl;
    // ----------------------------

    for (size_t j{0}; j < a.size(); j++)
    {
        double x = a.at(j) + b.at(j);
        newLocation.push_back(x);
    }

    //--------------------
    if (i == 0)
    {
        cout << "New Location\n";
        for (auto j : newLocation)
        {
            cout << j << " ";
        }
        cout << std::endl;
    }
    // ----------------------------

    performance = objectiveFunction(newLocation);
    // inserting the performance at the end of the vector of new locations X(t+1)
    newLocation.push_back(performance);

    //--------------------
    if (i == 0)
    {
        cout << "Testing new Location with performance\n";
        for (auto j : newLocation)
        {
            cout << j << " ";
        }
        cout << std::endl;
    }
    // ----------------------------

    return newLocation;
}
