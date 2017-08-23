#include "door.h"
#include "bsp.h"
#include "common/cs_dbg.h"
#include "qepn.h"
#include "user_interface.h"
#include "osapi.h"

#define DOOR_TASK_PRIORITY USER_TASK_PRIO_0
#define DOOR_TASK_QUEUE_SIZE 32

typedef struct DoorTag {
  QHsm super;
  os_timer_t timer;
  os_event_t ev_queue[DOOR_TASK_QUEUE_SIZE];
} Door;


Door AO_Door;

static void door_task(os_event_t *e) {
  Door *const me = &AO_Door;
  Q_SIG(&me->super) = e->sig;
  // Q_PAR(&me->super) = e->par;
  QHSM_DISPATCH(&me->super); /* dispatch to the HSM (RTC step) */
}

static void timer_cb(void *arg) {
  LOG(LL_INFO, ("Timer callback"));
  Door_post(Q_TIMEOUT_SIG);
  (void)arg;
}

void Door_ctor(void) {
  Door *const me = &AO_Door;

  //init task
  system_os_task(door_task, DOOR_TASK_PRIORITY, me->ev_queue, DOOR_TASK_QUEUE_SIZE);

  //set timer function
  os_timer_disarm(&me->timer);
  os_timer_setfn(&me->timer, timer_cb, NULL);

  //hsm ctor and init
  //QHsm_ctor(&me->super, Q_STATE_CAST(&Door_initial));
  QHSM_INIT(&me->super);
}

void Door_post(enum DoorSignals signal) {
  if (!system_os_post(DOOR_TASK_PRIORITY, signal, (os_param_t)0)) {
    LOG(LL_INFO, ("Error posting"));
  }
}


void Door_set_timer(int msecs, bool repeat) {
  Door *const me = &AO_Door;
  os_timer_disarm(&me->timer);
  os_timer_arm(&me->timer, msecs, repeat);
}

void Door_clear_timer() {
  Door *const me = &AO_Door;
  os_timer_disarm(&me->timer);
}