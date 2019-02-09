#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define DEBUG
#define MAX 100001

using namespace std;

int dictionary_num;
struct node
{
    char terran[15];
    char protoss[15];
}dictionary[MAX];

int query_num;
struct ask
{
    char protoss[15];
}query[MAX];

inline void read_data()
{
    char line[30];

    dictionary_num = 0;
    while (gets(line) != NULL) {
        if (line[0] == '\0')
            break;
        sscanf(line, "%s%s", dictionary[dictionary_num].terran, dictionary[dictionary_num].protoss);
        dictionary_num++;
    }

    query_num = 0;
    while (gets(line) != NULL) {
        sscanf(line, "%s", query[query_num].protoss);
        query_num++;
    }
}

inline void init()
{
#ifdef DEBUG
    freopen("in.txt", "r", stdin);
#endif
    read_data();
}

bool cmp(node m, node n)
{
    return strcmp(m.protoss, n.protoss) < 0;
}

inline void calc()
{
    sort(dictionary, dictionary + dictionary_num, cmp);
}

inline void answer()
{
    int bot, top, mid;
    bool flag;
    for (int i = 0; i < query_num; i++) {
        bot = 0;
        top = dictionary_num - 1;
        flag = false;
        while (bot <= top) {
            mid = (bot + top) / 2;
            if (strcmp(dictionary[mid].protoss, query[i].protoss) < 0)
                bot = mid + 1;
            else if (strcmp(dictionary[mid].protoss, query[i].protoss) > 0)
                top = mid - 1;
            else {
                flag = true;
                printf("%s\n", dictionary[mid].terran);
                break;
            }
        }
        if (!flag)
            printf("eh\n");
    }
}

inline void print_all()
{
    for (int i = 0; i < dictionary_num; i++)
        printf("%s %s\n", dictionary[i].terran, dictionary[i].protoss);
    printf("\n");
    for (int i = 0; i < query_num; i++)
        printf("%s\n", query[i].protoss);
}

int main()
{
    init();
    calc();
    answer();
//    print_all();
    return 0;
}
