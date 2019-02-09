#include <bits/stdc++.h>
#include <algorithm>

#define MAX 0xffff
typedef long long i64;
#define KIND 26
#define nil NULL
#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)

using namespace std;

struct node
{
    node *fail;
    node *child[KIND];
    bool isEnd;
    node(): fail(nil), isEnd(false) {
        memset(child, nil, sizeof(child));
    }
};

static i64 N;
static node *root = new node();
static node *cons[MAX];
static i64 head = 0, tail = 0;

inline void insert(char *s)
{
    if (s == nil || strlen(s) == 0)
        return;
    node *p = root;
    i64 pos;
    loz(i, strlen(s)) {
        pos = s[i] - 'a';
        if (p->child[pos] == nil) {
            p->child[pos] = new node();
        }
        p = p->child[pos];
    }
    p->isEnd = true;
}

inline void verify()
{
    cons[head++] = root;
    while (head > tail) {
        node *p = cons[tail++];
        loz(i, KIND) {
            if (p->child[i] == nil)
                continue;
            cons[head++] = p->child[i];
            if (p->fail == nil)
                p->child[i]->fail = root;
            else {
                node *tmp = p->fail;
                while(tmp != nil) {
                    if(tmp->child[i] != nil)
                    {
                        p->child[i]->fail = tmp->child[i];
                        break;
                    }
                    tmp = tmp->fail;
                }
                if(tmp == nil)
                    p->child[i]->fail = root;
//                while (tmp->child[i] == nil) {
//                    if (tmp->fail == root) {
//                        p->child[i]->fail = root;
//                        break;
//                    }
//                    tmp = tmp->fail;
//                }
//                if (!p->child[i]->fail)
//                    p->child[i]->fail = tmp->child[i];
            }
        }
    }
}

i64 query(char *s)
{
    i64 i = 0;
    node *p = root;
    i64 pos;
    while (i < static_cast<i64>(strlen(s)) && !p->isEnd) {
        pos = s[i] - 'a';
        if (p->child[pos] != nil) {
            i++;
            p = p->child[pos];
        }
        if (p->fail == nil)
            i++;
        else
            p = p->fail;
    }
    if (p->isEnd)
        return i;
    return -1;
}

int main()
{
    freopen("in.txt", "r", stdin);
    cin >>N;
    char tmp[MAX];
    loz(i, N) {
        cin >>tmp;
        insert(tmp);
    }
    char src[MAX];
    cin >>src;
    verify();
    cout<< query(src)<< endl;
    return 0;
}
