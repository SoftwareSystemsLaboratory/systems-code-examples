#include <minix/drivers.h>
#include <minix/driver.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <minix/ds.h>
#include <machine/cmos.h>
#include "time.h"

/*
 *
 *  Some code borrowed from /usr/src/drivers/readclock
 *
 */


FORWARD _PROTOTYPE( char * time_name,   (void) );
FORWARD _PROTOTYPE( int time_open,      (struct driver *d, message *m) );
FORWARD _PROTOTYPE( int time_close,     (struct driver *d, message *m) );
FORWARD _PROTOTYPE( struct device * time_prepare, (int device) );
FORWARD _PROTOTYPE( void time_from_cmos, (char* buffer, int size));
FORWARD _PROTOTYPE( int time_transfer,  (int procnr, int opcode,
                    u64_t position, iovec_t *iov,
                    unsigned nr_req) );
FORWARD _PROTOTYPE( void time_geometry, (struct partition *entry) );

/* SEF functions and variables. */
FORWARD _PROTOTYPE( void sef_local_startup, (void) );
FORWARD _PROTOTYPE( int sef_cb_init, (int type, sef_init_info_t *info) );

/* Entry points to the time driver. */
PRIVATE struct driver time_tab =
{
    time_name, time_open, time_close,
    nop_ioctl, time_prepare, time_transfer,
    nop_cleanup, time_geometry, nop_alarm,
    nop_cancel, nop_select, nop_ioctl, do_nop,
};

/** Represents the /dev/time device. */
PRIVATE struct device time_device;

PRIVATE char * time_name(void)
{
    printf("time_name()\n");
    return "time";
}

PRIVATE int time_open(d, m)
struct driver *d;
message *m;
{
    printf("time_open()\n");
    return OK;
}

PRIVATE int time_close(d, m)
struct driver *d;
message *m;
{
    printf("time_close()\n");
    return OK;
}

PRIVATE struct device * time_prepare(dev)
int dev;
{
    time_device.dv_base.lo = 0;
    time_device.dv_base.hi = 0;
    time_device.dv_size.lo = 0;
    time_device.dv_size.hi = 0;
    return &time_device;
}

void write_register(int reg_addr, int value)
{
    if(sys_outb(RTC_INDEX, reg_addr) != OK)
    {
        printf("cmos: outb failed of %x\n", RTC_INDEX);
        exit(1);
    }
    if(sys_outb(RTC_IO, value) != OK)
    {
        printf("cmos: outb failed of %x (index %x)\n", RTC_IO, reg_addr);
        exit(1);
    }
}

int bcd_to_dec(int n)
{
    return ((n >> 4) & 0x0F) * 10 + (n & 0x0F);
}

int dec_to_bcd(int n)
{
    return ((n / 10) << 4) | (n % 10);
}

int read_register(int reg_addr)
{
    u32_t r;

    if(sys_outb(RTC_INDEX, reg_addr) != OK)
    {
        printf("cmos: outb failed of %x\n", RTC_INDEX);
        exit(1);
    }
    if(sys_inb(RTC_IO, &r) != OK)
    {
        printf("cmos: inb failed of %x (index %x) failed\n", RTC_IO, reg_addr);
        exit(1);
    }
    return r;
}

int nflag = 0;
int wflag = 0;
int Wflag = 0;
int y2kflag = 0;

void get_time(struct tm *t)
{
    int osec, n;

    do
    {
        osec = -1;
        n = 0;
        do
        {
            /* Clock update in progress? */
            if (read_register(RTC_REG_A) & RTC_A_UIP) continue;

            t->tm_sec = read_register(RTC_SEC);
            if (t->tm_sec != osec)
            {
                /* Seconds changed.  First from -1, then because the
                 * clock ticked, which is what we're waiting for to
                 * get a precise reading.
                 */
                osec = t->tm_sec;
                n++;
            }
        }
        while (n < 2);

        /* Read the other registers. */
        t->tm_min = read_register(RTC_MIN);
        t->tm_hour = read_register(RTC_HOUR);
        t->tm_mday = read_register(RTC_MDAY);
        t->tm_mon = read_register(RTC_MONTH);
        t->tm_year = read_register(RTC_YEAR);

        /* Time stable? */
    }
    while (read_register(RTC_SEC) != t->tm_sec
            || read_register(RTC_MIN) != t->tm_min
            || read_register(RTC_HOUR) != t->tm_hour
            || read_register(RTC_MDAY) != t->tm_mday
            || read_register(RTC_MONTH) != t->tm_mon
            || read_register(RTC_YEAR) != t->tm_year);

    if ((read_register(RTC_REG_B) & RTC_B_DM_BCD) == 0)
    {
        /* Convert BCD to binary (default RTC mode). */
        t->tm_year = bcd_to_dec(t->tm_year);
        t->tm_mon = bcd_to_dec(t->tm_mon);
        t->tm_mday = bcd_to_dec(t->tm_mday);
        t->tm_hour = bcd_to_dec(t->tm_hour);
        t->tm_min = bcd_to_dec(t->tm_min);
        t->tm_sec = bcd_to_dec(t->tm_sec);
    }
    t->tm_mon--;  /* Counts from 0. */

    /* Correct the year, good until 2080. */
    if (t->tm_year < 80) t->tm_year += 100;

    if (y2kflag)
    {
        /* Clock with Y2K bug, interpret 1980 as 2000, good until 2020. */
        if (t->tm_year < 100) t->tm_year += 20;
    }
}

PRIVATE void time_from_cmos(buffer,size)
char *buffer;
int size;
{
    struct tm tVal;

    get_time(&tVal);


    snprintf(buffer, size,
             "%04d-%02d-%02d %02d:%02d:%02d\n",
             tVal.tm_year + 1900, tVal.tm_mon + 1,
             tVal.tm_mday, tVal.tm_hour, tVal.tm_min,
             tVal.tm_sec);
}

PRIVATE int time_transfer(proc_nr, opcode, position, iov, nr_req)
int proc_nr;
int opcode;
u64_t position;
iovec_t *iov;
unsigned nr_req;
{
    int bytes, ret;
    char buffer[1024];

    printf("time_transfer()\n");

    time_from_cmos(buffer, sizeof(buffer));

    bytes = strlen(buffer) - position.lo < iov->iov_size
            ? strlen(buffer) - position.lo
            : iov->iov_size;
    if(bytes <= 0)
    {
        return OK;
    }
    switch(opcode)
    {
    case DEV_GATHER_S:
        ret = sys_safecopyto(proc_nr, iov->iov_addr, 0, (vir_bytes)(buffer+position.lo),bytes,D);
        iov->iov_size -= bytes;
        break;
    default:
        return EINVAL;
    }
    return ret;
}

PRIVATE void time_geometry(entry)
struct partition *entry;
{
    printf("time_geometry()\n");
    entry->cylinders = 0;
    entry->heads     = 0;
    entry->sectors   = 0;
}

PRIVATE void sef_local_startup()
{
    /*
     * Register init callbacks. Use the same function for all event types
     */
    sef_setcb_init_fresh(sef_cb_init);
    sef_setcb_init_lu(sef_cb_init);
    sef_setcb_init_restart(sef_cb_init);

    /*
     * Register live update callbacks.
     */
    /* - Agree to update immediately when LU is requested in a valid state. */
    sef_setcb_lu_prepare(sef_cb_lu_prepare_always_ready);
    /* - Support live update starting from any standard state. */
    sef_setcb_lu_state_isvalid(sef_cb_lu_state_isvalid_standard);

    /* Let SEF perform startup. */
    sef_startup();
}

PRIVATE int sef_cb_init(int type, sef_init_info_t *info)
{
    int do_announce_driver = TRUE;
    switch(type)
    {
    case SEF_INIT_FRESH:
        printf("startup\n");
        break;
    case SEF_INIT_LU:
        printf("new version\n");
        do_announce_driver = FALSE;
        break;
    case SEF_INIT_RESTART:
        printf("restart\n");
        break;
    }
    if(do_announce_driver)
    {
        driver_announce();
    }
    return OK;
}

PUBLIC int main(int argc, char **argv)
{
    /*
     * Perform initialization.
     */
    sef_local_startup();

    /*
     * Run the main loop.
     */
    driver_task(&time_tab, DRIVER_STD);
    return OK;
}

