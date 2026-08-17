#include <zephyr/kernel.h>

K_SEM_DEFINE(data_sem, 0, 3);

int main(void)
{
    printk("Initial count = %u\n",
           k_sem_count_get(&data_sem));

    k_sem_give(&data_sem);
    k_sem_give(&data_sem);
    k_sem_give(&data_sem);

    printk("After gives = %u\n",
           k_sem_count_get(&data_sem));

    k_sem_take(&data_sem, K_NO_WAIT);
    k_sem_take(&data_sem, K_NO_WAIT);

    printk("After takes = %u\n",
           k_sem_count_get(&data_sem));

    return 0;
}