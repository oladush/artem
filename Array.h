#pragma  once
#include <iostream>

class  Array
{
private:
    int *arr, len, mem;
    // функции сортировки
    void ShellSort(int *, int, int *, int); //
    int  MakeSteps(int *, int);
    void DirectInsertSortWithPadding(int *, int, int); //
public:
    Array(int length = 1);
    Array(int *, int);
    Array(const Array &);
    Array & operator = (const Array &);

    ~Array();

    void Scan(int);
    void Print();
    int FindKey(int);

    int & operator [](int);

    Array & operator += (int key);
    Array operator + (int key);

    Array & operator += (const Array &);
    Array operator + (const Array &);

    Array & operator -= (int key);
    Array operator - (int key);

    bool operator == (const Array &);
    bool operator != (const Array &);

    int Max();
    int Min();

    void Sorting ();

    Array & DelPosEq (int);
    Array   DelPosNew(int);

    int GetLength() {return len; }

    friend std::ostream & operator << (std::ostream &, Array &);
    friend std::istream & operator >> (std::istream &, Array &);
};
