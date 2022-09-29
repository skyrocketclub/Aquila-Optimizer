// Continue from
/*
Look into why the values from the objective function are high...
*/

/*
    PSEUDOCODE FOR AQUILA ALGORITHM
    1. Initialize Algorithm Parameters and Population Randomly
    Xij = rand x (UB - LB) + LB
    Xbest is chosen

    2. Check While (Current Iteration <= Maximum Iteration)

    {

    3. Evaluate Agents Performance using Fitness Functions // by putting them in the objective function in this case and seeing which of the agents gives you a more desirable result...

    4. Select Best Among all based on Fitness Values

    5. For Population 1 : N, DO the following
        {
            6. Updates Agents Locations Mean Value

            7. Update Parameters such as Levy's Flight, x, y, G1, G2, and the others that need updating

            8. Check if (Current Iteration <= (2/3) * Maximum Iterations)
            {
                    if(rand<=0.5){
                        Method 1 to obtain the current solution
                        then greedy selection
                    }else{
                        Method 2 to obtain the current solution
                        then greedy selection
                    }
            }   else{
                if(rand<=0.5){
                    Method 3 to obtain the current solution
                    then greedy selection
                }else{
                    Method 4 to obtain the current solution
                    then greedy selection
                }
            }

        }
        Evaluate Agents Performance using Fitness Functions // by putting them in the objective function in this case and seeing which of the agents gives you a more desirable result...

        Iteration ++;
    }

*/
#include <iostream>
#include <vector>
#include <time.h>

#include "helper.cpp"
#include "methodOne.cpp"
#include "methodTwo.cpp"
#include "methodThree.cpp"
#include "methodFour.cpp"
#include "chooseBest.cpp"

using std::cin;
using std::cout;
using std::vector;

// Parameter initialization
// exploitation adjustment parameters
double ALPHA = 0.1;
double GAMMA = 0.1;

int populationSize = 5;
int maxIter = 300; // maximum number of iterations
int currentIter = 0;

int main()
{
    // initialize the population here by editing the factor boundaries

    vector<vector<double>> factorBoundaries;
    factorBoundaries = {{5.0, 20.0}, {4.5, 6.0}, {60.0, 90.0}, {3.0, 6.0}, {15.0, 30.0}};

    // Getting the randomly initialised matrix
    vector<vector<double>> Population = randomInitializer(factorBoundaries, populationSize);
    //--------------------------

    for (auto m : Population)
    {
        for (auto n : m)
        {
            cout << n << " ";
        }
        cout << std::endl;
    }
    //--------------------------

    // best signifies whether the user wishes the maximum possible or minimum possible input...
    int best{};
    cout << "1 - Maximize\n2 - Minimize\nchoice: ";
    cin >> best;

    vector<double> bestSolution{};
    vector<double> mean{};
    vector<vector<double>> allBest{};

    while (currentIter < maxIter)
    {
        // For now, the best and the mean vectors have the objective function values attached...
        srand((unsigned)time(NULL)); // seeding the random numbers
        best == 1 ? bestSolution = chooseMax(Population) : bestSolution = chooseMin(Population);

        //--------------------
        if (currentIter == 0)
        {
            cout << "Testing Best\n";
            for (auto j : bestSolution)
            {
                cout << j << " ";
            }
            cout << std::endl;
        }

        // ----------------------------

        // Looping through all the elements

        for (int i{0}; i < populationSize; i++)
        {
            mean = meanSolution(Population);

            if (i == 0 && currentIter == 0)
            {
                //-------------------------------------------
                cout << "Testing Mean\n";
                for (auto x : mean)
                {
                    cout << x << " ";
                }
                //--------------------------------------------
            }

            if (currentIter <= ((double)2 / 3) * maxIter)
            {

                // random number between 0 & 1...
                double randomNumber = (float)rand() / RAND_MAX;

                // displaying the values for the first element in the first iteration...
                if (currentIter == 0 && i == 0)
                {
                    cout << "Showing steps for the first element in the first iteration\n";
                    cout << "\nrand chosen: " << randomNumber << std::endl;
                }

                if (randomNumber <= 0.5)
                {
                    // Method 1
                    // displaying the values for the first element in the first iteration...
                    if (currentIter == 0 && i == 0)
                    {
                        cout << "Using Method 1 since random Number: " << randomNumber << endl;
                    }

                    vector<double> prospectiveLocation{};
                    prospectiveLocation = methodOne(bestSolution, mean, currentIter, maxIter, i);

                    // carrying out the greedy selection
                    if (best == 1)
                    {
                        // Maximize
                        if (prospectiveLocation.back() > Population.at(i).back())
                        {
                            // Replacement
                            // displaying the values for the first element in the first iteration...
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " > " << Population.at(i).back() << " , replacement occurs...\n";
                            }
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() <= Population.at(i).back())
                        {
                            // No Replacement
                            // displaying the values for the first element in the first iteration...
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " !> " << Population.at(i).back() << " , replacement does not occur...\n";
                            }
                        }
                    }
                    else
                    {
                        // Minimize
                        if (prospectiveLocation.back() < Population.at(i).back())
                        {
                            // displaying the values for the first element in the first iteration...
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " < " << Population.at(i).back() << " , replacement occurs...\n";
                            }
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() >= Population.at(i).back())
                        {
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " !< " << Population.at(i).back() << " , replacement does not occur...\n";
                            }
                        }
                    }
                }
                else
                {
                    // Method 2
                    if (currentIter == 0 && i == 0)
                    {
                        cout << "Using Method 2 since random Number: " << randomNumber << endl;
                    }

                    srand((unsigned)time(NULL));
                    vector<double> prospectiveLocation{};
                    vector<double> randomsolution{};

                    int randomSolutionIndex{};
                    int r1{15};

                    randomSolutionIndex = rand() % populationSize;
                    randomsolution = Population.at(randomSolutionIndex);

                    prospectiveLocation = methodTwo(bestSolution, randomsolution, r1, i, currentIter);

                    // Greedy Selection
                    if (best == 1)
                    {
                        // Maximize
                        if (prospectiveLocation.back() > Population.at(i).back())
                        {
                            // Replacement
                            // displaying the values for the first element in the first iteration...
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " > " << Population.at(i).back() << " , replacement occurs...\n";
                            }
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() <= Population.at(i).back())
                        {
                            // No Replacement
                            // displaying the values for the first element in the first iteration...
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " !> " << Population.at(i).back() << " , replacement does not occur...\n";
                            }
                        }
                    }
                    else
                    {
                        // Minimize
                        if (prospectiveLocation.back() < Population.at(i).back())
                        {
                            // displaying the values for the first element in the first iteration...
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " < " << Population.at(i).back() << " , replacement occurs...\n";
                            }
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() >= Population.at(i).back())
                        {
                            if (i == 0 && currentIter == 0)
                            {
                                cout << "Since " << prospectiveLocation.back() << " !< " << Population.at(i).back() << " , replacement does not occur...\n";
                            }
                        }
                    }
                }
            }
            else
            {
                double randomNumber = (float)rand() / RAND_MAX;
                if (randomNumber <= 0.5)
                {
                    // Method 3

                    vector<double> prospectiveLocation{};

                    prospectiveLocation = methodThree(bestSolution, mean, factorBoundaries);
                    if (best == 1)
                    {
                        // Maximize
                        if (prospectiveLocation.back() > Population.at(i).back())
                        {
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() <= Population.at(i).back())
                        {
                            // No repacement occurs...
                        }
                    }
                    else
                    {
                        // Minimize
                        if (prospectiveLocation.back() < Population.at(i).back())
                        {
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() >= Population.at(i).back())
                        {
                            // No repacement occurs...
                        }
                    }
                }
                else
                {
                    // Method 4
                    vector<double> prospectiveLocation{};
                    prospectiveLocation = methodFour(bestSolution, Population.at(i), currentIter, maxIter);

                    if (best == 1)
                    {
                        // Maximize
                        if (prospectiveLocation.back() > Population.at(i).back())
                        {
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() <= Population.at(i).back())
                        {
                            // No repacement occurs...
                        }
                    }
                    else
                    {
                        // Minimize
                        if (prospectiveLocation.back() < Population.at(i).back())
                        {
                            Population.at(i) = prospectiveLocation;
                        }
                        else if (prospectiveLocation.back() >= Population.at(i).back())
                        {
                            // No repacement occurs...
                        }
                    }
                }
            }
        }

        allBest.push_back(bestSolution);
        currentIter++;
    }

    cout << endl
         << endl
         << "Displaying the best solutions of size " << allBest.size() << std::endl;
    for (size_t i{0}; i < allBest.size(); i++)
    {
        cout << "Iteration " << i + 1 << ": ";
        for (auto x : allBest.at(i))
        {
            cout << x << " ";
        }
        cout << endl;
    }
}