#include "./Include/actions.h"
#include <stdio.h>
#define MAX_PLAY_ACTION 14

char play_actions[] = {
    ACTION_DASH_L,
    ACTION_BOMB,
    ACTION_TELEPORT_D,
    ACTION_SPLASH,
    ACTION_DASH_R,
    ACTION_BOMB,
    ACTION_STILL,
    ACTION_STILL,
    ACTION_STILL,
    ACTION_STILL,
    ACTION_STILL,
    ACTION_DASH_L,
    ACTION_BOMB,
    ACTION_TELEPORT_D
};

char get_action()
{
    static int i = 0;
    char ret_val = 0;

    ret_val = play_actions[i];
    i++;
    if (i >= MAX_PLAY_ACTION)
    {
        i = 0;
    }
    return (ret_val);
}