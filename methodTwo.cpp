#include <iostream>
#include <vector>
#include <time.h>

using std::cout;
using std::endl;
using std::vector;

vector<double> methodTwo(vector<double> best, vector<double> randomSolution, int r1, int currentElement, int currentIter)
{
    double levy{};
    vector<double> y{};
    vector<double> x{};
    vector<int> DOne{};
    vector<double> r;
    vector<double> theta{};
    vector<double> prospectiveLocation{};
    double U{};
    double w{};
    double theta1{};
    double performance{};

    // evaluating levy
    double s{};
    double u{};
    double sigma, v, beta;
    U = 0.00565;
    w = 0.005;

    s = 0.01;
    sigma = 0.6966;
    beta = 1.5;

    srand((unsigned)time(NULL));
    u = (double)rand() / RAND_MAX;
    v = (double)rand() / RAND_MAX;

    levy = s * (u * sigma) / (pow(v, 1 / (double)beta));

    if (currentElement == 0 && currentIter == 0)
    {

        cout << "s: " << s << "\nu: " << u << "\nsigma: " << sigma << "\nv: " << v << "\nlevy" << levy << std::endl;
    }

    // we have to pop the last element from x... and the random Solution
    best.pop_back();
    randomSolution.pop_back();

    for (auto x : best)
    {
        x *= levy;
    }

    if (currentElement == 0 && currentIter == 0)
    {
        // displaying best after multiplication with levy
        for (auto y : best)
        {
            cout << y << " ";
        }
        cout << endl;
    }

    // evaulating x and y

    for (int i{1}; i <= best.size(); i++)
    {
        DOne.push_back(i);
    }

    for (int i{0}; i < DOne.size(); i++)
    {
        double val = r1 + (U * DOne.at(i));
        r.push_back(val);
    }

    theta1 = (3 * M_PI) / 2;
    for (int i{0}; i < DOne.size(); i++)
    {
        double value = -w * DOne.at(i) + theta1;
        theta.push_back(value);
    }

    for (int i{0}; i < DOne.size(); i++)
    {
        y.push_back(r.at(i) * cos(theta.at(i)));
    }

    for (int i{0}; i < DOne.size(); i++)
    {
        x.push_back(r.at(i) * sin(theta.at(i)));
    }

    // Where we display the values for the sake of demonstration
    if (currentElement == 0 && currentIter == 0)
    {
        cout << "Displaying D1\n";
        for (auto x : DOne)
        {
            cout << x << " ";
        }
        cout << endl;

        cout << "Displaying r\n";
        for (auto x : r)
        {
            cout << x << " ";
        }
        cout << endl;

        cout << "Theta One " << theta1 << endl;

        cout << "Displaying Theta" << endl;
        for (auto x : theta)
        {
            cout << x << " ";
        }
        cout << endl;

        cout << "Displaying y " << endl;
        for (auto x : y)
        {
            cout << x << " ";
        }
        cout << endl;

        cout << "Displaying x " << endl;
        for (auto parts : x)
        {
            cout << parts << " ";
        }
        cout << endl;
    }

    // calculating the propective location
    for (int i{0}; i < DOne.size(); i++)
    {
        double value{};
        double randn{};
        randn = (double)rand() / RAND_MAX;
        value = (best.at(i) * levy) + randomSolution.at(i) + ((y.at(i) - x.at(i)) * randn);

        if (currentElement == 0 && currentIter == 0 && i == 0)
        {
            // for the sake of demonstration
            cout << "randn used for first element: " << randn << endl;
        }
        prospectiveLocation.push_back(value);
    }

    if (currentElement == 0 && currentIter == 0)
    {
        cout << "New Location before boundary check\n";
        for (auto j : prospectiveLocation)
        {
            cout << j << " ";
        }
        cout << std::endl;
    }

    // carrying out boundary check
    prospectiveLocation = checkBoundaries(prospectiveLocation);

    if (currentElement == 0 && currentIter == 0)
    {
        cout << "New Location after boundary check\n";
        for (auto j : prospectiveLocation)
        {
            cout << j << " ";
        }
        cout << std::endl;
    }

    performance = objectiveFunction(prospectiveLocation);
    // inserting the performance at the end of the vector of new locations X(t+1)
    prospectiveLocation.push_back(performance);

    if (currentElement == 0 && currentIter == 0)
    {
        cout << "Testing new Location with performance\n";
        for (auto j : prospectiveLocation)
        {
            cout << j << " ";
        }
        cout << std::endl;
    }

    return prospectiveLocation;
}