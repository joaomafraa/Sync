#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

typedef struct station {
    pthread_mutex_t mutex;

    pthread_cond_t vagas_disponiveis;
    pthread_cond_t embarque_concluido;

    int esperando;    
    int vagas_livres;  
    int embarcando;
}station;