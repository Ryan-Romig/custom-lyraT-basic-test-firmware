#include "sdkconfig.h"
extern "C"{
#include "../components/wifi_test/include/wifi_test.h"
#include "../components/dac_test/include/dac_test.h"
}
#include "../components/led_test/include/led_test.hpp"

extern "C" void app_main(void)
{
    init_buttons_listener();
    init_wifi_blink_listener();
    start_wifi_test();
    start_dac_test();
}
