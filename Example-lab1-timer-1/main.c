#include "embARC.h"
#include "embARC_debug.h"

void to_isr(void *ptr)
{

}

void t1_isr(void *ptr)
{

}

int main(void)
{
    uint32_t val = 0;
    uint64_t cur_us = 0;

    board_delay_ms(5,1);

    timer_current(TIMER_1, &val);
    EMBARC_PRINTF("%d\n", val);
    EMBARC_PRINTF("%d\n", val);
    timer_stop(TIMER_1);
    board_delay_ms(5,1);
    EMBARC_PRINTF("123\n");
    timer_current(TIMER_0, &val);
    EMBARC_PRINTF("%d\n", val);
    timer_current(TIMER_0, &val);
    EMBARC_PRINTF("%d\n", val);

    while(1)
    {
        cur_us = board_get_cur_us();
        timer_stop(TIMER_0);
        EMBARC_PRINTF("%d\n", cur_us);
        //board_delay_ms(1000,1);
    }

    return E_SYS;
}