#include <zephyr/kernel.h>

K_SEM_DEFINE(data_sem, 1, 1);

void fake_isr(void){
    k_sem_give(&data_sem);
}

void thread_worker(void *arg1, void *arg2, void *arg3)
{
    const char *thread_name = (const char *)arg1;
    while (1) {
        int ret = k_sem_take(&data_sem, K_MSEC(200));

        if (ret == 0) {
            printk("Thread %s: Got the semaphore!\n", thread_name);
            k_sleep(K_MSEC(500));
            k_sem_give(&data_sem);
            printk("Thread %s: Released the semaphore.\n", thread_name);
        } else {
            printk("Thread %s: Timeout while waiting for the semaphore.\n", thread_name);
        }
        k_sleep(K_MSEC(500)); 
    }
}

K_THREAD_DEFINE(tid_prod, 512, thread_worker, "Producer", NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(tid_cons, 512, thread_worker, "Consumer", NULL, NULL, 5, 0, 0);

int main(void)
{
    k_sleep(K_FOREVER);
}