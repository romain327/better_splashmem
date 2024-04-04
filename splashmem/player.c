#include <stdlib.h>
#include <SDL2/SDL.h>
#include <dlfcn.h>
#include "./Include/player.h"
#include "./Include/param.h"

u_int32_t pos_player_x[][8]=
{
    {MAP_SIZE / 2},
    {MAP_SIZE / 4, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE * 3 / 4, MAP_SIZE / 2},
    {MAP_SIZE / 4, MAP_SIZE * 3 / 4, MAP_SIZE / 4, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE * 3 / 4, MAP_SIZE / 2, MAP_SIZE / 4, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4, MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4, MAP_SIZE / 2, MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4, MAP_SIZE / 4, MAP_SIZE * 3 / 4, MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4}
};

u_int32_t pos_player_y[][8]=
{
    {MAP_SIZE / 2},
    {MAP_SIZE / 2, MAP_SIZE / 2},
    {MAP_SIZE / 4,MAP_SIZE / 4, MAP_SIZE / 4 * 3},
    {MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4},
    {MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE / 4, MAP_SIZE / 2, MAP_SIZE / 2, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4, MAP_SIZE * 3 / 4},
};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void player_init(t_player *p_player, uint8_t num, void *handle, u_int32_t nb_player)
{
    p_player->id = num + 1;
    p_player->color = 0;
    p_player->x = pos_player_x[nb_player-1][num];
    p_player->y = pos_player_y[nb_player-1][num];
    p_player->credits = P_CREDITS;
    p_player->count = 0;
    p_player->get_Action = dlsym(handle, "get_action");
}
