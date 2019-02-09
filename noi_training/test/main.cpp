#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX 99999
int list[MAX];
int num;
int request;

inline void read_data()
{
    cin>>num;
    for (int i = 0; i < num; i++)
        cin>>list[i];
}

inline void init()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    num = 0;
    for (int i = 0; i < MAX; i++)
        list[i] = 0;
    read_data();
}

int search(int bot, int top)
{
    int mid = (bot + top) / 2;
    if (list[mid] > request)
        return search(bot, mid - 1);
    else if (list[mid] < request)
        return search(mid + 1, top);
    else
        return mid;
}

int main()
{
    init();
    request = 12;
    cout<< search(0, num - 1) + 1<< endl;
    return 0;
}
