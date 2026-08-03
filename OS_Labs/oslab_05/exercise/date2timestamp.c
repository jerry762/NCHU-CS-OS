#include <linux/module.h>
#include <linux/timekeeping.h>
#include <linux/time.h>

int date = 0, month = 0, year = 0;
time64_t ts = 0;

module_param(date, int, 0);
MODULE_PARM_DESC(date, "date of time");

module_param(month, int, 0);
MODULE_PARM_DESC(month, "month of time");

module_param(year, int, 0);
MODULE_PARM_DESC(year, "year of time");


int init_module(void) {
    struct tm birth_tm = {0};

    birth_tm.tm_year = year;
    birth_tm.tm_mon = month;
    birth_tm.tm_mday = date;

    if(year < 0 || month < 0 || date < 0)
    {
        printk(KERN_ERR "Invalid argument(s).\n");
        return -EINVAL;
    }

    ts = mktime64(birth_tm.tm_year, birth_tm.tm_mon, birth_tm.tm_mday,
         birth_tm.tm_hour, birth_tm.tm_min, birth_tm.tm_sec);

    if(ts < (time64_t)0)
    {
        printk(KERN_ERR "Failed to convert date to timestamp.\n");
        return -EINVAL;
    }
    else
    {
        printk(KERN_INFO "date2timestamp insert successfully!, ts=%ld\n", (long)ts);
        return 0;
    }
}


void cleanup_module(void) {
    printk(KERN_INFO "date2timestamp module remove successfully!\n");

}

EXPORT_SYMBOL(ts);


// module information

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William");
MODULE_DESCRIPTION("OSlab5: date2timestamp module");

