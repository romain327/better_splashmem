#ifndef __PLAYER__
#define __PLAYER__

#include <stdlib.h>
#include <stdint.h>

typedef void* (*fptr)();

enum PwrUp
{
    PwrUP_NoPwrUp,
    PwrUP_TOURBILOL
};

typedef struct s_player
{
    /* data */
    uint32_t id;
    uint32_t color;
    uint8_t* data;
    uint32_t x;
    uint32_t y;
    enum PwrUp PwrUP_id;
    int32_t credits;
    uint32_t score;
    fptr get_Action;
} t_player;

void player_init(t_player *p_player, uint8_t num, void *handle, u_int32_t nb_player);


#endif