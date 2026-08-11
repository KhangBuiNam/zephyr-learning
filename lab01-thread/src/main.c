#include <zephyr/kernel.h>

K_MUTEX_DEFINE(print_mutex);

void thread_a(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    while (1) {
        k_mutex_lock(&print_mutex, K_FOREVER);

        printk("Thread A is running\n");

        k_mutex_unlock(&print_mutex);

        k_sleep(K_SECONDS(1));
    }
}

void thread_b(void *arg1, void *arg2, void *arg3)
{
    ARG_UNUSED(arg1);
    ARG_UNUSED(arg2);
    ARG_UNUSED(arg3);

    while (1) {
        k_mutex_lock(&print_mutex, K_FOREVER);

        printk("Thread B is running\n");

        k_mutex_unlock(&print_mutex);

        k_sleep(K_SECONDS(2));
    }
}

K_THREAD_DEFINE(
    thread_a_id,
    1024,
    thread_a,
    NULL,
    NULL,
    NULL,
    5,
    0,
    0
);

K_THREAD_DEFINE(
    thread_b_id,
    1024,
    thread_b,
    NULL,
    NULL,
    NULL,
    5,
    0,
    0
);

int main(void)
{
    printk("Main thread is running\n");

    while (1) {
        printk("Main is alive\n");

        k_sleep(K_SECONDS(3));
    }

    return 0;
}