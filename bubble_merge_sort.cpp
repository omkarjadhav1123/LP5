#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to perform parallelized Bubble Sort
void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    int i, j;

#pragma omp parallel for private(i, j) shared(arr)
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap elements if they are in the wrong order
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform parallelized Merge Sort
void merge(vector<int> &arr, int low, int mid, int high)
{
   int left=low,right=mid+1;
   vector<int> temp;
   while(left<=mid && right<=high){
       if(arr[left]>arr[right]){
           temp.push_back(arr[right]);
           right++;
       }
       else {
           temp.push_back(arr[left]);
           left++;
       }
   }
   while(left<=mid){
       temp.push_back(arr[left]);
       left++;
   }
   while(right<=high){
       temp.push_back(arr[right]);
       right++;
   }
   for(int i=low;i<=high;i++){
       arr[i]=temp[i-low];
   }
}

// Function to perform parallelized Merge Sort
void parallelMergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            parallelMergeSort(arr, left, middle);
#pragma omp section
            parallelMergeSort(arr, middle + 1, right);
        }

        merge(arr, left, middle, right);
    }
}

int main()
{
    int n;
    cout<<"Enter number of elements: ";
    cin>>n;
    cout<<"\nEnter elements: ";
    vector<int> data(n);
    for(int i=0;i<n;i++)cin>>data[i];
    // Measure Parallel Bubble Sort Time
    vector<int> bubbleSortedData = data; // Make a copy for bubble sort
    cout << "Sorting array of size " << n << " using Parallel Bubble Sort..." << endl;
    parallelBubbleSort(bubbleSortedData);
    for(int i=0;i<n;i++)cout<<bubbleSortedData[i]<<" ";
    
    // Measure Parallel Merge Sort Time
    vector<int> mergeSortedData = data; // Make a copy for merge sort
    cout << "\nSorting array of size " << n << " using Parallel Merge Sort..." << endl;
    parallelMergeSort(mergeSortedData, 0, mergeSortedData.size() - 1);
    for(int i=0;i<n;i++)cout<<mergeSortedData[i]<<" ";

    return 0;
}

/*
openMP execution
g++ -fopenmp programName.cpp -o programName
./programName
*/