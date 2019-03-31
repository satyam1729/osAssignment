#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
/*
Smoker0 has paper
Smoker1 has matches
Smoker2 has tobacco
*/

sem_t smokerSem[3];
sem_t agent;

void init(){
    sem_init(&agent, 0, 1);
    for (int i=0;i<3;i++){
        sem_init(&smokerSem[i], 0, 0);
    }
}
void smoke(int x){
    cout <<"smoker "<<x <<" smokes"<<endl;
}
void* smoker0Routine(void* arg){
    while(true){
        
        sem_wait(&smokerSem[0]);
        smoke(0);
        sem_post(&agent);
    }
}

void* smoker1Routine(void* arg){
    while(true){
        
        sem_wait(&smokerSem[1]);
        smoke(1);
        sem_post(&agent);
    }
}

void* smoker2Routine(void* arg){
    while(true){
        sem_wait(&smokerSem[2]);
        smoke(2);
        sem_post(&agent);
    }
}

int main(){
    pthread_t smoker_threads[3];
    init();
    pthread_create(&smoker_threads[0], NULL, smoker0Routine, NULL);
    pthread_create(&smoker_threads[0], NULL, smoker1Routine, NULL);
    pthread_create(&smoker_threads[0], NULL, smoker2Routine, NULL);
    pthread_exit(NULL);
    return 0;
}
