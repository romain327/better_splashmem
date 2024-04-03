#ifndef __ACTIONS__
#define __ACTIONS__

#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

enum action
{
    ACTION_STILL,
    ACTION_MOVE_L,
    ACTION_MOVE_R,
    ACTION_MOVE_U,
    ACTION_MOVE_D,
    ACTION_DASH_L,
    ACTION_DASH_R,
    ACTION_DASH_U,
    ACTION_DASH_D,
    ACTION_TELEPORT_L,
    ACTION_TELEPORT_R,
    ACTION_TELEPORT_U,
    ACTION_TELEPORT_D,
    ACTION_SPLASH,
    ACTION_BOMB,
    ACTION_NUMBER,
    ACTION_PwrUP_TOURBILOL,
    ACTION_PwrUP_NoPwrUp
};

void STILL(t_player *p_player);
void MOVE_L(t_player *p_player);
void MOVE_R(t_player *p_player);
void MOVE_U(t_player *p_player);
void MOVE_D(t_player *p_player);
void DASH_L(t_player *p_player);
void DASH_R(t_player *p_player);
void DASH_U(t_player *p_player);
void DASH_D(t_player *p_player);
void TELEPORT_L(t_player *p_player);
void TELEPORT_R(t_player *p_player);
void TELEPORT_U(t_player *p_player);
void TELEPORT_D(t_player *p_player);
void SPLASH(t_player *p_player);
void BOMB(t_player *p_player);
void ROCKET(t_player *p_player);
void GRAB(t_player *p_player);
void STUN(t_player *p_player);

void PwrUP_do(t_player *p_player);

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

void actions_do(t_player *p_player, enum action act_id);
void actions_init();
void Splash(uint32_t xpos, uint32_t ypos, uint32_t plID,uint32_t splashSize);
#endif
