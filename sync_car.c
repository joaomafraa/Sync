#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "sync_car.h"

void station_init(struct station *s){
    s->esperando =0;
    s->vagas_livres=0;
    s->embarcando=0;
    
    pthread_mutex_init(&s->mutex,NULL);
    pthread_cond_init(&s->vagas_disponiveis,NULL);
    pthread_cond_init(&s->embarque_concluido,NULL);
}
void station_wait_for_car(struct station *s){
    pthread_mutex_lock(&s->mutex); //protegendo a variavel para outra thread nao mudar
    s->esperando++;
    while (s->vagas_livres==0)//se nao tiver vgas deixa a thread dormindo 
    {
        pthread_cond_wait(&s->vagas_disponiveis,&s->mutex);//thread dorme e libera o mutex atualizar a variavel
    }
    s->esperando--;//deixa de ser esperando
    s->vagas_livres--;
    s->embarcando++;
    pthread_mutex_unlock(&s->mutex);
}
void station_on_board(struct station *s){
    pthread_mutex_lock(&s->mutex);
    s->embarcando--;//conclui o embarque diminui
    if(s->embarcando==0){//ele foi o ultimo passageiro
        pthread_cond_signal(&s->embarque_concluido);// avisa a thread do vagao 
    }
    pthread_mutex_unlock(&s->mutex);
}

void station_load_car(struct station *s,int count){
    pthread_mutex_lock(&s->mutex);

    s->vagas_livres = count;

    pthread_cond_broadcast(&s->vagas_disponiveis);

    while((s->vagas_livres > 0 && s->esperando > 0) || s->embarcando > 0){
        pthread_cond_wait(&s->embarque_concluido,&s->mutex);
    }

    s->vagas_livres = 0;

    pthread_mutex_unlock(&s->mutex);
}
