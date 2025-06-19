#ifndef _LED_H_
#define _LED_H_

int ledLibInit(void);
int ledOnOff(int ledNum, int onOFF);
int ledStatus(void);         // 아직 구현되지 않았지만 인터페이스는 있어도 무방
int ledLibExit(void);

#define LED_DRIVER_NAME "/dev/periled"

#endif // _LED_H_
