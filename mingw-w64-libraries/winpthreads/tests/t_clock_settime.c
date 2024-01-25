#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

static void test_clock_settime()
{
    int rc;
    struct timespec tp, request = { 1, 0 }, remain;

    rc = clock_gettime(CLOCK_REALTIME, &tp);
    assert(rc == 0);
    printf("[%10"PRId64".%09d] clock_gettime (CLOCK_REALTIME)\n", (__int64) tp.tv_sec, (int) tp.tv_nsec);
    
    rc = clock_settime(CLOCK_MONOTONIC, &tp);
    assert(rc == -1 && (errno == EINVAL));
    
    rc = clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tp);
    assert(rc == -1 && (errno == EINVAL));
    
    rc = clock_settime(CLOCK_THREAD_CPUTIME_ID, &tp);
    assert(rc == -1 && (errno == EINVAL));
    
    rc = clock_settime(CLOCK_REALTIME, &tp);
    assert(rc == 0 || (errno == EPERM));

    rc = clock_gettime(CLOCK_REALTIME, &tp);
    assert(rc == 0);
    printf("[%10"PRId64".%09d] clock_gettime (CLOCK_REALTIME)\n", (__int64) tp.tv_sec, (int) tp.tv_nsec);
}

int main(int argc, char *argv[])
{
    test_clock_settime();

    return 0;
}
