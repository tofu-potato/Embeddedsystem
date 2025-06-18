#ifndef _BUZZER_H_
#define _BUZZER_H_

#define MESSAGE_ID 1122
typedef struct
{
    long int messageNum;
    int keyInput;
    int pressed;
} BUTTON_MSG_T;

int buzzerInit(void);
int buzzerPlaySong(int scale);
int buzzerStopSong(void);
int buzzerExit(void);



#endif // _BUZZER_H_
