#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <dlfcn.h>

#include "./Include/param.h"
#include "./Include/world.h"
#include "./Include/actions.h"
#include "./Include/splash.h"
#include "./Include/fifo_bomb.h"
#include "./Include/fifo_rocket.h"

uint32_t colors[MAX_PLAYERS + 1] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void init_colors(SDL_PixelFormat *format)
{
    colors[0] = SDL_MapRGB(format, 0x00, 0x00, 0x00);
    colors[1] = SDL_MapRGB(format, 0xFF, 0, 0);
    colors[2] = SDL_MapRGB(format, 0, 0xFF, 0);
    colors[3] = SDL_MapRGB(format, 0, 0x0, 0xFF);
    colors[4] = SDL_MapRGB(format, 0xFF, 0, 0xFF);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void inits(int argc, char *argv[])
{

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);
    SDL_PixelFormat *format = screenSurface->format;
    init_colors(format);
    actions_init();
    world_create_players(argv);
    buffer_bomb = (fifo_bomb *)malloc(sizeof(fifo_bomb));
    buffer_bomb->first = NULL;
    buffer_rocket = (fifo_rocket *)malloc(sizeof(fifo_rocket));
    buffer_rocket->first_r = NULL;

    printf("inits done\n");
}