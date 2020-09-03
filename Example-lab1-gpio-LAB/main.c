#include "embARC.h"
#include "embARC_debug.h"

#define GPIO4B2_0_OFFSET	0
#define GPIO4B2_1_OFFSET	1
#define GPIO4B2_2_OFFSET	2
#define GPIO4B2_3_OFFSET	3

static int mode = 0;

static void next_mode(DEV_GPIO_PTR gpio_4b2)
{
    mode++;
    if(mode == 4) {mode = 0;}

    switch(mode)
    {
        case 0 :
            gpio_4b2->gpio_write(0<<GPIO4B2_1_OFFSET, 1<<GPIO4B2_1_OFFSET);
            EMBARC_PRINTF("mode 0\n");
            break;
        case 1 :
            gpio_4b2->gpio_write(1<<GPIO4B2_3_OFFSET, 1<<GPIO4B2_3_OFFSET);
            EMBARC_PRINTF("mode 1\n");
            break;
        case 2 :
            gpio_4b2->gpio_write(1<<GPIO4B2_2_OFFSET, 1<<GPIO4B2_3_OFFSET|1<<GPIO4B2_2_OFFSET);
            EMBARC_PRINTF("mode 2\n");
            break;
        case 3 :
            gpio_4b2->gpio_write(1<<GPIO4B2_1_OFFSET, 1<<GPIO4B2_2_OFFSET|1<<GPIO4B2_1_OFFSET);
            EMBARC_PRINTF("mode 3\n");
            break;
    }     

}

int main(void)
{
    DEV_GPIO_PTR gpio_4b2 = gpio_get_dev(DFSS_GPIO_4B2_ID);

    uint32_t read_value = 0;

    gpio_4b2->gpio_open(1<<GPIO4B2_3_OFFSET|1<<GPIO4B2_2_OFFSET|1<<GPIO4B2_1_OFFSET);


    while(1)
    {
        gpio_4b2->gpio_read(&read_value, 1<<GPIO4B2_0_OFFSET);

        if(read_value == 1)
        {
            //board_delay_ms(30, 1);
            gpio_4b2->gpio_read(&read_value, 1<<GPIO4B2_0_OFFSET);
            if(read_value == 1)
            {
                EMBARC_PRINTF("next\n");
                next_mode(gpio_4b2);
                while(read_value == 1)
                {
                     gpio_4b2->gpio_read(&read_value, 1<<GPIO4B2_0_OFFSET);
                }
            }
        }
        //board_delay_ms(100,1);
    }

    return E_SYS;
}