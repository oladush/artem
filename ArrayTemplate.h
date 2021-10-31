#pragma  once
#include <iostream>

using namespace std;

template<class temp>
class  ArrayTemplate
{
private:
    temp *arr;
    int len, mem;
    // функции для сортировки
    void ShellSort(temp *, int, int *, int); //
    int  MakeSteps(int *, int);
    void DirectInsertSortWithPadding(temp *, int, int); //
public:
    ArrayTemplate(int size = 1);
    ArrayTemplate(temp *, int);
    ArrayTemplate(const ArrayTemplate &);
    ArrayTemplate & operator = (const ArrayTemplate &);

    ~ArrayTemplate();

    void Scan(int);
    void Print();
    int FindKey(temp);

    temp & operator [](int);

    ArrayTemplate & operator += (temp key);
    ArrayTemplate operator + (temp key);

    ArrayTemplate & operator += (const ArrayTemplate &);
    ArrayTemplate operator + (const ArrayTemplate &);

    ArrayTemplate & operator -= (temp key);
    ArrayTemplate operator - (temp key);

    bool operator == (const ArrayTemplate &);
    bool operator != (const ArrayTemplate &);

    int Max();
    int Min();

    void Sorting ();

    ArrayTemplate & DelPosEq (int);
    ArrayTemplate   DelPosNew(int);

    int GetLength() {return len; }
    
    template<class t2>
    friend std::ostream & operator << (std::ostream &, ArrayTemplate<t2> &);
    template<class t2>
    friend std::istream & operator >> (std::istream &, ArrayTemplate<t2> &);
};
template<class temp>
ArrayTemplate<temp>::ArrayTemplate(int size)
{
    len = size;
    mem = size * 2;
    arr = new temp[mem];

    fill(arr, arr+len, 0);
}
template<class temp>
ArrayTemplate<temp>::ArrayTemplate(temp * array, int size): ArrayTemplate(size)
{
    for(int i = 0; i < len; i++)
    {
        arr[i] = array[i];
    }
}

template<class temp>
ArrayTemplate<temp>::ArrayTemplate(const ArrayTemplate & array): ArrayTemplate(array.arr, array.len)
{}

template<class temp>
ArrayTemplate<temp> & ArrayTemplate<temp>::operator=(const ArrayTemplate<temp> & x)
{
    if (*this != x)
    {
        delete [] arr;
        len = x.len;
        mem = x.mem;
        arr = new temp[mem];

        for(int i = 0; i < len; i++)
        {
            arr[i] = x.arr[i];
        }
    }

    return *this;
}

template<class temp>
ArrayTemplate<temp>::~ArrayTemplate<temp>()
{
    delete [] arr;
}

template<class temp>
void ArrayTemplate<temp>::Scan(int n)
{
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    len = n;
}
template<class temp>
void ArrayTemplate<temp>::Print()
{
    for(int i = 0; i < len; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
}
template<class temp>
int ArrayTemplate<temp>::FindKey(temp key)
{
    for(int i = 0; i < len; i++)
    {
        if(arr[i] == key)
            return i;
    }
    return -1;
}
template<class temp>
temp & ArrayTemplate<temp>::operator[](int index)
{
    if (index < 0 or index >= len)
    {
        cout << "index out of range\n";
        exit(1);
    }
    return arr[index];
}

template<class temp>
ArrayTemplate<temp> & ArrayTemplate<temp>::operator += (temp key)
{
    temp * tmp;

    if(len + 1 >= mem)
    {
        tmp = arr;
        mem = (len+1) * 2;

        arr = new temp[mem];
        memcpy(arr, tmp, len * sizeof(temp));
    }

    arr[len++] = key;

    return *this;
}
template<class temp>
ArrayTemplate<temp> ArrayTemplate<temp>::operator+(temp key)
{
    ArrayTemplate<temp> newArr(len + 1);

    memcpy(newArr.arr, arr, len * sizeof(temp));

    newArr.arr[len] = key;

    return  newArr;
}
template<class temp>
ArrayTemplate<temp> & ArrayTemplate<temp>::operator+=(const ArrayTemplate<temp> & array)
{
    temp * tmp;
    if (len + array.len >= mem)
    {
        tmp = arr;
        mem = (len + array.len) * 2;

        arr = new temp[mem];
        memcpy(arr, tmp, len * sizeof(temp));

        delete [] tmp;
    }

    memcpy(arr + len, array.arr, array.len * sizeof(temp));
    len += array.len;

    return *this;
}
template<class temp>
ArrayTemplate<temp> ArrayTemplate<temp>::operator+(const ArrayTemplate & array)
{
    ArrayTemplate<temp> newArr(len + array.len);

    memcpy(newArr.arr, arr, len * sizeof(temp));
    memcpy(newArr.arr + len, array.arr, array.len * sizeof(temp));

    return newArr;
}
template<class temp>
ArrayTemplate<temp> & ArrayTemplate<temp>::DelPosEq(int pos)
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
template<class temp>
ArrayTemplate<temp>ArrayTemplate<temp>::DelPosNew(int pos)
{
    ArrayTemplate<temp> newArr = *this;
    newArr.DelPosEq(pos);

    return newArr;
}

template<class temp>
ArrayTemplate<temp> & ArrayTemplate<temp>::operator-=(temp key)
{
    return DelPosEq(FindKey(key));
}

template<class temp>
ArrayTemplate<temp>ArrayTemplate<temp>::operator-(temp key)
{
    return DelPosNew(FindKey(key));
}

template<class temp>
bool ArrayTemplate<temp>::operator==(const ArrayTemplate<temp> & array)
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
template<class temp>
bool ArrayTemplate<temp>::operator!=(const ArrayTemplate<temp> & array)
{
    return !((*this) == array);
}
template<class temp>
int ArrayTemplate<temp>::Max()
{
    temp max = arr[0];
    int maxi = 0;

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
template<class temp>
int ArrayTemplate<temp>::Min()
{
    temp min = arr[0];
    int mini = 0;

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
template<class temp>
ostream & operator << (ostream & ost, ArrayTemplate<temp> & array)
{
    array.Print();
    return ost;
}
template<class temp>
istream & operator >> (istream & ist, ArrayTemplate<temp> & array)
{
    int n = -1;

    while(n <= 0)
    {
        cout << "Enter n - size of array:" << endl;
        cin >> n;
    }

    if (n > array.mem)
    {
        array = ArrayTemplate<temp>(n);
    }

    array.Scan(n);
    return ist;
}

/////
template<class temp>
int ArrayTemplate<temp>::MakeSteps(int * pads, int len)
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
}
template<class temp>
void ArrayTemplate<temp>::DirectInsertSortWithPadding(temp *arr, int len, int pad)
{
    temp tmp;
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
template<class temp>
void ArrayTemplate<temp>::ShellSort(temp * arr, int len, int * pads, int plen)
{
    for(int k = plen - 1; k >= 0; k--)
    {
        for(int j = 0; j < pads[k]; j++)
            DirectInsertSortWithPadding(arr+j, len-j, pads[k]);
    }
}

template<class temp>
void ArrayTemplate<temp>::Sorting()
{
    int *pads = new int[len/2];
    int plen = MakeSteps(pads, len);
    ShellSort(arr, len, pads, plen);
    delete [] pads;
}
