#include "mqtt.h"
#include "mgos_mqtt.h"
#include "mgos_sys_config.h"

bool publish(const char *topic, const char *fmt, ...) {
  char msg[200];
  struct json_out jmo = JSON_OUT_BUF(msg, sizeof(msg));
  va_list ap;
  int n;
  va_start(ap, fmt);
  n = json_vprintf(&jmo, fmt, ap);
  va_end(ap);

  return mgos_mqtt_pub(topic, msg, n, get_cfg()->mqtt.pub_qos);
}

bool MQTT_publish_status(const char *state_name, const char *debug_info) {
  char topic_name[32];
  snprintf(topic_name, sizeof(topic_name), "%s/status", get_cfg()->device.id);
  return publish(topic_name, "{state: %Q, debug: %Q}", state_name, debug_info);
}

void cmd_subscription_handler(struct mg_connection *nc, const char *topic,
                              int topic_len, const char *msg, int msg_len,
                              void *ud) {
  LOG(LL_INFO, ("topic=%.*s, msg=%.*s", topic_len, topic, msg_len, msg));

  (void)nc;
  (void)ud;
}

void MQTT_subscribe_cmd() {
  char topic_name[32];
  snprintf(topic_name, sizeof(topic_name), "%s/cmd", get_cfg()->device.id);
  mgos_mqtt_sub(topic_name, &cmd_subscription_handler, NULL);
}