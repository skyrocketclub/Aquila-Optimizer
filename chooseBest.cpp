#include <iostream>
#include <vector>

using std::vector;

vector<double> chooseMin(vector<vector<double>> &matrix)
{
    double smallest = 1000;
    vector<double> best;

    for (size_t i{0}; i < matrix.size(); i++)
    {
        if (matrix.at(i).back() < smallest)
        {
            best = matrix.at(i);
            smallest = matrix.at(i).back();
        }
    }
    return best;
}

vector<double> chooseMax(vector<vector<double>> &matrix)
{
    double biggest = 0;
    vector<double> best;

    for (size_t i{0}; i < matrix.size(); i++)
    {
        if (matrix.at(i).back() > biggest)
        {
            best = matrix.at(i);
            biggest = matrix.at(i).back();
        }
    }
    return best;
}