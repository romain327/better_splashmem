#include "./Include/world.h"
#include "./Include/actions.h"
#include "./Include/fifo_bomb.h"
#include <stdio.h>
#include "./Include/param.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "./Include/splash.h"
#include "./Include/fifo_rocket.h"

// world_paint_spot(uint32_t x, uint32_t y, uint32_t num)

int PwrUP_TOURBILOL_Time = 0;

void actions_do(t_player *p_player, enum action act_id)
{
    // printf("Action_id=%d\n",act_id);
    switch (act_id)
    {
    case ACTION_STILL:
        if (p_player->credits >= STILL_COST)
        {
            STILL(p_player);
        }
        break;

    case ACTION_MOVE_L:
        if (p_player->credits >= MOVE_COST)
        {
            MOVE_L(p_player);
        }
        break;

    case ACTION_MOVE_R:
        if (p_player->credits >= MOVE_COST)
        {
            MOVE_R(p_player);
        }
        break;

    case ACTION_MOVE_U:
        if (p_player->credits >= MOVE_COST)
        {
            MOVE_U(p_player);
        }
        break;

    case ACTION_MOVE_D:
        if (p_player->credits >= MOVE_COST)
        {
            MOVE_D(p_player);
        }
        break;
    case ACTION_DASH_L:
        if (p_player->credits >= DASH_COST)
        {
            DASH_L(p_player);
        }
        break;

    case ACTION_DASH_R:
        if (p_player->credits >= DASH_COST)
        {
            DASH_R(p_player);
        }
        break;

    case ACTION_DASH_U:
        if (p_player->credits >= DASH_COST)
        {
            DASH_U(p_player);
        }
        break;

    case ACTION_DASH_D:
        if (p_player->credits >= DASH_COST)
        {
            DASH_D(p_player);
        }
        break;

    case ACTION_TELEPORT_L:
        if (p_player->credits >= TELEPORT_COST)
        {
            TELEPORT_L(p_player);
        }
        break;

    case ACTION_TELEPORT_R:
        if (p_player->credits >= TELEPORT_COST)
        {
            TELEPORT_R(p_player);
        }
        break;

    case ACTION_TELEPORT_U:
        if (p_player->credits >= TELEPORT_COST)
        {
            TELEPORT_U(p_player);
        }
        break;

    case ACTION_TELEPORT_D:
        if (p_player->credits >= TELEPORT_COST)
        {
            TELEPORT_D(p_player);
        }
        break;

    case ACTION_SPLASH:
        if (p_player->credits >= SPLASH_COST)
        {
            Splash(p_player->x, p_player->y, p_player->id, SPLASH_ZONE);
            p_player->credits = p_player->credits - SPLASH_COST;
        }
        break;

    case ACTION_BOMB:
        if (p_player->credits >= BOMB_COST)
        {
            add_fifo_bomb_elements(buffer_bomb, BOMB_COUNTER, p_player->x, p_player->y, p_player->id);
            p_player->credits = p_player->credits - BOMB_COST;
        }
        break;
    
    case ACTION_ROCKET:
        if (p_player->credits >= ROCKET_COST)
        {
            add_fifo_rocket_elements(buffer_rocket, ROCKET_COUNTER, p_player->x, p_player->y, p_player->id, p_player->credits);
            p_player->credits = p_player->credits - ROCKET_COST;
        }
        break;

    case ACTION_PwrUP_TOURBILOL:

        p_player->PwrUP_id = PwrUP_TOURBILOL;

        break;

    case ACTION_PwrUP_NoPwrUp:

        p_player->PwrUP_id = PwrUP_NoPwrUp;

        break;

    default:
        printf("Err: No action corresponding");
        break;
    }

    PwrUP_do(p_player);
}

void PwrUP_do(t_player *p_player)
{

    switch (p_player->PwrUP_id)
    {
    case PwrUP_TOURBILOL:

        PwrUP_TOURBILOL_Time++;

        if(PwrUP_TOURBILOL_Time == 6)
        {
            PwrUP_TOURBILOL_Time = 0;
        }

        if( (((p_player->x)+2)<96) && (((p_player->y)+2<96)) && (((p_player->x))> 4) && (((p_player->y))> 4) )
        {

            switch (PwrUP_TOURBILOL_Time)
            {
            case 0:

            world_paint_spot((p_player->x)+3, (p_player->y)+3, p_player->id);
            world_paint_spot((p_player->x)+3, (p_player->y)-3, p_player->id);
            world_paint_spot((p_player->x)-3, (p_player->y)-3, p_player->id);
            world_paint_spot((p_player->x)-3, (p_player->y)+3, p_player->id);

            break;

            case 1:

            world_paint_spot((p_player->x)+4, (p_player->y)+2, p_player->id);
            world_paint_spot((p_player->x)+2, (p_player->y)-4, p_player->id);
            world_paint_spot((p_player->x)-4, (p_player->y)-2, p_player->id);
            world_paint_spot((p_player->x)-2, (p_player->y)+4, p_player->id);

            break;

            case 2:

            world_paint_spot((p_player->x)+5, (p_player->y)+1, p_player->id);
            world_paint_spot((p_player->x)+1, (p_player->y)-5, p_player->id);
            world_paint_spot((p_player->x)-5, (p_player->y)-1, p_player->id);
            world_paint_spot((p_player->x)-1, (p_player->y)+5, p_player->id);

            break;

            case 3:

            world_paint_spot((p_player->x)+5, (p_player->y), p_player->id);
            world_paint_spot((p_player->x), (p_player->y)-5, p_player->id);
            world_paint_spot((p_player->x)-5, (p_player->y), p_player->id);
            world_paint_spot((p_player->x), (p_player->y)+5, p_player->id);

            break;

            case 4:

            world_paint_spot((p_player->x)+5, (p_player->y)-1, p_player->id);
            world_paint_spot((p_player->x)-1, (p_player->y)-5, p_player->id);
            world_paint_spot((p_player->x)-5, (p_player->y)+1, p_player->id);
            world_paint_spot((p_player->x)+1, (p_player->y)+5, p_player->id);

            break;

            case 5:

            world_paint_spot((p_player->x)+4, (p_player->y)-2, p_player->id);
            world_paint_spot((p_player->x)-2, (p_player->y)-4, p_player->id);
            world_paint_spot((p_player->x)-4, (p_player->y)+2, p_player->id);
            world_paint_spot((p_player->x)+2, (p_player->y)+4, p_player->id);

            break;

            default:
            break;
            }

        }

        p_player->credits = p_player->credits - TOURBILOL_COST;

    break;

    default:
    break;
    }
}



void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
const int32_t diameter = (radius * 2);

int32_t x = (radius - 1);
int32_t y = 0;
int32_t tx = 1;
int32_t ty = 1;
int32_t error = (tx - diameter);

while (x >= y)
{
// Each of the following renders an octant of the circle
SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

    if (error <= 0)
    {
    ++y;
    error += ty;
    ty += 2;
    }

    if (error > 0)
    {
    --x;
    tx += 2;
    error += (tx - diameter);
    }

}
}


void actions_init()
{
}

void Splash(uint32_t xpos, uint32_t ypos, uint32_t plID, uint32_t splashSize)
{
    uint32_t x = xpos - (splashSize / 2);
    uint32_t y;
    if (x > 10000)
    {
        x = MAP_SIZE - 1;
    }

    for (uint8_t i = 0; i < splashSize; i++)
    {
        y = ypos - (splashSize / 2);
        if (y > 10000)
        {
            y = MAP_SIZE - 1;
        }
        for (uint8_t j = 0; j < splashSize; j++)
        {

            // printf("Paint_spot x:%u , y:%u\n",x,y);
            world_paint_spot(x, y, plID);
            y++;
            if (y > MAP_SIZE - 1)
            {
                y = 0;
            }
        }
        x++;
        if (x > MAP_SIZE - 1)
        {
            x = 0;
        }
    }
}

void STILL(t_player *p_player){
    p_player->credits = p_player->credits - STILL_COST;
    world_paint_spot(p_player->x, p_player->y, p_player->id);
}
void MOVE_L(t_player *p_player){
    p_player->x--;
    if (p_player->x > 10000)
    {
        p_player->x = MAP_SIZE - 1;
    }
    p_player->credits = p_player->credits - MOVE_COST;
    world_paint_spot(p_player->x, p_player->y, p_player->id);
}
void MOVE_R(t_player *p_player){
    p_player->x++;
    if (p_player->x > MAP_SIZE - 1)
    {
        p_player->x = 0;
    }
    p_player->credits = p_player->credits - MOVE_COST;
    world_paint_spot(p_player->x, p_player->y, p_player->id);
}
void MOVE_U(t_player *p_player){
    p_player->y--;
    if (p_player->y > 10000)
    {
        p_player->y = MAP_SIZE - 1;
    }
    p_player->credits = p_player->credits - MOVE_COST;
    world_paint_spot(p_player->x, p_player->y, p_player->id);
}
void MOVE_D(t_player *p_player){
    p_player->y++;
    if (p_player->y > MAP_SIZE - 1)
    {
        p_player->y = 0;
    }
    p_player->credits = p_player->credits - MOVE_COST;
    world_paint_spot(p_player->x, p_player->y, p_player->id);
}
void DASH_L(t_player *p_player){
    for (uint8_t i = 0; i < DASH_LENGTH; i++)
    {
        p_player->x--;
        if (p_player->x > 10000)
        {
            p_player->x = MAP_SIZE - 1;
        }
        world_paint_spot(p_player->x, p_player->y, p_player->id);
    }
    p_player->credits = p_player->credits - DASH_COST;
}
void DASH_R(t_player *p_player){
    for (uint8_t i = 0; i < DASH_LENGTH; i++)
    {
        p_player->x++;
        if (p_player->x > MAP_SIZE - 1)
        {
            p_player->x = 0;
        }
        world_paint_spot(p_player->x, p_player->y, p_player->id);
    }
    p_player->credits = p_player->credits - DASH_COST;
}
void DASH_U(t_player *p_player){
    for (uint8_t i = 0; i < DASH_LENGTH; i++)
    {
        p_player->y--;
        if (p_player->y > 10000)
        {
            p_player->y = MAP_SIZE - 1;
        }
        world_paint_spot(p_player->x, p_player->y, p_player->id);
    }
    p_player->credits = p_player->credits - DASH_COST;
}
void DASH_D(t_player *p_player){
    for (uint8_t i = 0; i < DASH_LENGTH; i++)
    {
        p_player->y++;
        if (p_player->y > MAP_SIZE - 1)
        {
            p_player->y = 0;
        }
        world_paint_spot(p_player->x, p_player->y, p_player->id);
    }
    p_player->credits = p_player->credits - DASH_COST;
}
void TELEPORT_L(t_player *p_player){
    for (uint8_t i = 0; i < TELEPORT_LENGTH; i++)
    {
        p_player->x--;
        if (p_player->x > 10000)
        {
            p_player->x = MAP_SIZE - 1;
        }
    }
    world_paint_spot(p_player->x, p_player->y, p_player->id);
    p_player->credits = p_player->credits - TELEPORT_COST;
}
void TELEPORT_R(t_player *p_player){
    for (uint8_t i = 0; i < TELEPORT_LENGTH; i++)
    {
        p_player->x++;
        if (p_player->x > MAP_SIZE - 1)
        {
            p_player->x = 0;
        }
    }
    world_paint_spot(p_player->x, p_player->y, p_player->id);
    p_player->credits = p_player->credits - TELEPORT_COST;
}
void TELEPORT_U(t_player *p_player){
    for (uint8_t i = 0; i < TELEPORT_LENGTH; i++)
    {
        p_player->y--;
        if (p_player->y > 10000)
        {
            p_player->y = MAP_SIZE - 1;
        }
    }
    world_paint_spot(p_player->x, p_player->y, p_player->id);
    p_player->credits = p_player->credits - TELEPORT_COST;
}
void TELEPORT_D(t_player *p_player){
    for (uint8_t i = 0; i < TELEPORT_LENGTH; i++)
    {
        p_player->y++;
        if (p_player->y > MAP_SIZE - 1)
        {
            p_player->y = 0;
        }
    }
    world_paint_spot(p_player->x, p_player->y, p_player->id);
    p_player->credits = p_player->credits - TELEPORT_COST;
}
// void SPLASH(t_player *p_player);
// void BOMB(t_player *p_player);
// void ROCKET(t_player *p_player);
// void GRAB(t_player *p_player);
// void STUN(t_player *p_player);er *p_player);
// void BOMB(t_player *p_player);
// void ROCKET(t_player *p_player);
// void GRAB(t_player *p_player);
// void STUN(t_player *p_player);