#include "include/led_test.hpp"
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#define LED_PIN GPIO_NUM_21
#define BACK_BUTTON_PIN GPIO_NUM_4
#define FORWARD_BUTTON_PIN GPIO_NUM_19
#define CENTER_BUTTON_PIN GPIO_NUM_27
xTaskHandle ledHandle;
void center_button_listener_task(void* pvParams)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(CENTER_BUTTON_PIN, GPIO_MODE_INPUT);
    while (1) {
        if (gpio_get_level(CENTER_BUTTON_PIN) == 0) {
            gpio_set_level(LED_PIN, 0);
        }
        else{
            gpio_set_level(LED_PIN, 1);
        }
        vTaskDelay(1);
    }
}
void back_button_listener_task(void* pvParams)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BACK_BUTTON_PIN, GPIO_MODE_INPUT);
    while (1) {
        if (gpio_get_level(BACK_BUTTON_PIN) == 0) {
            gpio_set_level(LED_PIN, 0);
        }
        else{
            gpio_set_level(LED_PIN, 1);
        }
        vTaskDelay(1);
    }
}
void forward_button_listener_task(void* pvParams)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(FORWARD_BUTTON_PIN, GPIO_MODE_INPUT);
    while (1) {
        if (gpio_get_level(FORWARD_BUTTON_PIN) == 0) {
            gpio_set_level(LED_PIN, 0);
        }
        else{
            gpio_set_level(LED_PIN, 1);
        }
        vTaskDelay(1);
    }
}
void init_button_listeners(){
    xTaskCreate(&center_button_listener_task, "LED_BLINK", 512, NULL, 5, NULL);
    xTaskCreate(&back_button_listener_task, "LED_BLINK", 512, NULL, 5, NULL);
    // xTaskCreate(&forward_button_listener_task, "LED_BLINK", 512, NULL, 5, NULL);
}

void slow_led_blink_task(void* pvParams)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
void fast_led_blink_task(void* pvParams)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(500 / portTICK_RATE_MS);
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}
void fast_blink_led()
{
    if (ledHandle) {
        vTaskDelete(ledHandle);
    }
    printf("led is blinking fast");
    xTaskCreate(&fast_led_blink_task, "LED_BLINK", 512, NULL, 5, &ledHandle);
}
void slow_blink_led()
{
    if (ledHandle) {
        vTaskDelete(ledHandle);
    }
    printf("led is blinking slow");
    xTaskCreate(&slow_led_blink_task, "LED_BLINK", 512, NULL, 5, &ledHandle);
}
void back_button_blink() { printf("back button LED mode on"); }
void play_button_blink() { printf("play button LED blink"); }
void forward_button_blink() { printf("forward button blink"); }
void wifi_on_blink() { printf("forward blink"); }