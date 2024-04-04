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
t_player *players[MAX_PLAYERS] = {0};

fifo_bomb *buffer_bomb;
fifo_rocket * buffer_rocket;

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_players(char *argv[])
{
    int i = 0;
    void *handle[MAX_PLAYERS];

    for (i = 0; i < MAX_PLAYERS; i++)
    {

        handle[i] = dlopen(argv[i + 1], RTLD_NOW);
        players[i] = (t_player *)malloc(sizeof(t_player));
        player_init(players[i], i, handle[i]);
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
    for (uint32_t i = 0; i < MAP_SIZE * MAP_SIZE; i++)
    {

        switch (mapmem[i])
        {
        case 1:
            players[0]->count++;
            break;
        case 2:
            players[1]->count++;
            break;
        case 3:
            players[2]->count++;
            break;
        case 4:
            players[3]->count++;
            break;

        default:
            break;
        }
    }
    uint32_t resultat[MAX_PLAYERS][2] = {{players[0]->id, players[0]->count}, {players[1]->id, players[1]->count}, {players[2]->id, players[2]->count}, {players[3]->id, players[3]->count}};
    printf("p1:%u  p2:%u   p3:%u   p4:%u\n", players[0]->count, players[1]->count, players[2]->count, players[3]->count);

    int i, j;
    uint32_t c[2] = {0, 0};
    for (i = 0; i < MAX_PLAYERS - 1; i++)
    {
        for (j = i + 1; j < MAX_PLAYERS; j++)
        {
            if (resultat[i][1] > resultat[j][1])
            {
                c[0] = resultat[i][0];
                c[1] = resultat[i][1];
                resultat[i][0] = resultat[j][0];
                resultat[i][1] = resultat[j][1];
                resultat[j][0] = c[0];
                resultat[j][1] = c[1];
            }
        }
    }
    printf("*********CLASSEMENT*********\n");
    printf("   1e: p%u  score: %u\n",resultat[3][0],resultat[3][1]);
    printf("   2e: p%u  score: %u\n",resultat[2][0],resultat[2][1]);
    printf("   3e: p%u  score: %u\n",resultat[1][0],resultat[1][1]);
    printf("   4e: p%u  score: %u\n",resultat[0][0],resultat[0][1]);
       
    
    
}
