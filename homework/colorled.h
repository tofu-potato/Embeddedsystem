#ifndef __COLORLED_H__
#define __COLORLED_H__

#define PWM_CHIP_R "/sys/class/pwm/pwmchip0/"
#define PWM_CHIP_G "/sys/class/pwm/pwmchip1/"
#define PWM_CHIP_B "/sys/class/pwm/pwmchip2/"

#define PWM_EXPORT     "export"
#define PWM_UNEXPORT   "unexport"
#define PWM_DUTY       "pwm0/duty_cycle"
#define PWM_PERIOD     "pwm0/period"
#define PWM_ENABLE     "pwm0/enable"

#define PWM_PERIOD_NS 1000000  // 1ms = 1kHz

// 색상 인덱스 (0: B, 1: G, 2: R)
#define COLOR_B 0
#define COLOR_G 1
#define COLOR_R 2

// 기능 함수 원형
void colorLedInit(void);
void colorLedSetPercent(int percent, int color); // color: 0(B),1(G),2(R)
void colorLedExit(void);

#endif // __COLORLED_H__
