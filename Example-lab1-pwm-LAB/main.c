#include "embARC.h"
#include "embARC_debug.h"

//ADC_DEFINE(adc_test, ADC_INT_NUM, ADC_CRTL_BASE, NULL);

void arduino_pin_init(void)
{
	io_arduino_config(ARDUINO_PIN_3, ARDUINO_PWM, IO_PINMUX_ENABLE);//pwm timer ch0
	io_arduino_config(ARDUINO_PIN_5, ARDUINO_PWM, IO_PINMUX_ENABLE);//pwm timer ch1
	io_arduino_config(ARDUINO_PIN_6, ARDUINO_PWM, IO_PINMUX_ENABLE);//pwm timer ch2
	io_arduino_config(ARDUINO_PIN_9, ARDUINO_PWM, IO_PINMUX_ENABLE);//pwm timer ch3
	io_arduino_config(ARDUINO_PIN_10, ARDUINO_PWM, IO_PINMUX_ENABLE);//pwm timer ch4
	io_arduino_config(ARDUINO_PIN_11, ARDUINO_PWM, IO_PINMUX_ENABLE);//pwm timer ch5
}

int main(void)
{
    arduino_pin_init();
    DEV_PWM_TIMER_PTR pwm_timer_0 = pwm_timer_get_dev(DW_PWM_TIMER_0_ID);
    pwm_timer_0->pwm_timer_open();
    //pwm_timer_0->pwm_timer_control(0x0000, PWM_TIMER_CMD_ENA_CH, (void*)(0<<0));
    uint32_t dc[3] = {0, 0, 0};
    uint32_t offset[3] = {5, 0 ,0};
    int count = 0;
    int times = 0;
    int color = 0;
    bool dir = true;
    //offset[0] = 5;
    //offset[1] = 0;
    //offset[2] = 0;
    while(1)
    {
        if(dir)
        {
            dc[0] += offset[0];
            dc[1] += offset[1];
            dc[2] += offset[2];
        }
        else
        {
            dc[0] -= offset[0];
            dc[1] -= offset[1];
            dc[2] -= offset[2];
        }

        pwm_timer_0->pwm_timer_write(PWM_TIMER0, DEV_PWM_TIMER_MODE_PWM, 100000, dc[0]);
        pwm_timer_0->pwm_timer_write(PWM_TIMER1, DEV_PWM_TIMER_MODE_PWM, 100000, dc[1]);
        pwm_timer_0->pwm_timer_write(PWM_TIMER2, DEV_PWM_TIMER_MODE_PWM, 100000, dc[2]);
        //EMBARC_PRINTF("%d\n", dc);
        board_delay_ms(35,1);
        count++;

        if(count == 20)
        {
            count = 0;
            dir = !dir;
            times++;
            if(times == 4)
            {
                times = 0;
                color++;
                if(color == 7)
                    color = 0;
                switch(color)
                {
                    case 0: // red
                        offset[0] = 5;
                        offset[1] = 0;
                        offset[2] = 0;
                        break;
                    case 1 : // orange
                        offset[0] = 5;
                        offset[1] = 2;
                        offset[2] = 0;
                        break;
                    case 2 : // yellow
                        offset[0] = 5;
                        offset[1] = 5;
                        offset[2] = 0;
                        break;
                    case 3 : // green
                        offset[0] = 0;
                        offset[1] = 5;
                        offset[2] = 0;
                        break;
                    case 4 : // blue
                        offset[0] = 0;
                        offset[1] = 0;
                        offset[2] = 5;
                        break;
                    case 5 : // purple
                        offset[0] = 5;
                        offset[1] = 0;
                        offset[2] = 5;
                        break;
                    case 6 : // white
                        offset[0] = 5;
                        offset[1] = 5;
                        offset[2] = 5;
                        break;
                }
            }
        }
    }

    return E_SYS;
}