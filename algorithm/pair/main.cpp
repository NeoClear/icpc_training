#include <iostream>
#include <stdio.h>
#include <string.h>

#define MAX 0xffff
typedef long long i64;
#define loz(i, n) for (i64 i = 0; i < static_cast<i64>(n); i++)

using namespace std;

namespace match {
    static char sequence[MAX];

    bool fit(char l, char r)
    {
        if (l == '(' && r == ')')
            return true;
        if (l == '[' && r == ']')
            return true;
        if (l == '{' && r == '}')
            return true;
        return false;
    }

    namespace debug {
        inline void run()
        {
            freopen("in.txt", "r", stdin);
            scanf("%s", sequence);
        }
        inline void print()
        {
            printf("%s\n", sequence);
        }
        inline void print_stack(char *s, i64 top)
        {
            loz(i, top) {
                printf("%c", s[i]);
            }
            printf("\n");
        }
    }

    bool match()
    {
        i64 top = 0;
        char simulate_stack[MAX];
        loz(i, strlen(sequence)) {
            simulate_stack[top++] = sequence[i];
            if (top > 1 && fit(simulate_stack[top - 2], simulate_stack[top - 1]))
                top -= 2;
        }
//        debug::print_stack(simulate_stack, top);
        if (top)
            return false;
        else
            return true;
    }
}

int main()
{
    match::debug::run();
//    match::debug::print();
    if (match::match())
        printf("True\n");
    else
        printf("False\n");
    return 0;
}
