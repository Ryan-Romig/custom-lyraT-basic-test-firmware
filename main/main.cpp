#include "sdkconfig.h"
#include "../components/wifi_test/include/wifi_test.hpp"
#include "../components/led_test/include/led_test.hpp"

extern "C" void app_main(void)
{
    init_buttons_listener();
}
