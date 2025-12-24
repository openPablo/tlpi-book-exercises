/*
When using the Linux-specific reboot() system call to reboot the system, the second
argument, magic2, must be specified as one of a set of magic numbers (e.g.,
LINUX_REBOOT_MAGIC2). What is the significance of these numbers? (Converting them
to hexadecimal provides a clue.)
*/
#include <linux/reboot.h>
#include <stdio.h>

int main(){
    printf("%x\n", LINUX_REBOOT_MAGIC1);
    printf("%x\n", LINUX_REBOOT_MAGIC2);
}

//1969 the year Unix started getting developed