#include <iostream>
using namespace std;

void Print(int A[], int n)
{
    cout << "[] = { ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << "}\n";
}

int min(int A[], int n)
{
    int mini = INT_MAX;
    int mini_index = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (mini > A[i])
        {
            mini = A[i];
            mini_index = i;
        }
    }
    return mini_index;
}

void N(int A[], int n, int v, int k)
{
    int* diff = new int[n];

    for (int i = 0; i < n; i++)
        diff[i] = abs(v - A[i]);
    
    int pivot = min(diff, n);
    int i = pivot - 1;
    int j = pivot + 1;
    int currSize = 0;
    int* subA = new int[k];
    int index = 0;

    int* RightA = new int[n];
    int RightA_index = 0;
    int* LeftA = new int[n];
    int LeftA_index = 0;
    while (currSize != k - 1)
    {
        if (diff[i] < diff[j] && i!=-1)
        {
            LeftA[LeftA_index] = A[i];
            LeftA_index++;
            i--;
        }
        else
        {
            RightA[RightA_index] = A[j];
            RightA_index++;
            j++;
        }
        currSize++;
    }
    cout << endl;
    LeftA_index--;
    index = 0;
    while (LeftA_index != -1)
    {
        subA[index] = LeftA[LeftA_index];
        LeftA_index--;
        index++;
    }
    subA[index] = A[pivot];
    index++;
    for (int i = 0; i < RightA_index; i++)
    {
        subA[index] = RightA[i];
        index++;
    }

    cout << "Input: A";
    Print(A, n);
    cout << "v = " << v << "\nk = " << k << endl;
    //cout << "Diff";
    //Print(diff, n);
    cout << "Output: SubArray";
    Print(subA, k);
}

void TestN()
{
    int A1[] = { 2, 3, 5, 6, 9, 15, 23 };
    int A2[] = { 6, 8, 9, 12, 23 };
    int A3[] = { 1, 8, 9, 12, 23 };
    int A4[] = { 1, 2, 3, 6, 7, 15, 23 };
    int A5[] = { 3, 5, 7,14,20, 21, 25 };
    int A6[] = { -6, -1, 0,3,8, 9, 15, 21 };
    int A7[] = { -1, 5, 15,16,30, 35 };

    int* AlphaA[] = { A1,A2,A3,A4,A5,A6,A7 };
    int v[] = { 6,4,7,4,13,5,24 };
    int k[] = { 4,3,2,4,3,4,3 };

    int sizes[] = { size(A1),size(A2), size(A3), size(A4),size(A5),size(A6),size(A7) };

    for (int i = 0; i < size(AlphaA); i++)
    {
        cout << "===========================================================================\n";
        N(AlphaA[i], sizes[i], v[i], k[i]);
        cout << endl;
    }
}

int main()
{
    TestN();
}