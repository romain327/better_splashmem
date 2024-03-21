#ifndef __FIFOBOMBS__
#define __FIFOBOMBS__
#include <stdlib.h>
#include <stdint.h>
#include "world.h"

typedef struct s_bomb
{
    uint32_t ID_players;
    uint32_t X_bomb;
    uint32_t y_bomb;
    uint8_t bombState; //0 =en attente 1=explose
    
} t_bomb;


typedef struct Element Element;
struct Element
{
    uint16_t counter;
    t_bomb bombInfo;
    Element *next;
};

typedef struct fifo_bomb fifo_bomb;
struct fifo_bomb
{
    Element *first;
};
extern fifo_bomb *buffer_bomb;

/*fonction definition*/
void add_fifo_bomb_elements(fifo_bomb *fifo_bomb, uint16_t counter_value, uint32_t xpos_bomb, uint32_t ypos_bomb ,uint32_t IDplayers);
t_bomb Check_bomb_time_out(fifo_bomb *fifo_bomb);
void decrement_counter(fifo_bomb *fifo_bomb);
/***********************/

#endif
