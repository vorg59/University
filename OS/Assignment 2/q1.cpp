#include <iostream>
#include <chrono>
using namespace std;


struct ThreadParam
{
    int* A;
    int n; 
};

double average;
void* AVG(void *tparam)
{
    ThreadParam *param= (ThreadParam*) tparam;
    double *sum=new double;
    *sum=0;
    double *avg_ptr=new double;
    for (int i = 0; i < param->n; i++)
        *sum+=param->A[i];
    *avg_ptr=*sum/double(param->n);
    average=*avg_ptr;
    return (void *)0;
}

int maximum;
void* MAX(void *tparam)
{
    ThreadParam *param= (ThreadParam*) tparam;
    int *max_ptr = new int;
    *max_ptr=INT16_MIN;
    for (int i = 0; i < param->n; i++)
    {
        if(param->A[i]>*max_ptr)
            *max_ptr=param->A[i];
    }
    maximum=*max_ptr;
    return (void *)0;    
}

int minimum;
void* MIN(void *tparam)
{
    ThreadParam *param= (ThreadParam*) tparam;
    int *min_ptr = new int;
    *min_ptr=INT16_MAX;
    for (int i = 0; i < param->n; i++)
    {
        if(param->A[i]<*min_ptr)
            *min_ptr=param->A[i];
    }
    minimum=*min_ptr;
    return (void *)0;    
}

void* Print(void *tparam)
{
    ThreadParam *param= (ThreadParam*) tparam;
    for (int i = 0; i < param->n; i++)
    {
        cout<<param->A[i]<<" ";
    }
    cout<<endl;
    return (void *)0;
}

int main(int args, char* argv[])
{
    auto start = chrono::steady_clock::now();



    int n = args - 1;
    int*A=new int[n];
    int j=0;
    for (int i = 1; i < args; i++)
    {
        A[j]=stoi(argv[i]);
        j++;
    }

    ThreadParam param;
    param.A=A;
    param.n=n;
    
    //ready Print
    pthread_t id_print;
    pthread_create(&id_print, NULL, &Print, &param);
    //ready AVG
    pthread_t id_AVG;
    pthread_create(&id_AVG, NULL, &AVG, &param);
    //ready MAX
    pthread_t id_MAX;
    pthread_create(&id_MAX, NULL, &MAX, &param);
    //ready MIN
    pthread_t id_MIN;
    pthread_create(&id_MIN, NULL, &MIN, &param);

    //start
    //start Print
    pthread_join(id_print, (void**) NULL);
    //start AVG
    pthread_join(id_AVG, (void**) NULL);
    //start MAX
    pthread_join(id_MAX, (void**) NULL);
    //start MIN
    pthread_join(id_MIN, (void**) NULL);

    cout<<"Average = "<<average<<endl;
    cout<<"Maximum = "<<maximum<<endl;
    cout<<"Minimum = "<<minimum<<endl;



    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in microseconds using Threads: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
}

// #include <iostream>
// #include <chrono>
// using namespace std;

// double AVG(int A[], int n)
// {
//     double sum = 0;
//     for (int i = 0; i < n; i++)
//         sum+=A[i];
//     return sum/double(n);    
// }

// int MAX(int A[], int n)
// {
//     int max = INT16_MIN;
//     for (int i = 0; i < n; i++)
//     {
//         if(A[i]>max)
//             max=A[i];
//     }
//     return max;    
// }

// int MIN(int A[], int n)
// {
//     int min = INT16_MAX;
//     for (int i = 0; i < n; i++)
//     {
//         if(A[i]<min)
//             min=A[i];
//     }
//     return min;    
// }

// void Print(int A[], int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         cout<<A[i]<<" ";
//     }
//     cout<<endl;
// }

// int main(int args, char* argv[])
// {
//     auto start = chrono::steady_clock::now();



//     int n = args - 1;
//     int*A=new int[n];
//     int j=0;
//     for (int i = 1; i < args; i++)
//     {
//         A[j]=stoi(argv[i]);
//         j++;
//     }
//     Print(A, n);
//     cout<<"Average = "<<AVG(A, n)<<endl;
//     cout<<"Maximum = "<<MAX(A, n)<<endl;
//     cout<<"Minimum = "<<MIN(A, n)<<endl;



//     auto end = chrono::steady_clock::now();
//     cout << "Elapsed time in microseconds not using Threads: "
//         << chrono::duration_cast<chrono::microseconds>(end - start).count()
//         << " µs" << endl;
// }
