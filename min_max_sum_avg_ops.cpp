#include <iostream>
#include <vector>
#include <limits>
#include <omp.h>
using namespace std;
// Function to find the minimum value in an array using parallel reduction
int parallelMin(const vector<int> &data)
{
    int min_val = numeric_limits<int>::max();
#pragma omp parallel for reduction(min : min_val)
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (data[i] < min_val)
        {
            min_val = data[i];
        }
    }
    return min_val;
}
// Function to find the maximum value in an array using parallel reduction
int parallelMax(const vector<int> &data)
{
    int max_val = numeric_limits<int>::min();
#pragma omp parallel for reduction(max : max_val)
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (data[i] > max_val)
        {
            max_val = data[i];
        }
    }
    return max_val;
}
// Function to find the sum of elements in an array using parallel reduction
int parallelSum(const vector<int> &data)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (size_t i = 0; i < data.size(); ++i)
    {
        sum += data[i];
    }
    return sum;
}
// Function to find the average of elements in an array using parallel reduction
double
parallelAverage(const vector<int> &data)
{
    int sum = parallelSum(data);
    return static_cast<double>(sum) / data.size();
}
int main()
{
    vector<int> data = {5, 2, 8, 1, 7, 3, 9, 4, 6};
    // Min
    cout << "Minimum: " << parallelMin(data) << endl;
    // Max
    cout << "Maximum: " << parallelMax(data) << endl;
    // Sum
    cout << "Sum: " << parallelSum(data) << endl;
    // Average
    cout << "Average: " << parallelAverage(data) << endl;
    return 0;
}

/*
openMP execution
g++ -fopenmp programName.cpp -o programName
./programName
*/