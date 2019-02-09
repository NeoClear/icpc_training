#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int expo, x, y;
int board[1025][1025];

void chess(int tx, int ty, int cx, int cy, int size)
{
    if (size == 1)
        return;

}

void print()
{
    for (int i = 1; i <= expo; i++) {
        for (int j = 1; j <= expo; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    cin>>expo>>x>>y;
    int ans = 1;
    for (int i = 0; i < expo; i++)
        ans *= 2;
    expo = ans;
    board[x][y] = 7;
    chess(1, 1, x, y, expo);
    print();
    return 0;
}


















//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>

//#define MAX 1025
//typedef long long i64;

//using namespace std;

//enum mode {
//    squre,
//    angle
//};

//enum direction {
//    top_left,
//    top_right,
//    bot_left,
//    bot_right,
//    arbitrary
//};

//struct coordinate
//{
//    i64 row;
//    i64 column;
//}impare;

//i64 expo;
//i64 range;
//char chessbord[MAX][MAX];

//i64 nrpower(i64 base, i64 time)
//{
//    if (time == 0)
//        return 1;
//    i64 ans = 1;
//    while (time > 0) {
//        if (time & 1 == 1)
//            ans *= base;
//        base *= base;
//        time >>= 1;
//    }
//    return ans;
//}

//inline void init()
//{
//    freopen("in.txt", "r", stdin);
//    scanf("%lld%lld%lld", &expo, &impare.row, &impare.column);
//    range = nrpower(2, expo);
//}

//direction position(coordinate find, coordinate top_l, coordinate bot_r)
//{
//    coordinate mid;
//    mid.row = (top_l.row + bot_r.row) / 2;
//    mid.column = (top_l.column + bot_r.column) / 2;
//    if (find.row >= top_l.row && find.row <= mid.row && find.column >= top_l.column && find.column <= mid.column)
//        return top_left;
//    else if (find.row >= top_l.row && find.row <= mid.row && find.column > mid.column && find.column <= bot_r.column)
//        return top_right;
//    else if (find.row > mid.row && find.row <= bot_r.row && find.column >= top_l.column && find.column <= mid.column)
//        return bot_left;
//    else
//        return bot_right;
//}

//void paint(mode m, direction d, coordinate top_l, coordinate bot_r)
//{
////    cout<<m<<d<<endl;
////    printf("%lld %lld, %lld %lld\n", top_l.row, top_l.column, bot_r.row, bot_r.column);
//    switch (m) {
//    case squre:
//        if (bot_r.row - top_l.row == 1) {
//            chessbord[impare.row][impare.column] = '7';
//            paint(angle, position(impare, top_l, bot_r), top_l, bot_r);
//        } else {
//            coordinate mid;
//            coordinate tdd;
//            switch (position(impare, top_l, bot_r)) {
//            case top_left:
//                mid.row = (top_l.row + bot_r.row) / 2;
//                mid.column = (top_l.column + bot_r.column) / 2;
//                paint(squre, arbitrary, top_l, mid);
//                paint(angle, top_left, top_l, bot_r);
//                break;
//            case top_right:
//                mid.row = top_l.row;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                tdd.row = (top_l.row + bot_r.row) / 2;
//                tdd.column = bot_r.column;
//                paint(squre, arbitrary, mid, tdd);
//                paint(angle, top_right, top_l, bot_r);
//                break;
//            case bot_left:
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = top_l.column;
//                tdd.row = bot_r.row;
//                tdd.column = (top_l.column + bot_r.column) / 2;
//                paint(squre, arbitrary, mid, tdd);
//                paint(angle, bot_left, top_l, bot_r);
//                break;
//            case bot_right:
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                paint(squre, arbitrary, mid, bot_r);
//                paint(angle, bot_right, top_l, bot_r);
//                break;
//            }
//        }
//        break;
//    case angle:
//        if (bot_r.row - top_l.row == 1) {
//            switch (d) {
//            case top_left:
//                chessbord[bot_r.row][bot_r.column] = '4';
//                chessbord[bot_r.row][bot_r.column - 1] = '4';
//                chessbord[bot_r.row - 1][bot_r.column] = '4';
//                break;
//            case top_right:
//                chessbord[top_l.row][top_l.column] = '3';
//                chessbord[top_l.row + 1][top_l.column] = '3';
//                chessbord[top_l.row + 1][top_l.column + 1] = '3';
//                break;
//            case bot_left:
//                chessbord[top_l.row][top_l.column] = '2';
//                chessbord[top_l.row][top_l.column + 1] = '2';
//                chessbord[top_l.row + 1][top_l.column + 1] = '2';
//                break;
//            case bot_right:
//                chessbord[top_l.row][top_l.column] = '1';
//                chessbord[top_l.row][top_l.column + 1] = '1';
//                chessbord[top_l.row + 1][top_l.column] = '1';
//                break;
//            }
//        } else {
//            coordinate mid, tdd;
//            switch (d) {
//            case top_left:
//                mid.row = top_l.row;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                tdd.row = (top_l.row + bot_r.row) / 2;
//                tdd.column = bot_r.column;
//                paint(angle, bot_left, mid, tdd);//top right
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                paint(angle, top_left, mid, bot_r);//bot right
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = top_l.column;
//                tdd.row = bot_r.row;
//                tdd.column = (top_l.column + bot_r.column) / 2 + 1;
//                paint(angle, top_right, mid, tdd);//bot left
//                mid.row = ((top_l.row + bot_r.row) / 2 + top_l.row) / 2 + 1;
//                mid.column = ((top_l.column + bot_r.column) / 2 + top_l.column) / 2 + 1;
//                tdd.row = ((top_l.row + bot_r.row) / 2 + 1 + bot_r.row) / 2;
//                tdd.column = ((top_l.column + bot_r.column) / 2 + 1 + bot_r.column) / 2;
//                paint(angle, top_left, mid, tdd);//middle
//                break;
//            case top_right:
//                mid.row = (top_l.row + bot_r.row) / 2;
//                mid.column = (top_l.column + bot_r.column) / 2;
//                paint(angle, bot_right, top_l, mid);//top left
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                paint(angle, top_left, mid, bot_r);//bot right
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = top_l.column;
//                tdd.row = bot_r.row;
//                tdd.column = (top_l.column + bot_r.column) / 2 + 1;
//                paint(angle, top_right, mid, tdd);//bot left
//                mid.row = ((top_l.row + bot_r.row) / 2 + top_l.row) / 2 + 1;
//                mid.column = ((top_l.column + bot_r.column) / 2 + top_l.column) / 2 + 1;
//                tdd.row = ((top_l.row + bot_r.row) / 2 + 1 + bot_r.row) / 2;
//                tdd.column = ((top_l.column + bot_r.column) / 2 + 1 + bot_r.column) / 2;
//                paint(angle, top_right, mid, tdd);//middle
//                break;
//            case bot_left:
//                mid.row = (top_l.row + bot_r.row) / 2;
//                mid.column = (top_l.column + bot_r.column) / 2;
//                paint(angle, bot_right, top_l, mid);//top left
//                mid.row = top_l.row;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                tdd.row = (top_l.row + bot_r.row) / 2;
//                tdd.column = bot_r.column;
//                paint(angle, bot_left, mid, tdd);//top right
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                paint(angle, top_left, mid, bot_r);//bot right
//                mid.row = ((top_l.row + bot_r.row) / 2 + top_l.row) / 2 + 1;
//                mid.column = ((top_l.column + bot_r.column) / 2 + top_l.column) / 2 + 1;
//                tdd.row = ((top_l.row + bot_r.row) / 2 + 1 + bot_r.row) / 2;
//                tdd.column = ((top_l.column + bot_r.column) / 2 + 1 + bot_r.column) / 2;
//                paint(angle, bot_left, mid, tdd);//middle
//                break;
//            case bot_right:
//                mid.row = (top_l.row + bot_r.row) / 2;
//                mid.column = (top_l.column + bot_r.column) / 2;
//                paint(angle, bot_right, top_l, mid);//top left
//                mid.row = (top_l.row + bot_r.row) / 2 + 1;
//                mid.column = top_l.column;
//                tdd.row = bot_r.row;
//                tdd.column = (top_l.column + bot_r.column) / 2 + 1;
//                paint(angle, top_right, mid, tdd);//bot left
//                mid.row = top_l.row;
//                mid.column = (top_l.column + bot_r.column) / 2 + 1;
//                tdd.row = (top_l.row + bot_r.row) / 2;
//                tdd.column = bot_r.column;
//                paint(angle, bot_left, mid, tdd);//top right
//                mid.row = ((top_l.row + bot_r.row) / 2 + top_l.row) / 2 + 1;
//                mid.column = ((top_l.column + bot_r.column) / 2 + top_l.column) / 2 + 1;
//                tdd.row = ((top_l.row + bot_r.row) / 2 + 1 + bot_r.row) / 2;
//                tdd.column = ((top_l.column + bot_r.column) / 2 + 1 + bot_r.column) / 2;
//                paint(angle, bot_right, mid, tdd);//middle
//                break;
//            }
//        }

//        break;
//    default:
//        printf("you must be kidding me.\n");
//    }
//}

//inline void print_all()
//{
//    for (int i = 1; i <= range; i++) {
//        for (int j = 1; j <= range; j++) {
//            printf("%c ", chessbord[i][j]);
//        }
//        printf("\n");
//    }
//}

//int main()
//{
//    init();
//    coordinate top_l, bot_r;
//    top_l.row = 1;
//    top_l.column = 1;
//    bot_r.row = range;
//    bot_r.column = range;
//    paint(squre, arbitrary, top_l, bot_r);
//    print_all();
//    return 0;
//}
