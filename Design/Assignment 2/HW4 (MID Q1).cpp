#include <iostream>
using namespace std;

void AlphaPrint(int A[], int n)
{
    cout << "Input: A[] = { ";
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << "}\n";
}

void Print(int A[], int n)
{
    cout << "Output: Subarray[] = { ";
    for (int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << "}\n";
}

int* mkSubArray(int A[], int start, int n, int k)
{
    int* nearest = new int[k];
    int ni = 0;
    for (int i = start; i <= n; i++)
    {
        nearest[ni] = A[i];
        ni++;
    }
    //Print(nearest, k);
    return nearest;
}

void binarySearch(int arr[], int l, int r, int v, int k, int n)
{
    int* nearest = new int[k];

    int start;
    int alpham = l + (r - l) / 2;
    int lDiff;
    int rDiff;
    while (l <= r) //l (^) OR r (v)
    {;
        int m = l + (r - l) / 2;
        //cout << m << " ";
        if (m != 0)
            lDiff = arr[m] - arr[m - 1];
        if (m != n - 1)
        rDiff = arr[m + 1] - arr[m];

        // Check if x is present at mid
        if (arr[m] == v)
        {
            //cout << lDiff << " < " << rDiff << "?\n";
            start = m;
            if (lDiff < rDiff)
            {
                start--;
                //cout << "+starting index is " << start << endl;
                //cout << "ending index is " << start + k - 1 << endl;
                nearest = mkSubArray(arr, start, start + k - 1 , k);
            }
            else
            {
                //cout << "-starting index is " << start << endl;
                //cout << "ending index is " << start + k - 1 << endl;
                nearest = mkSubArray(arr, start, start + k - 1, k);
            }
            Print(nearest, k);
;           return;
        }

        // If x greater, ignore left half
        if (arr[m] < v)
        {
            l = m + 1;
        }

        // If x is smaller, ignore right half
        else
        {
            start = 0;
            r = m - 1;
        }
    }

    //cout << "\nLeft Diff = " << lDiff << endl;
    //cout << "Right Diff = " << rDiff << endl;

    if (l < alpham)
    {
        //cout << "!";
        start = 0;
        if (rDiff < lDiff)
            start++;
        nearest = mkSubArray(arr, start, start + k - 1, k);
    }
    else
    {
        //cout << "&";
        start = alpham;
        if (rDiff > lDiff)
            start--;
        //cout << "@starting index is " << start << endl;
        //cout << "ending index is " << start + k << endl;
        nearest = mkSubArray(arr, start, start + k, k);
    }
    Print(nearest, k);

    // If we reach here, then element was not present
    return;
}

void Test()
{
    int A1[] = { 2, 3, 5, 6, 9, 15, 23 };
    int A2[] = { 6, 8, 9, 12, 23 };
    int A3[] = { 1, 8, 9, 12, 23 };
    int A4[] = { 1, 2, 3, 6, 7, 15, 23 };
    int A5[] = { 3, 5, 7,14,20, 21, 25 };

    int* AlphaA[] = { A1,A2,A3,A4,A5 };
    int v[] = { 6,4,7,4,9 };
    int k[] = { 4,3,2,4,3 };

    int sizes[] = { size(A1),size(A2), size(A3), size(A4),size(A5) };

    for (int i = 0; i < size(AlphaA); i++)
    {
        AlphaPrint(AlphaA[i], sizes[i]);
        cout << "v = " << v[i] << "\nk = " << k[i] << endl;
        binarySearch(AlphaA[i], 0, sizes[i] - 1, v[i], k[i], sizes[i]);
        cout << endl << endl;
    }
}

int main()
{
    Test();
    int A[] = { 2, 3, 5, 6, 9, 15, 23 };
    //int A[] = { 1, 2, 3, 6, 7, 15, 23 };
    int v = 6; 
    int k = 4;

    //int A[] = { 6, 8, 9, 12, 23 };
    //int v = 4;
    //int k = 3;

    //int A[] = { 1, 8, 9, 12, 23 };
    //int v = 7;
    //int k = 2;

    //int A[] = { 1, 2, 3, 6, 7, 15, 23 };
    //int v = 4; 
    //int k = 4;

    //cout << binarySearch(A, 0, size(A) - 1, v, k, size(A));
}
