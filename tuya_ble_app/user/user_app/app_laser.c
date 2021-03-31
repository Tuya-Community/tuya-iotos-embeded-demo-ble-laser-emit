#include "app_laser.h"



#define LASER_IO                      GPIO_PD2
#define time_ms                       (1000)
unsigned long time_tick = 0;

APP_CTRL_DATA_T app_ctrl_data = {0};

void app_init(void)
{
	gpio_set_func(LASER_IO ,AS_GPIO);
    gpio_set_output_en(LASER_IO, 1);
}

void app_ctrl_handle(void)
{
	if(!clock_time_exceed(time_tick, time_ms*500)) {
		return ;
	}
	time_tick = clock_time();

    TUYA_APP_LOG_INFO("-----enter user app handle-------\n");

    if(app_ctrl_data.laser_switch) {
        gpio_write(LASER_IO, 1);
    }else {
    	gpio_write(LASER_IO, 0);
    }

}

void app_dp_report(uint8_t dp_id, uint8_t *dp_value, DP_TYPE_T dp_type)
{
	uint8_t dp_buf[50] = {0};
    uint8_t dp_len = 0;
	dp_buf[0] = dp_id;
	dp_buf[1] = dp_type;

	switch(dp_type) {
	case Raw:

		break;
	case Bool:
		dp_len = 5;
	    dp_buf[2] = 0x00;
	    dp_buf[3] = 0x01;
	    dp_buf[4] = *dp_value;
		break;
	case Value:
		dp_len = 8;
	    dp_buf[2] = 0x00;
	    dp_buf[3] = 0x04;
	    dp_buf[4] = (uint8_t)(*dp_value >> 24);
	    dp_buf[5] = (uint8_t)(*dp_value >> 16);
	    dp_buf[6] = (uint8_t)(*dp_value >> 8);
	    dp_buf[7] = (uint8_t)*dp_value;
		break;
	case String:
		break;
	case Enum:
		dp_len = 5;
	    dp_buf[2] = 0x00;
	    dp_buf[3] = 0x01;
	    dp_buf[4] = *dp_value;
		break;
	default:
		break;
	}
    tuya_ble_dp_data_report(dp_buf,dp_len);
}

void app_dp_handle(uint8_t *dp_data)
{
	if((dp_data[0] == 0x01)&&(dp_data[1] == Bool)){
		app_ctrl_data.laser_switch = dp_data[3];
	}

}
