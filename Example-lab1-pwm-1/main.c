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
    uint32_t dc = 0;
    uint32_t offset = 1;
    bool dir = true;
    while(1)
    {
        if(dir)
            dc += offset;
        else
            dc -= offset;
         
        pwm_timer_0->pwm_timer_write(PWM_TIMER0, DEV_PWM_TIMER_MODE_PWM, 100000, dc);
        //EMBARC_PRINTF("%d\n", dc);
        board_delay_ms(7,1);

        if(dc == 100 || dc == 0)
            dir = !dir;
    }

    return E_SYS;
}