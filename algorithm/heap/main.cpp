﻿#include <bits/stdc++.h>
#include <algorithm>

#define inf 0xffff
typedef long long i64;
typedef double f64;
#define nil NULL
#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)
#define loo(i, n) for (i64 i = 1; i <= static_cast<i64>(n); i++)

using namespace std;

static i64 N;
static i64 heap[inf];

namespace io {
    i64 read_i64()
    {
        i64 ans = 0, f = 1;
        int ch = getchar();
        while (!isdigit(ch)) {
            if (ch == '-') {
                f = -1;
            }
            ch = getchar();
        }
        while (isdigit(ch)) {
            ans = ans * 10 + ch - '0';
            ch = getchar();
        }
        return ans * f;
    }

    f64 read_f64()
    {
        f64 ans = 0.0;
        f64 divide = 1.0;
        bool flag = false;
        f64 f = 1.0;
        int ch = getchar();
        while (!isdigit(ch)) {
            if (ch == '-')
                f = -1.0;
            ch = getchar();
        }
        while (isdigit(ch) || ch == '.') {
            if (ch == '.') {
                ch = getchar();
                flag = true;
            }
            ans = ans * 10.0 + static_cast<f64>((ch - '0'));
            if (flag)
                divide *= 10.0;
            ch = getchar();
        }
        return ans * f / divide;
    }
}


inline void init()
{
    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    N = io::read_i64();
    loo(i, N) {
        heap[i] = io::read_i64();
    }

}

namespace core {
    void shiftdown(i64 i)
    {
        i64 t;
        bool flag = true;
        while (i * 2 <= N && flag) {
            if (heap[i] > heap[i * 2])
                t = i * 2;
            else
                t = i;
            if (i * 2 + 1 <= N)
                if (heap[t] > heap[i * 2 + 1])
                    t = i * 2 + 1;
            if (t != i) {
                swap(heap[i], heap[t]);
                i = t;
            } else
                flag = false;
        }
    }
    void shiftup(i64 i)
    {
        bool flag = true;
        while (i >= 1 && flag) {
            if (heap[i] < heap[i / 2]) {
                swap(heap[i], heap[i / 2]);
                i /= 2;
            } else
                flag = false;
        }
    }
    void build()
    {
        for (i64 i = N / 2; i >= 1; i--) {
            shiftdown(i);
        }
    }
    i64 delete_min()
    {
        i64 m = heap[1];
        heap[1] = heap[N];
        N--;
        shiftdown(1);
        return m;
    }
}

namespace debug {
    void print_heap() {
        loo (i, N) {
            printf("%lld ", heap[i]);
        }
    }
}

int main()
{
    init();
    core::build();
    debug::print_heap();
    while (N)
        cout<< core::delete_min()<< " ";
    return 0;
}
