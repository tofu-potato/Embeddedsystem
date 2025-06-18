#include "button.h"
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>

int main(void) {
    BUTTON_MSG_T msg;
    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);

    if (!buttonInit()) {
        printf("Button init failed\n");
        return -1;
    }

    while (1) {
        if (msgrcv(msgID, &msg, sizeof(msg) - sizeof(long), 0, 0) >= 0) {
            if (msg.pressed == 1) {
                printf("Pressed Key Code: %d\n", msg.keyInput);
            }
        }
    }

    buttonExit();
    return 0;
}
