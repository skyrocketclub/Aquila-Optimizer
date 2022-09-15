#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>

using std::cout;
using std::endl;
using std::vector;

vector<double> methodFour(vector<double> best, vector<double> currentElement, int currentIteration, int maxIteration)
{
    vector<double> prospectiveLocation{};

    double performance{};
    double random1{};
    double random2{};
    double random3{};
    double QF{};
    double G1{};
    double G2{};

    // evaluating levy
    double s{};
    double u{};
    double sigma, v, beta, levy;

    s = 0.01;
    sigma = 0.6966;
    beta = 1.5;

    srand((unsigned)time(NULL));
    u = (double)rand() / RAND_MAX;
    v = (double)rand() / RAND_MAX;

    levy = s * (u * sigma) / (pow(v, 1 / (double)beta));

    random1 = (double)rand() / RAND_MAX;

    QF = pow(currentIteration, pow((1 - maxIteration), 2));
    G1 = 2 * random1 - 1;
    G2 = 2 * (1 - (currentIteration / maxIteration));

    best.pop_back();
    currentElement.pop_back();

    for (int i{0}; i < best.size(); i++)
    {
        double value{};
        random2 = (double)rand() / RAND_MAX;
        random3 = (double)rand() / RAND_MAX;

        value = QF * best.at(i) - (G1 * currentElement.at(i) * random2) - G2 * levy + random3 * G1;
        prospectiveLocation.push_back(value);
    }

    prospectiveLocation = checkBoundaries(prospectiveLocation);
    performance = objectiveFunction(prospectiveLocation);
    prospectiveLocation.push_back(performance);

    return prospectiveLocation;
}