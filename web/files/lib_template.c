#include "actions.h"
#include <stdio.h>
#define MAX_PLAY_ACTION N // Changer N par le nombre total de mouvements du tableau play_actions[]

char play_actions[] = {
	// Remplir ici les mouvements
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