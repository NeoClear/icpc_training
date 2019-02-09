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
    char value;
    node(): fail(nil), isEnd(false), value(nil) {
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
        p->value = s[i];
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

}

inline void print(node *n)
{
    cout<< n->value;
    if (n->isEnd)
        cout<< endl;
    loz(i, KIND) {
        if (n->child[i] != nil)
            print(n->child[i]);
    }
}

inline void print_fail(node *n)
{
    if (n->fail != nil)
        cout<< n->value<< " -> "<< n->fail->value<< endl;
    loz(i, KIND) {
        if (n->child[i] != nil)
            print_fail(n->child[i]);
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    cin >>N;
    char tmp[MAX];
    root->value = '*';
    loz(i, N) {
        cin >>tmp;
        insert(tmp);
//        cout<< tmp<< endl;
    }
    print(root);
    char src[MAX];
//    cin >>src;
    verify();
    print_fail(root);
    cout<< query(src)<< endl;
    return 0;
}
