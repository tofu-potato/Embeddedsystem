#ifndef __FND_H__
#define __FND_H__

#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)

// FND에 표시할 데이터를 담는 구조체
typedef struct FNDWriteDataForm_tag {
    char DataNumeric[FND_DATA_BUFF_LEN];  // 각 자리 숫자 (0~9)
    char DataDot[FND_DATA_BUFF_LEN];      // 각 자리 dot 여부 (1: on, 0: off)
    char DataValid[FND_DATA_BUFF_LEN];    // 각 자리 유효 여부 (1: 표시, 0: 무시)
} stFndWriteForm, *pStFndWriteForm;

// 숫자를 FND에 출력하는 함수
// num: 표시할 숫자 (0~999999), dotflag: 각 자리 dot 표시 여부 (비트 플래그)
int fndDisp(int num, int dotflag);

#endif // __FND_H__
