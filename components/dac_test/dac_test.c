#include <stdio.h>
#include "../../main/Global.h"
#include "include/dac_test.h"

#include <driver/i2c.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

static const char *TAG = "i2c-example";
#define I2C_SLAVE_ADDR	0x11
#define TIMEOUT_MS		1000
#define DELAY_MS		1000



void dac_test_task() {
	
        uint8_t rx_data[5];
	i2c_config_t conf = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = 18,
		.scl_io_num = 23,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = 400000,
	};
	i2c_param_config(I2C_NUM_0, &conf);
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
	while (1) {
		i2c_master_read_from_device(I2C_NUM_0, I2C_SLAVE_ADDR, rx_data, 5, TIMEOUT_MS/portTICK_RATE_MS);
		ESP_LOG_BUFFER_HEX(TAG, rx_data, 5);
		vTaskDelay(DELAY_MS/portTICK_RATE_MS);
	}
    
}
void start_dac_test()
{
    xTaskCreatePinnedToCore(dac_test_task, TAG, configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);

}