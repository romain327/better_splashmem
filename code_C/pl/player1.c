#include "./Include/actions.h"
#include <stdio.h>
#define MAX_PLAY_ACTION 11

char play_actions[] = {
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_DASH_R,
    ACTION_MOVE_D,
    /*/ ACTION_MOVE_L,
    // ACTION_MOVE_R,
    // ACTION_MOVE_U,
    // ACTION_MOVE_D,
    // ACTION_DASH_L,
     ACTION_DASH_R,
    // ACTION_DASH_U,
     ACTION_DASH_D,
    // ACTION_TELEPORT_L,
    // ACTION_TELEPORT_R,
    // ACTION_TELEPORT_U,
    // ACTION_TELEPORT_D,
    // ACTION_SPLASH,
    // ACTION_BOMB,
    // ACTION_NUMBER
    ACTION_TELEPORT_D,
    ACTION_BOMB,
    ACTION_TELEPORT_R,
    // ACTION_BOMB,
    ACTION_MOVE_R,
    ACTION_MOVE_R,
    ACTION_MOVE_R,
    ACTION_BOMB,
    ACTION_MOVE_R,*/
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