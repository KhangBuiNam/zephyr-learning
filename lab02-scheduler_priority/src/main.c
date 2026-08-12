#include <zephyr/kernel.h>


void thread_a(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    while (1) {
        printk("[A] Priority\n");
        k_sleep(K_SECONDS(1));
    }
}

void thread_b(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    while (1) {
        printk("[B] Got Priority\n");
        k_sleep(K_SECONDS(1));
    }
}

void thread_c(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    while (1) {
        printk("[C] Got Priority\n");
        k_yield();
    }
}

K_THREAD_DEFINE(thread_a_id,1024,thread_a,NULL,NULL,NULL,7,0,0);
K_THREAD_DEFINE(thread_b_id,1024,thread_b,NULL,NULL,NULL,5,0,0);
K_THREAD_DEFINE(thread_c_id,1024,thread_c,NULL,NULL,NULL,3,0,0);

int main(void)
{
    printk("Main thread is running\n");

    while(1) {
        printk("[Main] Running\n");
        k_sleep(K_SECONDS(1));
    }
}