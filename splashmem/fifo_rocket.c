#include "./Include/fifo_rocket.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


void add_fifo_rocket_elements(fifo_rocket *fifo_rocket, uint16_t counter_value, uint32_t xpos_rocket, uint32_t ypos_rocket, uint32_t IDplayers, int32_t Credits)
{
    Element_r *new_r = malloc(sizeof(*new_r));
    
    if (fifo_rocket == NULL || new_r == NULL)
    {
        printf("Err: pointeur NULL dans la fonction add_fifo_rocket dans fifo_rocket.c\n");
        exit(EXIT_FAILURE);
    }
    int Al = ((Credits % 7) * (Credits % 11) * (Credits % 13)) % 4;
    new_r->counter_r = counter_value;
    new_r->rocketInfo.ID_players_r=IDplayers;
    if (xpos_rocket < 1)
    {
        xpos_rocket =1;
    }
    new_r->rocketInfo.X_rocket=xpos_rocket;
    if (ypos_rocket < 1)
    {
        ypos_rocket =1;
    }
    new_r->rocketInfo.y_rocket=ypos_rocket;
    new_r->rocketInfo.Direction = Al;
    new_r->rocketInfo.rocketState=0;
    new_r->rocketInfo.Pres = 1;
    new_r->next_r = NULL;
    
    if (fifo_rocket->first_r != NULL) /* La file n'est pas vide */
    {   
        /* On se positionne à la fin de la file */
        Element_r *elementPosition = fifo_rocket->first_r;
        while (elementPosition->next_r != NULL)
        {
            
            elementPosition = elementPosition->next_r;
        }
        elementPosition->next_r= new_r;
    }
    else /* La file est vide, notre élément est le premier */
    {
       fifo_rocket->first_r = new_r;
    }
}

//return RocketInfo and delete associated element if the counter value=0 
t_rocket Check_rocket_time_out(fifo_rocket *fifo_rocket)
{
    if (fifo_rocket == NULL)
    {
        printf("Err: pointeur fifo NULL dans la fonction Check_rocket_time_out(fifo_brocket *fifo_rocket) dans fifo_rocket.c\n");
        exit(EXIT_FAILURE);
    }
    t_rocket info;
    info.ID_players_r=0;
    info.X_rocket=0;
    info.y_rocket=0;
    info.rocketState=0;
    
    /* On vérifie s'il y a quelque chose à défiler */
    if (fifo_rocket->first_r != NULL)
    {
        Element_r *element = fifo_rocket->first_r;
        if (element->counter_r==0)
        {
            info = element->rocketInfo;
            fifo_rocket->first_r = element->next_r;
            free(element);
            info.rocketState=1;
        }
    }
    return info;
}

void decrement_counter_r(fifo_rocket *fifo_rocket)
{
    if (fifo_rocket->first_r != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Element_r *elementPosition = fifo_rocket->first_r;
        uint32_t pos;
        if (elementPosition->next_r != NULL)
        {
            while (elementPosition->next_r != NULL)
            {
                elementPosition->counter_r--;
                
                if (elementPosition->counter_r != ROCKET_COUNTER)
                {
                if (elementPosition->rocketInfo.Pres == 0)
                {
                    pos = elementPosition->rocketInfo.y_rocket * MAP_SIZE + elementPosition->rocketInfo.X_rocket;
                    mapmem[pos] = 0;
                }
                }
                if (elementPosition->rocketInfo.Direction == 1)
                {
                    if (elementPosition->rocketInfo.y_rocket==99)
                    {
                        elementPosition->rocketInfo.y_rocket = 1;
                    }
                    else
                    {
                        elementPosition->rocketInfo.y_rocket++;
                    } 
                }
                else if (elementPosition->rocketInfo.Direction == 1)
                {
                    if (elementPosition->rocketInfo.X_rocket==99)
                    {
                        elementPosition->rocketInfo.X_rocket = 1;
                    }
                    else
                    {
                        elementPosition->rocketInfo.X_rocket++;
                    }
                }
                else if (elementPosition->rocketInfo.Direction == 2)
                {
                    if (elementPosition->rocketInfo.y_rocket==1)
                    {
                        elementPosition->rocketInfo.y_rocket = 99;
                    }
                    else
                    {
                        elementPosition->rocketInfo.y_rocket--;
                    }
                }
                else
                {
                    if (elementPosition->rocketInfo.X_rocket == 1)
                    {
                        elementPosition->rocketInfo.X_rocket = 99;
                    }
                    else
                    {
                    elementPosition->rocketInfo.X_rocket--;
                    }
                }
                pos = elementPosition->rocketInfo.y_rocket * MAP_SIZE + elementPosition->rocketInfo.X_rocket;
                if (mapmem[pos] == elementPosition->rocketInfo.ID_players_r)
                {
                    elementPosition->rocketInfo.Pres = 1;
                }
                else
                {
                    mapmem[pos] = elementPosition->rocketInfo.ID_players_r;
                    elementPosition->rocketInfo.Pres = 0;
                }
                elementPosition = elementPosition->next_r;
            }
            
        }
        else
        {
            elementPosition->counter_r--;
            //printf("counter:%u\n",elementPosition->counter);
        }
    }
}