

#include <linux/module.h>



/* Defines the license for this LKM */

MODULE_LICENSE("GPL");



/* Init function called on module entry */

int my_module_init( void )

{

    printk(KERN_INFO "my_module_init called.  Module is now loaded.\n");



    return 0;

}



/* Cleanup function called on module exit */

void my_module_cleanup( void )

{

    printk(KERN_INFO "my_module_cleanup called.  Module is now unloaded.\n");



    return;

}



/* Declare entry and exit functions */

module_init( my_module_init );

module_exit( my_module_cleanup );
