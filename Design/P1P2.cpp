#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

void ArrCPY(int arr[], int n, int arrcpy[])
{
    for (int i = 0; i < n; i++)
        arrcpy[i] = arr[i];
}

//=======================================================================================================

int maxSubarraySumBruteForce(int arr[], int size)
{
    int maxSum = arr[0];
    for (int i = 0; i < size; i++)
    {
        int currentSum = 0;
        for (int j = i; j < size; j++)
        {
            currentSum += arr[j];
            maxSum = max(maxSum, currentSum);
        }
    }
    return maxSum;
}

//=======================================================================================================

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int max(int a, int b, int c)
{
    return max(max(a, b), c);
}

int maxCrossingSum(int arr[], int l, int m, int h)
{
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--)
    {
        sum = sum + arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m; i <= h; i++)
    {
        sum = sum + arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    return max(left_sum + right_sum - arr[m], left_sum, right_sum);
}

int maxSubArraySum(int arr[], int l, int h)
{
    if (l > h)
        return INT_MIN;

    if (l == h)
        return arr[l];

    int m = (l + h) / 2;
    return max(maxSubArraySum(arr, l, m - 1), maxSubArraySum(arr, m + 1, h), maxCrossingSum(arr, l, m, h));
}

//=======================================================================================================

void ExecutionTime(int arr1[], int arr2[], int n)
{
    std::cout << "For n = " << n << std::endl;

    std::cout << "Brute      Force: ";
    auto start = std::chrono::steady_clock::now();
    maxSubarraySumBruteForce(arr1, n);
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;

    std::cout << "Divide & Conquer: ";
    start = std::chrono::steady_clock::now();
    maxSubArraySum(arr2, 0, n - 1);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;
}

//=======================================================================================================


void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l >= r)
        return;
    int m = (l + r - 1) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

//=======================================================================================================

void swap(int* x, int* y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void pickRandom(int arr[], int start, int end)
{
    int num = start + rand() % (end - start + 1);
    swap(arr[num], arr[end]);
}

int partition(int arr[], int start, int end)
{
    pickRandom(arr, start, end);
    int pivot = arr[end];
    int i = start;
    for (int k = start; k < end; k++)
    {
        if (arr[k] <= pivot)
        {
            swap(arr[k], arr[i]);
            i++;
        }
    }
    swap(arr[i], arr[end]);
    return i;
}

void RandomQuickSort(int arr[], int start, int end)
{
    if (start < end)
    {
        int p = partition(arr, start, end);
        RandomQuickSort(arr, start, p - 1);
        RandomQuickSort(arr, p + 1, end);
    }
}

//=======================================================================================================

int medianOfThree(int arr[], int low, int high)
{
    int randomIndices[3];
    srand(time(0));
    for (int i = 0; i < 3; i++)
        randomIndices[i] = rand() % (high - low + 1) + low;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2 - i; j++)
            if (arr[randomIndices[j]] > arr[randomIndices[j + 1]])
                swap(randomIndices[j], randomIndices[j + 1]);

    return randomIndices[1];
}

int partition1(int arr[], int start, int end)
{
    int pivot = arr[medianOfThree(arr, start, end)];
    int i = start;
    for (int k = start; k < end; k++)
    {
        if (arr[k] <= pivot)
        {
            swap(arr[k], arr[i]);
            i++;
        }
    }
    swap(arr[i], arr[end]);
    return i;
}

void MedianQuickSort(int arr[], int start, int end)
{
    if (start < end)
    {
        int p = partition1(arr, start, end);
        MedianQuickSort(arr, start, p - 1);
        MedianQuickSort(arr, p + 1, end);
    }
}

//=======================================================================================================

void ExecutionTime_(int arr1[], int arr2[], int arr3[], int n)
{
    std::cout << "For n = " << n << std::endl;

    std::cout << "Merge\tSort        (2 Way): ";
    auto start = std::chrono::steady_clock::now();
    mergeSort(arr1, 0, n - 1);
    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;

    std::cout << "Quick\tSort (Random Pivot): ";
    start = std::chrono::steady_clock::now();
    RandomQuickSort(arr2, 0, n - 1);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;

    std::cout << "Quick\tSort (Median Pivot): ";
    start = std::chrono::steady_clock::now();
    MedianQuickSort(arr3, 0, n - 1);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;
}

int main()
{
    //Problem 1
    srand(time(0));
    const int sizes[] = { 10, 25, 100, 1000, 10000, 100000 };
    for (int i = 0; i < 5; ++i)
    {
        const int s = sizes[i];
        int* A1 = new int[s];
        for (int j = 0; j < s; ++j)
            A1[j] = rand() % 100;
        int* A2 = new int[s];
        ArrCPY(A1, s, A2);
        ExecutionTime(A1, A2, s);
    }

    cout << "\n==============================================================\n\n";

    //Problem 2
    srand(time(0));
    for (int i = 2; i < 6; ++i)
    {
        const int s = sizes[i];
        int* A1 = new int[s];
        for (int j = 0; j < s; ++j)
            A1[j] = rand() % 100;
        int* A2 = new int[s];
        ArrCPY(A1, s, A2);
        int* A3 = new int[s];
        ArrCPY(A1, s, A3);
        ExecutionTime_(A1, A2, A3, s);
    }

    return 0;
}