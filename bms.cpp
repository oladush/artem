#include <iostream>
#include "stdio.h"

using namespace std;
#define TAB_SIZE 256

void fillTab(int *tab, string &key)
{
    fill(tab, tab+TAB_SIZE, key.length());
    for(int i = 0; i < key.length() - 1; i++)
    {
        tab[key[i]] = key.length() - i - 1;
    }

}

int calcTab(int*tab, string &key, string &text, int j)
{
    int m = key.length();

    for(int i = m - 1; i >= 0 and j >= 0; i--, j--)
    {
        if (key[i] != text[j])
        {
            return tab[text[j]];
        }
    }

    return 0;
}

int bmSearch(int *tab, string key, string text)
{
    cout << "pattern: " << key << "  text: " << text << endl;

    fillTab(tab, key);
    int m = key.length(), nTab;

    for(int j = m - 1; j < text.length();)
    {
        nTab = calcTab(tab, key, text, j);
        cout << "TAB = " << nTab << endl;
        if (nTab == 0) return j - m + 1;
        else j += nTab;
    }

    return -1;
}

int main() {
    system("chcp 65001");// кириллица

    int dictionary[TAB_SIZE]; // tab-array

    string run = "y";
    while (run == "y")
    {
        string key, text;

        cout << "Введите строку в которой будет осуществляться поиск: " << endl;

        getline(cin, text);

        cout << "Введите строку по которой будет осуществляться поиск: " << endl;
        getline(cin, key);

        cout << bmSearch(dictionary, key, text) << endl;

        cout << "Желаете продолжить? y/n\n";
        cin >> run;

        while(cin.get() != '\n');
    }

    return 0;
}
