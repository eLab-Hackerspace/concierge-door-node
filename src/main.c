#include <stdio.h>
#include "mgos_app.h"
#include "mgos_gpio.h"
#include "mgos_sys_config.h"
//#include "bsp.h"
#include "mqtt.h"

#define BUTTON_GPIO 0 /* Usually a "Flash" button. */
#define BUTTON_PULL MGOS_GPIO_PULL_UP
#define BUTTON_EDGE MGOS_GPIO_INT_EDGE_POS

static void button_cb(int pin, void *arg) {
  LOG(LL_INFO, ("Click!"));
  if (MQTT_publish_status("a state", "debug info")) {
    LOG(LL_INFO, ("Published!"));
  }
  (void) pin;
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) {
  //BSP_init();

  MQTT_subscribe_cmd();

  mgos_gpio_set_button_handler(BUTTON_GPIO, BUTTON_PULL, BUTTON_EDGE,
    50 /* debounce_ms */, button_cb, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
