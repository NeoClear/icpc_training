#include <bits/stdc++.h>
#include <algorithm>

#define MAX 0xffff
#define KIND 29
#define FINITE 10
#define nil NULL
typedef long long i64;
typedef double f64;

#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)

using namespace std;

static i64 prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
static char Err[99] = {'\0'};

struct node
{
    i64 key;
    char value[99];
    node *child[KIND];
    bool isDel;
    node(): key(nil), isDel(true) {
        memset(child, nil, sizeof(child));
    }
};

static node *root = new node();

bool insert(i64 k, char *v)
{
    node *p = root;
    loz(i, FINITE) {
        i64 pos = k % prime[i];
        if (p->child[pos] != nil) {
            if (p->child[pos]->key == k) {
                if (p->child[pos]->isDel == true) {
                    p->child[pos]->isDel = false;
                    strcpy(p->child[pos]->value, v);
                    return true;
                }
                return false;
            }
            p = p->child[pos];
            continue;
        }
        p->child[pos] = new node();
        p->child[pos]->key = k;
        strcpy(p->child[pos]->value, v);
        p->child[pos]->isDel = false;
        return true;
    }
}

char * query(i64 k)
{
    node *p = root;
    loz(i, FINITE) {
        i64 pos = k % prime[i];
        if (p->child[pos] == nil)
            return Err;
        if (p->child[pos]->key == k) {
            if (p->child[pos]->isDel)
                return Err;
            return p->child[pos]->value;
        }
        p = p->child[pos];
    }
    return Err;
}

bool remove(i64 k)
{
    node *p = root;
    loz(i, FINITE) {
        i64 pos = k % prime[i];
        if (p->child[pos] == nil)
            return false;
        if (p->child[pos]->key == k) {
            if (p->child[pos]->isDel)
                return false;
            p->child[pos]->isDel = true;
            return true;
        }
        p = p->child[pos];
    }
    return false;
}

inline void print(node *p)
{
    if (p != root)
        cout<<p->key<<": "<<p->value<<endl;
    loz(i, KIND) {
        if (p->child[i] != nil)
            print(p->child[i]);
    }
}

inline void run()
{
    i64 N;
    i64 k;
    char t[99];
    freopen("in.txt", "r", stdin);
    cin>>N;
    loz(i, N) {
        cin>>k>>t;
        insert(k, t);

    }
    cin>>N;
    i64 ins;
    loz(i, N) {
        cin>>ins;
        switch (ins) {
        case 0:
            cout<<"Insert: ";
            cin>>k>>t;
            if (insert(k, t))
                cout<<"Successful"<<endl;
            else
                cout<<"Error"<<endl;
            break;
        case 1:
            cout<<"Remove: ";
            cin>>k;
            if (remove(k))
                cout<<"Remove "<<k<<" successful"<<endl;
            else
                cout<<k<<" do not exist"<<endl;
            break;
        case 2:
            cout<<"Query: ";
            cin>>k;
            strcpy(t, query(k));
            if (strcmp(t, Err) != 0)
                cout<<k<<": "<<t<<endl;
            else
                cout<<k<<" do not exist"<<endl;
            break;
        }
    }
}

int main()
{
    run();
    return 0;
}
