#include "handler.h"

void handle(SDL_Event *e, SDL_Renderer *renderer, SDL_Window *window, uint8_t *finishing) {
    if(e->type == SDL_KEYDOWN) {
        switch(e->key.keysym.sym) {
            case SDLK_q:
                quit(renderer, window);
                *finishing = 0;
                break;
            case SDLK_ESCAPE:
                quit(renderer, window);
                *finishing = 0;
                break;
            default:
                break;
        }
    }
}

void quit(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Semaphore functions
void wait_semaphore(int semid) {
    struct sembuf sem_op;
    sem_op.sem_num = 0; // Indice du sémaphore dans l'ensemble
    sem_op.sem_op = -1; // Opération P (wait)
    sem_op.sem_flg = 0; // Options
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop wait failed");
        exit(EXIT_FAILURE);
    }
}

void signal_semaphore(int semid) {
    struct sembuf sem_op;
    sem_op.sem_num = 0; // Indice du sémaphore dans l'ensemble
    sem_op.sem_op = 1; // Opération V (signal)
    sem_op.sem_flg = 0; // Options
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop signal failed");
        exit(EXIT_FAILURE);
    }
}