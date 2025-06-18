#include "buzzer.h"
#include <unistd.h>

int main(void) {
    buzzerInit();

    // 도 ~ 시 ~ 도 1옥타브 재생
    for (int i = 0; i < 8; i++) {
        buzzerPlaySong(i);
        sleep(1);
    }

    buzzerStopSong();
    buzzerExit();
    return 0;
}
