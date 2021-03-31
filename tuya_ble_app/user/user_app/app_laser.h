#ifndef __APP_LASER_H__
#define __APP_LASER_H__

#include "tuya_ble_common.h"
#include "tuya_ble_log.h"

#define DP_LASER_SWITCH        (1)

typedef struct {
    bool laser_switch;
}APP_CTRL_DATA_T;

typedef enum {
	Raw = 0,
	Bool,
	Value,
	String,
	Enum,
	Bitmap,
}DP_TYPE_T;

void app_init(void);
void app_ctrl_handle(void);
void app_dp_report(uint8_t dp_id, uint8_t *dp_value, DP_TYPE_T dp_type);
void app_dp_handle(uint8_t *dp_data);

#endif
