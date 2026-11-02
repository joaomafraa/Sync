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

void station_init(station *s){
    s->esperando =0;
    s->vagas_livres=0;
    s->embarcando=0;
    
    pthread_mutex_init(&s->mutex,NULL);
    pthread_cond_init(&s->vagas_disponiveis,NULL);
    pthread_cond_init(&s->embarque_concluido,NULL);
}
void wait_for_car(station *s){
    pthread_mutex_lock(&s->mutex); //protegendo a variavel para outra thread nao mudar
    s->esperando++;
    while (s->vagas_livres==0)//se nao tiver vgas deixa a thread dormindo 
    {
        pthread_cond_wait(&s->vagas_disponiveis,&s->mutex);//thread dorme e libera o mutex atualizar a variavel
    }
    s->esperando--;//deixa de ser esperando
    s->vagas_livres--;
    s->embarcando++;
}