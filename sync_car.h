#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

struct station {
    pthread_mutex_t mutex;

    pthread_cond_t vagas_disponiveis;
    pthread_cond_t embarque_concluido;

    int esperando;
    int vagas_livres;
    int embarcando;
};

void station_init(struct station *station);

void station_wait_for_car(struct station *station);

void station_on_board(struct station *station);

void station_load_car(struct station *station, int count);

#endif