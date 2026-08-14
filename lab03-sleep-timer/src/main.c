#include <zephyr/kernel.h>

void timer_expiry_function(struct k_timer *timer)
{
    printk("Timer expired\n");
}

/*void thread_high(void *a, void *b, void *c)
{
    while (1) {
        printk("Woke up — preempting LOW \n ");
        k_sleep(K_SECONDS(1));
        printk("Done, going back to sleep \n ");
        k_sleep(K_SECONDS(1));
    }
}
*/


K_TIMER_DEFINE(my_timer, timer_expiry_function, NULL);

int main(void){
    printk("Starting timer\n");
    k_timer_start(&my_timer, K_SECONDS(3), K_SECONDS(2));

    while (1) {
        k_sleep(K_SECONDS(1));
        printk("LOW thread is running \n ");    
    }
}