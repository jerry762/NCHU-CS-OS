#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/timekeeping.h>
#include <linux/time.h>

extern time64_t ts;

int init_module(void) {
    
    time64_t current_timestamp = ktime_get_real_seconds();
    
    s64 seconds_diff = current_timestamp - ts;
    
    if (seconds_diff < 0) {
        printk(KERN_ERR "difftime < 0, myage module insert failed!\n");
        return -EINVAL;
    }
    
    printk(KERN_INFO "myage module insert successfully!\n");

    u64 total_days = (u64)seconds_diff / 86400;

    unsigned int years = total_days / 365;
    unsigned int remaining_days = total_days % 365;

    printk(KERN_INFO "Wow you have survived on this world %u years and %u days!\n", years, remaining_days);

    return 0;
}


void cleanup_module(void) {
    printk(KERN_INFO "myage module remove successfully!");
}

// module information

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William");
MODULE_DESCRIPTION("OSlab5: myage module");


