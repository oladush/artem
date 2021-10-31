#include "Array.h"
#include <iostream>

using namespace std;

Array::Array(int size)
{
    len = size;
    mem = size * 2;
    arr = new int[mem];

    fill(arr, arr+len, 0);
}
Array::Array(int * array, int size): Array(size)
{
    for(int i = 0; i < len; i++)
    {
        arr[i] = array[i];
    }
}

Array::Array(const Array & array): Array(array.arr, array.len)
{}

Array& Array::operator = (const Array & x)
{
    if (*this != x)
    {
        delete [] arr;
        len = x.len;
        mem = x.mem;
        arr = new int[mem];

        for(int i = 0; i < len; i++)
        {
            arr[i] = x.arr[i];
        }
    }

    return *this;
}

Array::~Array()
{
    delete [] arr;
}

Array Array::operator + (const Array & array)
{
    Array newArr(len + array.len);

    memcpy(newArr.arr, arr, len * sizeof(int));
    memcpy(newArr.arr + len, array.arr, array.len * sizeof(int));

    return newArr;
}
Array Array::operator + (int key)
{
    Array newArr(len + 1);

    memcpy(newArr.arr, arr, len * sizeof(int));

    newArr.arr[len] = key;

    return  newArr;
}

Array & Array::operator += (const Array & array)
{
    int * temp;
    if (len + array.len >= mem)
    {
        temp = arr;

        mem = (len + array.len) * 2;

        //delete [] arr;
        arr = new int[mem];

        memcpy(arr, temp, len * sizeof(int));

        //len = mem / 2;

        delete [] temp;
    }

    memcpy(arr + len, array.arr, array.len * sizeof(int));
    len += array.len;

    return *this;
}

Array & Array::operator += (int key)
{
    int * temp;

    if(len + 1 >= mem)
    {
        temp = arr;
        mem = (len+1) * 2;

        arr = new int[mem];
        memcpy(arr, temp, len * sizeof(int));
    }

    arr[len++] = key;

    return *this;
}

Array & Array::operator -= (int key)
{
    return DelPosEq(FindKey(key));
}

Array Array::operator - (int key)
{
    return DelPosNew(FindKey(key));
}

bool Array::operator == (const Array & array)
{
    if (len != array.len)
        return false;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] != array.arr[i])
            return false;
    }
    return true;
}

bool Array::operator != (const Array & array)
{
    return !((*this) == array);
}

int & Array::operator [](int index)
{
    if (index < 0 or index >= len)
    {
        cout << "index out of range\n";
        exit(1);
    }
    return arr[index];
}

int Array::Max()
{
    int max = arr[0], maxi = 0;

    for(int i = 1; i < len; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            maxi = i;
        }
    }
    return maxi;
}

int Array::Min()
{
    int min = arr[0], mini = 0;

    for(int i = 1; i < len; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
            mini = i;
        }
    }
    return mini;
}

int Array::FindKey(int key)
{
    for(int i = 0; i < len; i++)
    {
        if(arr[i] == key)
            return i;
    }
    return -1;
}

void Array::Print()
{
    for(int i = 0; i < len; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}

void  Array::Scan(int n)
{
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    len = n;
}

Array& Array::DelPosEq(int pos)
{
    if (pos < 0 or pos >= len)
    {
        cout << "index out of range\n";
        exit(1);
    }
    for(int i = pos; i < len; i++)
    {
        arr[i] = arr[i+1];
    }
    len--;

    return *this;
}

Array Array::DelPosNew(int pos)
{
    Array newArr = *this;
    newArr.DelPosEq(pos);

    return newArr;
}

ostream & operator << (ostream & ost, Array & array)
{
    array.Print();
    return ost;
}
istream & operator >> (istream & ist, Array & array)
{
    int n = -1;

    while(n <= 0)
    {
        cout << "Enter n - size of array:" << endl;
        cin >> n;
    }

    if (n > array.mem)
    {
        array = Array(n);
    }

    array.Scan(n);
    return ist;
}

int Array::MakeSteps(int *pads, int len) //возвращает кол-во подстановок
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
void Array::ShellSort(int *arr, int len, int *pads, int plen)
{
    for(int k = plen - 1; k >= 0; k--)
    {
        for(int j = 0; j < pads[k]; j++)
            DirectInsertSortWithPadding(arr+j, len-j, pads[k]);
    }
};

void Array::DirectInsertSortWithPadding(int *arr, int len, int pad)
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

void Array::Sorting()
{
    int *pads = new int[len/2];
    int plen = MakeSteps(pads, len);
    ShellSort(arr, len, pads, plen);
    delete [] pads;
}
