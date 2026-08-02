#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(hello) {

    pr_info("Hello\n");
    return 0;
}

SYSCALL_DEFINE1(hello_m, int, times) {

    int i;

    if (times < 0)
        return -EINVAL;

    for (i = 0; i < times; i++)
        pr_info("Hello\n");

    return 0;
}