#include <iostream>
#include <cstdlib> // для random
#include <ctime>

using namespace std;

bool permutation    (int, int*);
void invertTail     (int, int, int*);
void initPermutation(int, int, int*);
int  calcCosts      (int, int*, int**);

void printCostMatrix (int, int**);
void printPermutation(int, int *);

void genRandomCostMatrix(int , int**);

int accurateSolutionTSP(int n, int k, int** cost_matrix) // traveling salesman problem
{
    int  now_cost,  min_cost;
    int *now_perm, *min_perm;

    now_perm = new int[n];
    min_perm = new int[n];

    initPermutation(n, k, now_perm);
    memcpy(min_perm, now_perm, n*sizeof(int));

    now_cost = calcCosts(n, now_perm, cost_matrix);
    min_cost = now_cost;


    int i = 1;

    cout << i++ << ". ";
    printPermutation(n, now_perm);
    cout << "Cost: " << now_cost << endl;

    while (permutation(n, now_perm))
    {
        now_cost = calcCosts(n, now_perm, cost_matrix);

        cout << i++ << ". ";
        printPermutation(n, now_perm);
        cout << "Cost: " << now_cost << endl;

        if (now_cost < min_cost)
        {
            min_cost = now_cost;
            memcpy(min_perm, now_perm, n*sizeof(int));
        }
    }

    cout << "------------------------" << endl;
    cout << "the best permutation is:" << endl;
    printPermutation(n, min_perm);
    cout << endl << "the price is: " << min_cost << endl;

    delete [] now_perm; delete [] min_perm;

    return min_cost;
}

int main()
{
    srand(time(0));

    int n = 6;
    int **cost_matrix = new int*[n];

    genRandomCostMatrix(n, cost_matrix);

    printCostMatrix(n, cost_matrix);

    accurateSolutionTSP(n, 2, cost_matrix);

    for (int i = 0; i < n; i++)
    {
        delete [] cost_matrix[i];
    }
    delete [] cost_matrix;

    return 0;
}
bool permutation(int n, int* old)
{
    int temp;

    for (int i = n - 2; i >= 0; i--)
        if (old[i] < old[i+1] and i != 0)
            for (int j = n - 1; j >= 0; j--)
                if (old[i] < old[j])
                {
                    temp = old[i];
                    old[i] = old[j];
                    old[j] = temp;

                    invertTail(n, i, old);

                    return true;
                }
    return false;
}

void invertTail(int n, int i, int* perm)
{
    int temp;
    int* tail = perm + i + 1;
    n -= i + 1;

    for (int j = 0; j < n / 2; j++)
    {
        temp = tail[j];
        tail[j] = tail[n - j - 1];
        tail[n - j - 1] = temp;
    }
}

void initPermutation(int n, int k, int* perm)
{
    perm[0] = k;
    for (int i = 1; i <= k; i++)
    {
        perm[i] = i - 1;
    }
    for(int i = k+1; i < n; i++)
        perm[i] = i;
}

int calcCosts(int n, int *perm, int** matrix)
{
    int cost = matrix[perm[n-1]][perm[0]];
    for (int i = 1; i < n; i++)
        cost += matrix[perm[i-1]][perm[i]];
    return cost;
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

void printPermutation(int n, int * perm)
{
    for(int i = 0; i < n; i++)
    {
        cout << perm[i] << " -> ";
    }

    cout << perm[0] << " ";

}

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
