/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <errno.h>
#include <time.h>
#include <windows.h>
#include "pthread.h"
#include "pthread_time.h"

#define POW10_2 100LL
#define POW10_3 1000LL
#define POW10_4 10000LL
#define POW10_6 1000000LL
#define POW10_7 10000000LL
#define POW10_9 1000000000LL

/**
 * Sleep for the specified time.
 * @param  request The desired amount of time to sleep.
 * @param  remain The remain amount of time to sleep.
 * @return If the function succeeds, the return value is 0.
 *         If the function fails, the return value is -1,
 *         with errno set to indicate the error.
 */
int nanosleep(const struct timespec *request, struct timespec *remain)
{
    const struct _pthread_v *s = __pthread_self_lite();
    long long starting_time, ending_time, frequency;
    HANDLE h;
    DWORD rc;

    if (request->tv_sec < 0 || request->tv_nsec < 0 || request->tv_nsec >= POW10_9) {
        errno = EINVAL;
        return -1;
    }

    QueryPerformanceCounter(&starting_time);
    QueryPerformanceFrequency(&frequency);

    if (s->high_res_timer) {
        /* 100ns units, relative time (negative) */
        const long long dt = -(request->tv_sec * POW10_7 + request->tv_nsec / POW10_2);
        h = s->high_res_timer;
        SetWaitableTimer(h, &dt, 0, NULL, NULL, FALSE);
        timeout = INFINITE;
    } else {
        const long long dt = request->tv_sec * POW10_3 + request->tv_nsec / POW10_6;
        h = INVALID_HANDLE_VALUE;
        timeout = dt < INFINITE ? dt : INFINITE - 1;
    }

    pthread_testcancel();
    rc = WaitForSingleObjectEx(h, timeout, TRUE);
    pthread_testcancel();

    if (remain != NULL) {
        long long ending_time, elapsed, frequency;
        QueryPerformanceCounter(&ending_time);
        QueryPerformanceFrequency(&frequency);
        elapsed = (ending_time - starting_time) * POW10_9 / frequency;
        remain->tv_sec = elapsed / POW10_9;
        remain->tv_nsec = elapsed % POW10_9;
    }

    switch (rc) {
    case WAIT_TIMEOUT:
        return 0;
    case WAIT_IO_COMPLETION:
    case WAIT_OBJECT_0:
        errno = EINTR;
        return -1;
    case WAIT_FAILED:
        errno = 0;
        return -1;
    case WAIT_ABANDONED:
        UNREACHABLE();
    }
}
