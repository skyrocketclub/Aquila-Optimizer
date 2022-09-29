#include <iostream>
#include <vector>
#include <time.h>

using std::cout;
using std::endl;
using std::vector;

vector<double> methodThree(vector<double> best, vector<double> mean, vector<vector<double>> factorBoundaries)
{
    vector<double> prospectiveLocation{};
    vector<double> boundaryDifference{};
    vector<double> lowerBoundaries{};

    // exploitaion adjustment parameters
    double alpha{0.1};
    double gamma{0.1};
    double randomNumber1{};
    double randomNumber2{};
    double performance{};

    best.pop_back();
    mean.pop_back();

    srand((unsigned)time(NULL));

    // populating (UB-LB)
    for (int i{0}; i < factorBoundaries.size(); i++)
    {
        double value = factorBoundaries.at(i).at(1) - factorBoundaries.at(i).at(0);
        boundaryDifference.push_back(value);
        lowerBoundaries.push_back(factorBoundaries.at(i).at(0));
    }

    for (int i{0}; i < best.size(); i++)
    {
        double value{};
        randomNumber1 = (double)rand() / RAND_MAX;
        randomNumber2 = (double)rand() / RAND_MAX;
        value = (best.at(i) - mean.at(i)) * alpha - randomNumber1 + ((boundaryDifference.at(i)) * randomNumber2 + lowerBoundaries.at(i)) * gamma;
        prospectiveLocation.push_back(value);
    }

    prospectiveLocation = checkBoundaries(prospectiveLocation);
    performance = objectiveFunction(prospectiveLocation);
    prospectiveLocation.push_back(performance);

    return prospectiveLocation;
}