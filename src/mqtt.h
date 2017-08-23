#ifndef MQTT_H
#define MQTT_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

bool MQTT_publish_status(const char *state_name, const char *debug_info);
void MQTT_subscribe_cmd();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //MQTT_H