#include <iostream>
#include <string>
using std::string;
const int BUFF = 256;

int getMax(string arr[], int n) 
{
    int max = arr[0].size();
    for (int i = 1; i < n; i++) 
    {
        if (arr[i].size() > max)
            max = arr[i].size();
    }
    return max;
}

void countSort(string a[], int size, int k) 
{
    string* b = new string[size];
    int* c = new int[BUFF];

    for (int i = 0; i < BUFF; i++)
        c[i] = 0;

    for (int j = 0; j < size; j++)
        c[k < a[j].size() ? (int)(unsigned char)a[j][k] + 1 : 0]++;

    for (int f = 1; f < BUFF; f++)
        c[f] += c[f - 1];

    for (int r = size - 1; r >= 0; r--) 
    {
        b[c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0] - 1] = a[r];
        c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0]--;
    }

    for (int l = 0; l < size; l++)
        a[l] = b[l];
}

void radixSort(string b[], int r) 
{
    int max = getMax(b, r);
    for (int digit = max; digit > 0; digit--)
        countSort(b, r, digit - 1);
}

int main() {
    string data[] = { "John Doe", "Alice Smith", "Bob Johnson", "Charlie Brown", "David Lee" };

    std::cout << "Before sorting:\n";
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        std::cout << "    " << data[i] << "\n";

    radixSort(data, static_cast<int>(sizeof(data) / sizeof(data[0])));

    std::cout << "After sorting:\n";
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        std::cout << "    " << data[i] << "\n";

    return 0;
}
