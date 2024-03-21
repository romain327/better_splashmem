#include "./Include/world.h"
#include "./Include/actions.h"
#include "./Include/fifo_bomb.h"
#include <stdio.h>
#include "./Include/param.h"

// world_paint_spot(uint32_t x, uint32_t y, uint32_t num)

void actions_do(t_player *p_player, enum action act_id)
{
    // printf("Action_id=%d\n",act_id);
    switch (act_id)
    {
    case ACTION_STILL:
        if (p_player->credits >= STILL_COST)
        {
            p_player->credits = p_player->credits - STILL_COST;
        }
        break;

    case ACTION_MOVE_L:
        if (p_player->credits >= MOVE_COST)
        {
            p_player->x--;
            if (p_player->x > 10000)
            {
                p_player->x = MAP_SIZE - 1;
            }
            p_player->credits = p_player->credits - MOVE_COST;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;

    case ACTION_MOVE_R:
        if (p_player->credits >= MOVE_COST)
        {
            p_player->x++;
            if (p_player->x > MAP_SIZE - 1)
            {
                p_player->x = 0;
            }
            p_player->credits = p_player->credits - MOVE_COST;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;

    case ACTION_MOVE_U:
        if (p_player->credits >= MOVE_COST)
        {
            p_player->y--;
            if (p_player->y > 10000)
            {
                p_player->y = MAP_SIZE - 1;
            }
            p_player->credits = p_player->credits - MOVE_COST;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;

    case ACTION_MOVE_D:
        if (p_player->credits >= MOVE_COST)
        {
            p_player->y++;
            if (p_player->y > MAP_SIZE - 1)
            {
                p_player->y = 0;
            }
            p_player->credits = p_player->credits - MOVE_COST;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_DASH_L:
        if (p_player->credits >= DASH_COST)
        {
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
        break;

    case ACTION_DASH_R:
        if (p_player->credits >= DASH_COST)
        {
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
        break;

    case ACTION_DASH_U:
        if (p_player->credits >= DASH_COST)
        {
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
        break;

    case ACTION_DASH_D:
        if (p_player->credits >= DASH_COST)
        {
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
        break;

    case ACTION_TELEPORT_L:
        if (p_player->credits >= TELEPORT_COST)
        {
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
        break;

    case ACTION_TELEPORT_R:
        if (p_player->credits >= TELEPORT_COST)
        {
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
        break;

    case ACTION_TELEPORT_U:
        if (p_player->credits >= TELEPORT_COST)
        {
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
        break;

    case ACTION_TELEPORT_D:
        if (p_player->credits >= TELEPORT_COST)
        {
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

    default:
        printf("Err: No action corresponding");
        break;
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