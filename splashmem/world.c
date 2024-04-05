#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "./Include/world.h"
#include "./Include/param.h"
#include "./Include/player.h"
#include "./Include/actions.h"
#include "./Include/fifo_bomb.h"
#include "./Include/fifo_rocket.h"

/* !!!!!!!!!!!!!!!! MAP !!!!!!!!!!!!!!!!!!!!! */
uint8_t mapmem[MAP_SIZE * MAP_SIZE] = {0};

/*  PLAYERS */
uint8_t NB_PLAYER;

t_player *players[8] = {0};

fifo_bomb *buffer_bomb;
fifo_rocket * buffer_rocket;

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_players(char *argv[])
{
    int i = 0;
    void *handle[NB_PLAYER];

    for (i = 0; i < NB_PLAYER; i++)
    {

        handle[i] = dlopen(argv[i + 1], RTLD_NOW);
        players[i] = (t_player *)malloc(sizeof(t_player));
        player_init(players[i], i, handle[i], NB_PLAYER);
        world_paint_spot(players[i]->x, players[i]->y, players[i]->id);
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_do_player_action(t_player *p_player)
{
    // ici du code a qui fonctionne
    t_bomb bombInfo;
    t_rocket rocketInfo;
    actions_do(p_player, (enum action)p_player->get_Action());
    bombInfo = Check_bomb_time_out(buffer_bomb);
    rocketInfo = Check_rocket_time_out(buffer_rocket);
    // printf("Bomb info:\nbombState:%u\nID_players:%u\nX_bomb:%u\nY_bomb:%u\n\n",bombInfo.bombState,bombInfo.ID_players,bombInfo.X_bomb,bombInfo.y_bomb);
    if (bombInfo.bombState == 1)
    {
        Splash(bombInfo.X_bomb, bombInfo.y_bomb, bombInfo.ID_players, BOMB_ZONE);
    }
    if (rocketInfo.rocketState == 1)
    {
        Splash(rocketInfo.X_rocket, rocketInfo.y_rocket, rocketInfo.ID_players_r, BOMB_ZONE);
    }

    // printf("pl_id:%d x:%u , y:%u\n",i,players[0]->x,players[0]->y);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_paint_spot(uint32_t x, uint32_t y, uint32_t num)
{
    uint32_t pos = y * MAP_SIZE + x;
    mapmem[pos] = num;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_get_winner()
{
    for (int id = 0; id < NB_PLAYER; id++)
    {
        players[id]->score = 0;
        for (int j = 0; j < MAP_SIZE * MAP_SIZE; j++)
        {
            if (mapmem[j] == id){
                players[id]->score++;
            }
        }
    }
}

u_int64_t world_get_map(t_player *p_player)
{
    u_int64_t map[25][25];
    u_int32_t compteur_i = 0;
    u_int32_t compteur_j = 0;
    for (int i = (p_player->x)-12; i<(p_player->x)+12; i++)
    {
        if (i<0){i+=MAP_SIZE;}
        if (i>MAP_SIZE){i-=MAP_SIZE;}
        compteur_i++;
        for (int j = (p_player->y)-12; j<(p_player->y)+12; j++)
        {
            compteur_j++;
            if (j<0){j+=MAP_SIZE;}
            if (j>MAP_SIZE){j-=MAP_SIZE;}
            map[compteur_i][compteur_j]=mapmem[i*MAP_SIZE+j];
        }
    }
    return map;
}
