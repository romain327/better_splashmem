#ifndef __FIFOROCKETS__
#define __FIFOROCKETS__
#include <stdlib.h>
#include <stdint.h>
#include "world.h"


typedef struct s_rocket
{
    uint32_t ID_players_r;
    uint32_t X_rocket;
    uint32_t y_rocket;
    uint8_t Direction; // 0 = up / 1 = right / 2 = down / 3 = left
    uint8_t Pres; //Presence of player's color on the way (if yes does not delete the color on it way)
    uint8_t rocketState; //0 =en attente 1=explose
} t_rocket;


typedef struct Element_r Element_r;
struct Element_r
{
    uint16_t counter_r;
    t_rocket rocketInfo;
    Element_r *next_r;
};

typedef struct fifo_rocket fifo_rocket;
struct fifo_rocket
{
    Element_r *first_r;
};
extern fifo_rocket *buffer_rocket;

/*fonction definition*/
void add_fifo_rocket_elements(fifo_rocket *fifo_rocket, uint16_t counter_value, uint32_t xpos_rocket, uint32_t ypos_rocket ,uint32_t IDplayers,int32_t Creedits);
t_rocket Check_rocket_time_out(fifo_rocket *fifo_rocket);
void decrement_counter_r(fifo_rocket *fifo_rocket);
/***********************/

#endif 