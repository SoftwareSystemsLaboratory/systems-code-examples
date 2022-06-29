//
// Created by gkt on 10/16/20.
//

#include "millisleep.h"
#include <errno.h>
#include <time.h>
#include <stdint.h>

int millisecond_sleep(long milliseconds)
{
    struct timespec sleep_time;
    int status;

    if (milliseconds < 0)
    {
        errno = EINVAL;
        return -1;
    }

    sleep_time.tv_sec = milliseconds / 1000;
    sleep_time.tv_nsec = (milliseconds % 1000) * 1000000;

    do
    {
        status = nanosleep(&sleep_time, &sleep_time);
    }
    while (status && errno == EINTR);

    return status;
}
