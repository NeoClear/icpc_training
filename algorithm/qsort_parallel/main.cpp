#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>

#define inf 0xffffff
#define MAX_THREADS 8
typedef long long i64;

using namespace std;

static i64 seq[inf];
static i64 N;
static i64 threads = 0;

namespace Profiler {
    static clock_t start_t, end_t;
    static void start() {
        start_t = clock();
    }
    static void end() {
        end_t = clock();
    }
    static double duration() {
        double clc = static_cast<double>(end_t - start_t);
        double cps = static_cast<double>(CLOCKS_PER_SEC);
        return clc / cps;
    }
}

void qsort_parallel(i64 begin, i64 end, bool isNewThread)
{
//    this_thread::sleep_for(chrono::milliseconds(5000));
//    printf("%lld, %lld\n", begin, end);
//    cout<< threads<< endl;
    if (begin > end) {
        if (isNewThread)
            threads--;
        return;
    }
//    if (isNewThread)
//        threads++;
    i64 i = begin;
    i64 j = end;
    i64 standard = seq[begin];
    while (i < j) {
        while (seq[j] >= standard && i < j)
            j--;
        while (seq[i] <= standard && i < j)
            i++;
        if (i < j)
            swap(seq[i], seq[j]);
    }
    swap(seq[begin], seq[i]);
    if (threads < MAX_THREADS) {
        threads += 2;
        thread t(qsort_parallel, begin, i - 1, true);
        t.detach();
        thread q(qsort_parallel, i + 1, end, true);
        q.detach();
    } else {
        qsort_parallel(begin, i - 1, false);
        qsort_parallel(i + 1, end, false);
    }
    if (isNewThread)
        threads--;
}

void qst(i64 begin, i64 end)
{
    if (begin > end)
        return;
    i64 i = begin;
    i64 j = end;
    i64 standard = seq[begin];
    while (i < j) {
        while (seq[j] >= standard && i < j)
            j--;
        while (seq[i] <= standard && i < j)
            i++;
        if (i < j)
            swap(seq[i], seq[j]);
    }
    swap(seq[begin], seq[i]);
    qst(begin, i - 1);
    qst(i + 1, end);
}

int main()
{
    freopen("in.txt", "r", stdin);
    cin >>N;
    for (i64 i = 1; i <= N; ++i) {
        cin >>seq[i];
    }
    Profiler::start();
    qsort_parallel(1, N, false);
//    qst(1, N);
    this_thread::sleep_for(chrono::milliseconds(1));

    while (1) {
        cout<<threads<<endl;
        if (threads == 0)
            break;
        this_thread::sleep_for(chrono::milliseconds(1));
    }
//    for (i64 i = 1; i <= N; ++i) {
//        cout<< seq[i]<< " ";
//    }
    Profiler::end();
    printf("%lf\n", Profiler::duration());
    cout<< seq[1]<< endl;
    return 0;
}
