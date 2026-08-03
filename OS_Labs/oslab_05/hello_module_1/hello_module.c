#include <linux/module.h>

int init_module(void) {

    printk(KERN_INFO "Hello module insert successfully!\n");
    return 0;

}


void cleanup_module(void) {
    printk(KERN_INFO "Hello module remove successfully!\n");
}

// module information ex: lsmod -> modinfo

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William");
MODULE_DESCRIPTION("OSlab5: hello_module");


