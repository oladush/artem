#include <iostream>
#include <time.h>
using namespace std;

int  MakeSteps (int *, int);
void PrintArr  (int *, int);
void fillRandom(int *, int);
void ShellSort(int *, int, int *, int);
void DirectInsertSortWithPadding(int*, int, int);

int MakeSteps(int *pads, int len) //возвращает кол-во подстановок
{
    int p1 = 1, p2 = 1, p3 = 1;
    int s = -1; int i = 0;
    do
    {
        if (++s % 2)
        {
            pads[s] = 8*p1 - 6*p2 + 1;
        }
        else
        {
            pads[s] = 9*p1 - 9*p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2; i++;
    } while(3 * pads[s] < len);

    return i;
};

void ShellSort(int *arr, int len, int *pads, int plen) // массив подстановок инвертирован
{
    for(int k = plen - 1; k >= 0; k--)
    {
        for(int j = 0; j < pads[k]; j++)
            DirectInsertSortWithPadding(arr+j, len-j, pads[k]);

        cout << "With step " << pads[k] << ": ";
        PrintArr(arr, len);
    }
};

void DirectInsertSortWithPadding(int *arr, int len, int pad)
{
    int tmp;
    for (int i = pad, j; i < len;)
    {
        j = i - pad;
        tmp = arr[i];

        while(j >= 0 and arr[j] > tmp)
        {
            arr[j+pad] = arr[j];
            j-=pad;
        }
        arr[j+pad] = tmp;
        i += pad;
    }
}

void PrintArr (int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void fillRandom(int *arr, int len)
{
    srand(time(0));
    for(int i = 0; i < len; i++)
    {
        arr[i] = rand() % 42;
    }
}

void Program(int n)
{
    int *a = new int[n];
    fillRandom(a, n);

    int *pads = new int[n/2];
    int plen = MakeSteps(pads, n);

    cout << "Original array: ";
    PrintArr(a, n);
    cout << "The steps which me use(reverse): ";
    PrintArr(pads, plen);

    ShellSort(a, n, pads, plen);

    delete [] a;
    delete [] pads;
}

int main()
{
    int n = 0, run = 1;
    string answer;

    while(run)
    {
        while (n <= 0)
        {
            cout << "Please, enter n - size of random array" << endl;
            cin >> n;
        }

        Program(n);

        run = -1;
        while(run == -1)
        {
            cout << "Do you want to continue? y/n" << endl;
            cin >> answer;

            if (answer[0] == 'y')
                run = 1;
            if (answer[0] == 'n')
                run = 0;

            n = -1;
        }
    }
    return 0;
}
