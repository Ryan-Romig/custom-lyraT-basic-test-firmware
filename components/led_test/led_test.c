#include "include/led_test.h"
#include "../../main/Global.h"
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#define LED_PIN GPIO_NUM_21
#define BACK_BUTTON_PIN GPIO_NUM_4
#define FORWARD_BUTTON_PIN GPIO_NUM_19
#define CENTER_BUTTON_PIN GPIO_NUM_27
xTaskHandle ledHandle;

void button_listener_task(void *pvParams)
{
    
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BACK_BUTTON_PIN, GPIO_MODE_INPUT);
    while (1)
    {
        if (gpio_get_level(BACK_BUTTON_PIN) == 0 || gpio_get_level(FORWARD_BUTTON_PIN) == 0 || gpio_get_level(CENTER_BUTTON_PIN) == 0)
        {
            gpio_set_level(LED_PIN, 0);
        }
        else
        {
            gpio_set_level(LED_PIN, 1);
        }
        vTaskDelay(20);
    }
}

void init_buttons_listener() { xTaskCreatePinnedToCore(&button_listener_task, "BUTTON_LISTENER", 1024, NULL, 1, NULL,0); }

void slow_led_blink_task(void *pvParams)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while (1)
    {
        printf("slow blink");
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
void fast_led_blink_task(void *pvParams)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while (1)
    {
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(500 / portTICK_RATE_MS);
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}
void fast_blink_led()
{
    if (ledHandle)
    {
        vTaskDelete(ledHandle);
    }
    printf("led is blinking fast");
    xTaskCreatePinnedToCore(&fast_led_blink_task, "LED_BLINK", 1024, NULL, 5, &ledHandle,0);
}
void slow_blink_led()
{
    if (ledHandle)
    {
        vTaskDelete(ledHandle);
    }
    xTaskCreatePinnedToCore(&slow_led_blink_task, "LED_BLINK", 1024, NULL, 5, &ledHandle,0);
}
void wifi_led_blink_task(void *pvParams)
{

    for (;;)
    {
        gpio_pad_select_gpio(LED_PIN);
        gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
        if (wifi_connected == 1)
        {
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(100 / portTICK_RATE_MS);
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(100 / portTICK_RATE_MS);
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(200 / portTICK_RATE_MS);

            gpio_set_level(LED_PIN, 0);
            vTaskDelay(50 / portTICK_RATE_MS);
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(50 / portTICK_RATE_MS);
            gpio_set_level(LED_PIN, 0);
            vTaskDelay(50 / portTICK_RATE_MS);
            gpio_set_level(LED_PIN, 1);
            vTaskDelay(2000 / portTICK_RATE_MS);
            continue;
        }
        vTaskDelay(1);
    }
}
void init_wifi_blink_listener()
{
    if (ledHandle)
    {
        vTaskDelete(ledHandle);
    }

    xTaskCreatePinnedToCore(&wifi_led_blink_task, "WIFI_LED_BLINK", 1024 * 2, NULL, 5, &ledHandle,0);
}
void back_button_blink() { printf("back button LED mode on"); }
void play_button_blink() { printf("play button LED blink"); }
void forward_button_blink() { printf("forward button blink"); }
