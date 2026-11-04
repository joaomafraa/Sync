#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

typedef struct station{
    pthread_mutex_t mutex;

    pthread_cond_t vagas_disponiveis;
    pthread_cond_t embarque_concluido;

    int esperando;
    int vagas_livres;
    int embarcando;
}station;

void station_init(station *s);

void station_wait_for_car(station *s);

void station_on_board(station *s);

void station_load_car(station *s, int count);

#endif