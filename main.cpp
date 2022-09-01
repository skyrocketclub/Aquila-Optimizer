/*
    PSEUDOCODE FOR AQUILA ALGORITHM
    1. Initialize Algorithm Parameters and Population Randomly
    Xij = rand x (UB - LB) + LB
    Xbest is chosen

    2. Check While (Current Iteration <= Maximum Iteration)

    3. Evaluate Agents Performance using Fitness Functions

    4. Select Best Among all based on Fitness Values

    5. For Population 1 : N, DO the following

    6. Updates Agents Locations Mean Value

    7. Update Parameters such as Levy's Flight, Mean Value, x, y, G1, G2, and the others that need updating

    8. Check if (Current Iteration <=(2/3) *Maximum Iterations)
    {
            if(rand<=0.5){
                Method 1
            }else{
                Method 2
            }
    }   else{
        if(rand<=0.5){
            Method 3
        }else{
            Method 4
        }
    }
9. Display best Solution Found

*/
#include <iostream>
#include <vector>

#include "helper.cpp"
#include "methodOne.cpp"
#include "methodTwo.cpp"
#include "methodThree.cpp"
#include "methodFour.cpp"
#include "chooseBest.cpp"

using std::cin;
using std::cout;
using std::vector;

int main()
{
    // initialize the population here by editing the factor boundaries
    vector<vector<double>> factorBoundaries;
    factorBoundaries = {{5, 20}, {4.5, 6.0}, {60, 90}, {3, 6}, {15, 30}};

    // initialize certain paramters
    int populationSize = 3;
    int maxIter = 200; // maximum number of iterations
    int currentIter = 0;

    // Getting the randomly initialised matrix
    vector<vector<double>> initialPopulation = randomInitializer(factorBoundaries, populationSize);
    //--------------------------

    // for (auto m : initialPopulation)
    // {
    //     for (auto n : m)
    //     {
    //         cout << n << " ";
    //     }
    //     cout << std::endl;
    // }
    //--------------------------

    int best{};
    cout << "1 - Maximize\n2 - Minimize\nchoice: ";
    cin >> best;

    vector<double> bestSolution{};
    best == 1 ? bestSolution = chooseMax(initialPopulation) : chooseMin(initialPopulation);

    //--------------------
    // cout << "Testing Best\n";
    // for (auto j : bestSolution)
    // {
    //     cout << j << " ";
    // }
    // cout << std::endl;
    //----------------------------

    vector<double> mean = meanSolution(initialPopulation);

    //-------------------------------------------
    // cout << "Testing Mean\n";
    // for (auto x : mean)
    // {
    //     cout << x << " ";
    // }
    //--------------------------------------------

    while (currentIter < maxIter)
    {
    }
}