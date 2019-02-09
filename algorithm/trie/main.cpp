#include <bits/stdc++.h>
#include <algorithm>

#define MAX 0xffff
#define BYTE 26
typedef long long i64;
#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)

using namespace std;

static i64 N;

struct trie
{
    i64 num;
    trie *son[BYTE];
    char value;
    bool isEnd;
    trie(): num(0), value(0), isEnd(false) {
        loz(i, BYTE) son[i] = nullptr;
    }
};

static trie *root = new trie();

inline void insert(char *pattern)
{
    if (!strlen(pattern) || pattern == nullptr)
        return;
    struct trie *p = root;
    loz(i, strlen(pattern)) {
        p->num++;
        int pos = pattern[i] - 'a';
        if (p->son[pos] == nullptr) {
            p->son[pos] = new trie();
            p->son[pos]->value = pattern[i];
        }
            p = p->son[pos];
    }
    p->isEnd = true;
}

bool match(char *pattern)
{
    if (strlen(pattern) == 0 || pattern == nullptr)
        return false;
    struct trie *p = root;
    loz(i, strlen(pattern)) {
        i64 pos = pattern[i] - 'a';
        if (p->son[pos] == nullptr)
            return false;
        p = p->son[pos];
    }
    return p->isEnd;
}
int main()
{
    freopen("in.txt", "r", stdin);
    char p[MAX];
    cin >>N;
    loz(i, N) {
        cin >>p;
        insert(p);
    }
    cin >>N;
    loz(i, N) {
        cin >>p;
        if (match(p))
            cout<< p<< " inside"<< endl;
        else
            cout<< p<< " not inside"<< endl;
    }
    return 0;
}
