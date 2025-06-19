#ifndef __TEXTLCD_H__
#define __TEXTLCD_H__

#define LINE_NUM        2
#define COLUMN_NUM      16
#define LINE_BUFF_NUM   (COLUMN_NUM + 4)  // dummy 포함

#define TEXT_LCD_DEVICE "/dev/peritextlcd"

// 명령어 정의
#define CMD_DISPLAY_MODE             0x10
#define CMD_CURSOR_MOVE_MODE        0x11
#define CMD_CURSOR_MOVE_POSITION    0x12
#define CMD_WRITE_STRING            0x20

// cmdData 값 정의
#define CMD_DATA_WRITE_BOTH_LINE    0
#define CMD_DATA_WRITE_LINE_1       1
#define CMD_DATA_WRITE_LINE_2       2

// LCD 출력 함수
int lcdTextWrite(const char* str1, const char* str2, int lineFlag);

#endif // __TEXTLCD_H__
