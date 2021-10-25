#include <iostream>
#include "time.h"

using namespace std;

void genRandomCostMatrix(int n, int** matrix)
{
    for(int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];

        for (int j = 0; j < n; j++)
        {
            if (i == j) matrix[i][j] = 0;
            else matrix[i][j] = 1 + rand() % 23;
        }
    }
}
void printCostMatrix(int n, int** matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "\t";
        }

        cout << endl;
    }
}

int nextCity(int n, bool* passed, int* cost_line)
{
    int min_i = -1, min_cost = 0;

    for(int i = 0; i < n; i++)
    {
        if (passed[i] == 0 and cost_line[i] != 0)
        {
            // нужно инициализировать min_cost
            // пока это не произошло, мы не будем искать минимум
            // min_cost считать инизилизированным когда он отличен от нуля
            if (!min_cost or cost_line[i] < min_cost)
            {
                min_cost = cost_line[i];
                min_i = i;
            }
        }
    }

    return min_i;
}
int evristicSolutionTSP(int n, int k, int** cost_matrix)
{
    bool* passed = new bool[n];
    fill(passed, passed+n, 0);

    int cost = 0, city = k, ncity = 0;

    while (ncity != -1)
    {
        ncity = nextCity(n, passed, cost_matrix[city]);
        cout << city << " -> ";
        if (ncity != -1)
        {
            cost += cost_matrix[city][ncity];
            passed[city] = true;
            city = ncity;
        }
    }

    cost += cost_matrix[city][k];

    cout << k << endl;

    return cost;
}

void program()
{
    int n, k;

    n = -1;
    while (n <= 0)
    {
        cout << "Пожалуста введите число n в интервале [1, oo):" << endl;
        cin >> n;
    }

    int **cost_matrix = new int*[n];

    genRandomCostMatrix(n, cost_matrix);

    printCostMatrix(n, cost_matrix);

    k = -1;
    while (k < 0 or k >= n)
    {
        cout << "Пожалуста введите число k в интервале [0, n):" << endl;
        cin >> k;
    }

    cout << "Evristic: " << evristicSolutionTSP(n, k, cost_matrix) << endl;

    for(int i = 0; i < n; i++)
    {
        delete[] cost_matrix[i];
    }
    delete [] cost_matrix;
};

int main()
{
    srand(time(0));
    system("chcp 65001");// кириллица

    int run = 1;
    
    while(run)
    {
        program();
        cout << "Желаете продолжить? 1/0\n";

        cin >> run;
    }

    return 0;
}
