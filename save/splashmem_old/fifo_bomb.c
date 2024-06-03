#include "./Include/fifo_bomb.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



void add_fifo_bomb_elements(fifo_bomb *fifo_bomb, uint16_t counter_value, uint32_t xpos_bomb, uint32_t ypos_bomb, uint32_t IDplayers)
{
    Element *new = malloc(sizeof(*new));
    if (fifo_bomb == NULL || new == NULL)
    {
        printf("Err: pointeur NULL dans la fonction add_fifo_bomb dans fifo_bomb.c\n");
        exit(EXIT_FAILURE);
    }
    
    new->counter = counter_value;
    new->bombInfo.ID_players=IDplayers;
    new->bombInfo.X_bomb=xpos_bomb;
    new->bombInfo.y_bomb=ypos_bomb;
    new->bombInfo.bombState=0;
    new->next = NULL;
    
    if (fifo_bomb->first != NULL) /* La file n'est pas vide */
    {   
        /* On se positionne à la fin de la file */
        Element *elementPosition = fifo_bomb->first;
        while (elementPosition->next != NULL)
        {
            
            elementPosition = elementPosition->next;
        }
        elementPosition->next = new;
    }
    else /* La file est vide, notre élément est le premier */
    {
       fifo_bomb->first = new;
    }
}

//return BombInfo and delete associated element if the counter value=0 
t_bomb Check_bomb_time_out(fifo_bomb *fifo_bomb)
{
    if (fifo_bomb == NULL)
    {
        printf("Err: pointeur fifo NULL dans la fonction Check_bomb_time_out(fifo_bomb *fifo_bomb) dans fifo_bomb.c\n");
        exit(EXIT_FAILURE);
    }

    t_bomb info;
    info.ID_players=0;
    info.X_bomb=0;
    info.y_bomb=0;
    info.bombState=0;

    /* On vérifie s'il y a quelque chose à défiler */
    if (fifo_bomb->first != NULL)
    {
        Element *element = fifo_bomb->first;
        if (element->counter==0)
        {
            info = element->bombInfo;
            fifo_bomb->first = element->next;
            free(element);
            info.bombState=1;
        }
    }
    return info;
}

void decrement_counter(fifo_bomb *fifo_bomb)
{
    if (fifo_bomb->first != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Element *elementPosition = fifo_bomb->first;
        if (elementPosition->next != NULL)
        {
            while (elementPosition->next != NULL)
            {
                elementPosition->counter--;
                //printf("counter:%u\n",elementPosition->counter);
                elementPosition = elementPosition->next;
            }
            
        }
        else
        {
            elementPosition->counter--;
            //printf("counter:%u\n",elementPosition->counter);
        }
        

        
    }

}