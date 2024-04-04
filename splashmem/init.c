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

uint32_t colors[9] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void init_colors(SDL_PixelFormat *format)
{
    colors[0] = SDL_MapRGB(format, 0x00, 0x00, 0x00);   // Noir
    colors[1] = SDL_MapRGB(format, 0xFF, 0x00, 0x00);   // Rouge
    colors[2] = SDL_MapRGB(format, 0x00, 0xFF, 0x00);   // Vert
    colors[3] = SDL_MapRGB(format, 0x00, 0x00, 0xFF);   // Bleu
    colors[4] = SDL_MapRGB(format, 0xFF, 0x00, 0xFF);   // Magenta
    colors[5] = SDL_MapRGB(format, 0xFF, 0xFF, 0x00);   // Jaune
    colors[6] = SDL_MapRGB(format, 0x00, 0xFF, 0xFF);   // Cyan
    colors[7] = SDL_MapRGB(format, 0x80, 0x80, 0x80);   // Gris
    colors[8] = SDL_MapRGB(format, 0xFF, 0xFF, 0xFF);   // Blanc
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

    printf("inits done\n");
}