#include <iostream>
using namespace std;

void Print(int A[], int n)
{
	cout << "{ ";
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << "}\n";
}

int Find(int A[], int n, int v)
{
	for (int i = 0; i < n; i++)
	{
		if (A[i] == v)
			return i;
	}
	return -1;
}

void Theta1(int A[], int n)
{
	int MSS = INT_MAX;
	int maxMSS = INT_MIN;
	int Start = INT_MAX;
	int minStart = INT_MAX;

	for (int i = 0; i < n + 1; i++)
	{
		if (i == 0)
		{
			MSS = A[i];
			Start = i;
		}
		else
		{
			if ((MSS + A[i]) > (A[i]))
			{
				if (MSS > maxMSS)
					maxMSS = MSS;

				MSS = MSS + A[i];
			}
			else
			{
				MSS = A[i];
				Start = i;
				if (Start < minStart)
					minStart = Start;
			}
		}
	}
	if (minStart == INT_MAX)
		minStart = 0;
	Start = minStart;
	MSS = maxMSS;
	if (Find(A, n, MSS) != -1)
		Start = Find(A, n, MSS);

	cout << "MSS = " << MSS << endl;
	cout << "Start = " << Start << endl;
}

void ThetaN(int A[], int n)
{
	int* MSS = new int[n];
	int* Start = new int[n];

	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			MSS[i] = A[i];
			Start[i] = i;
		}
		else
		{
			if ((MSS[i - 1] + A[i]) > (A[i]))
			{
				MSS[i] = MSS[i - 1] + A[i];
				Start[i] = Start[i - 1];
			}
			else
			{
				MSS[i] = A[i];
				Start[i] = i;
			}
		}
	}
	cout << "MSS[] = ";
	Print(MSS, n);
	cout << "start[] = ";
	Print(Start, n);
}

int main()
{
	int A[] = {1,12,-7,3,-2,14,-10,2};
	//int A[] = { 1,-12,-7,3,-2,-14,-10,-2 };
	//int A[] = { 1,-12,7,3,2,-14,-10,-2 };
	//int A[] = { 5,-9,8,5,8,-8,-7,9,-7,-4,5 };
	cout << "A[] = ";
	Print(A, size(A));
	cout << "\nO(N) Space\n";
	ThetaN(A, size(A));
	cout << "\nO(1) Space\n";
	Theta1(A, size(A));
}
