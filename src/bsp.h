#ifdef BSP_H
#define BSP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void BSP_init(void);

void BSP_ledOn();
void BSP_ledOff();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //BSP_H