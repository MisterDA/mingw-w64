#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread_time.h>
#include <windows.h>

static unsigned __stdcall start_address(void *dummy)
{
    int counter = 0;
    struct timespec request = { 1, 0 }, remain;
    (void)dummy;

    while (counter < 5) {
        int rc = nanosleep(&request, &remain);
        if (rc != 0) {
            printf("nanosleep interrupted, remain %d.%09d sec.\n",
                (int) remain.tv_sec, (int) remain.tv_nsec);
        } else {
            printf("nanosleep succeeded.\n");
        }

        counter ++;
    }

    return 0;
}

static void WINAPI usr_apc(ULONG_PTR dwParam)
{
    long *index = (long *) dwParam;
    printf("running apc %ld\n", *index);
}

static void test_apc(void)
{
    long i, data[5];
    HANDLE thread;
    DWORD rc;

    thread = (HANDLE)(uintptr_t) _beginthreadex(NULL, 0, start_address, NULL, 0, NULL);
    if (thread == NULL) {
        exit(1);
    }

    for (i = 0; i < 5; i++) {
        data[i] = i;
        Sleep(250U + (unsigned)rand() % 250U);
        rc = QueueUserAPC(usr_apc, thread, (ULONG_PTR) & data[i]);
        if (rc == 0) {
            printf("QueueUserAPC failed: %ld\n", GetLastError());
            exit(1);
        }
    }

    rc = WaitForSingleObject(thread, INFINITE);
    if (rc != WAIT_OBJECT_0) {
        printf("WaitForSingleObject failed with %ld: %ld\n", rc, GetLastError());
        exit(1);
    }
}

int main(void)
{
    int rc;
    struct timespec request = { 1, 0 }, remain;
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;

    srand((unsigned)time(NULL));

    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);

    rc = nanosleep(&request, &remain);

    QueryPerformanceCounter(&EndingTime);
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

    if (rc != 0) {
        printf("remain: %d.%09d\n", (int) remain.tv_sec, (int) remain.tv_nsec);
    }

    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    printf("sleep %d ms\n\n", (int) ElapsedMicroseconds.QuadPart);

    test_apc();

    return 0;
}
