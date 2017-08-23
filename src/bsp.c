#include "bsp.h"
#include "mgos_gpio.h"
#include "mgos_sys_config.h"
#include "qepn.h"
#include "qassert.h"

Q_DEFINE_THIS_FILE

#define LED_GPIO 2
#define STEP_STICK_ENABLE_GPIO 4
#define STEP_STICK_DIR_GPIO 13
#define STEP_STICK_STEP_GPIO 15
#define DOOR_SWITCH_GPIO 5
#define DOOR_SWITCH_PULL MGOS_GPIO_PULL_UP
#define DOOR_SWITCH_EDGE MGOS_GPIO_INT_EDGE_ANY
#define LOCK_SWITCH_GPIO 0
#define LOCK_SWITCH_PULL MGOS_GPIO_PULL_UP
#define LOCK_SWITCH_EDGE MGOS_GPIO_INT_EDGE_ANY
#define NOT_USED_SWITCH_GPIO 3
#define NOT_USED_SWITCH_PULL MGOS_GPIO_PULL_UP
#define NOT_USED_SWITCH_EDGE MGOS_GPIO_INT_EDGE_ANY

void BSP_init(void) {
  mgos_gpio_set_mode(LED_GPIO, MGOS_GPIO_MODE_OUTPUT);
}

void BSP_ledOn() { mgos_gpio_write(LED_GPIO, true); }
void BSP_ledOff() { mgos_gpio_write(LED_GPIO, false); }

void Q_onAssert(char const Q_ROM *const file, int line) {
  LOG(LL_ERROR, ("Assert: %s:%d", file, line));
}