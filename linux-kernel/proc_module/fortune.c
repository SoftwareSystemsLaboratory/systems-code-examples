#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>

/*
 * original code by:
 * http://www.ibm.com/developerworks/linux/library/l-proc/index.html
 *
 * fixes by: Joe Kaylor
 *
 */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Fortune Cookie Kernel Module");
MODULE_AUTHOR("M. Tim Jones");

#define MAX_COOKIE_LENGTH       PAGE_SIZE

static struct proc_dir_entry *proc_entry;
static char *cookie_pot;  // Space for fortune strings
static int cookie_index;  // Index to write next fortune
static int next_fortune;  // Index to read next fortune

static const struct file_operations fops =
{
    .owner = THIS_MODULE
};

ssize_t fortune_write(struct file *filp, const char __user *buff, unsigned long len, void *data )
{
    int space_available = (MAX_COOKIE_LENGTH-cookie_index)+1;

    if (len > space_available)
    {
        printk(KERN_INFO "fortune: cookie pot is full!\n");
        return -ENOSPC;
    }

    if (copy_from_user( &cookie_pot[cookie_index], buff, len ))
    {
        return -EFAULT;
    }

    cookie_index += len;

    cookie_pot[cookie_index-1] = 0;

    return len;
}

int fortune_read( char *page, char **start, off_t off, int count, int *eof, void *data )
{
    int len;
    if (off > 0)
    {
        *eof = 1;
        return 0;
    }

    /* Wrap-around */

    if (next_fortune >= cookie_index)
    {
        next_fortune = 0;
    }
    len = sprintf(page, "%s\n", &cookie_pot[next_fortune]);
    next_fortune += len;

    return len;
}

int init_fortune_module( void )
{
    int ret = 0;
    cookie_pot = (char *)vmalloc( MAX_COOKIE_LENGTH );

    if (!cookie_pot)
    {
        ret = -ENOMEM;
    }
    else
    {
        memset( cookie_pot, 0, MAX_COOKIE_LENGTH );

        proc_entry = create_proc_entry( "fortune", 0666, NULL );

        if (proc_entry == NULL)
        {
            ret = -ENOMEM;
            vfree(cookie_pot);
            printk(KERN_INFO "fortune: Couldn't create proc entry\n");
        }
        else
        {
            cookie_index = 0;
            next_fortune = 0;
            proc_entry->read_proc = fortune_read;
            proc_entry->write_proc = fortune_write;
            proc_entry->size = MAX_COOKIE_LENGTH;
            printk(KERN_INFO "fortune: Module loaded.\n");
        }
    }
    return ret;
}

void cleanup_fortune_module( void )
{
    remove_proc_entry("fortune", &proc_entry);
    vfree(cookie_pot);
    printk(KERN_INFO "fortune: Module unloaded.\n");
}


module_init( init_fortune_module );
module_exit( cleanup_fortune_module );

