#include <iostream>
using namespace std;

struct ThreadParam
{
    long int* A;
    long int n; 
};

void* Fib(void *tparam)
{
    ThreadParam *param = (ThreadParam*) tparam;
    param->A = new long int[param->n];
    param->A[0] = 0;
    param->A[1] = 1;
    for (long int i = 2; i < param->n; i++)
        param->A[i] = param->A[i - 1] + param->A[i - 2];
    return (void**)param->A;
}

void* Print(void *tparam)
{
    ThreadParam *param = (ThreadParam*) tparam;
    for (long int i = 0; i < param->n; i++)
        cout << param->A[i] << " ";
    cout << endl;
    return (void**)0;
}

int main(int args, char* argv[])
{
    ThreadParam param;
    param.n = stoi(argv[1]);
    //Ready Fib
    pthread_t id_fib;
    pthread_create(&id_fib, NULL, &Fib, &param);
    //start Fib
    long int* Fib_Arr;
    pthread_join(id_fib, (void**)&Fib_Arr);
    //Ready Prlong int
    param.A = Fib_Arr;
    pthread_t id_print;
    pthread_create(&id_print, NULL, &Print, &param);
    pthread_join(id_print, (void**)NULL);
}
