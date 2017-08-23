#ifndef DOOR_H
#define DOOR_H

#include "qepn.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum DoorSignals {
    OFF_SIG = Q_USER_SIG,
    ON_SIG
};

void Door_ctor(void);
void Door_post(enum DoorSignals signal);

extern struct DoorTag AO_Door;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //DOOR_H