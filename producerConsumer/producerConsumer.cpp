#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
//resources for the problem
const int size = 10;
int buffer[size];
int index=0;

//semaphores definition
sem_t f;
sem_t e;
pthread_mutex_t mutex; // mutex for acess to buffer
void initialize(){
	sem_init(&e,0,size);
	sem_init(&f,0,0);
	pthread_mutex_init(&mutex,NULL);
}
int produceNew(){
	//function that generates new item
	int sth = -1;
	return sth;
}
void consumeOne(int itemGot){
	//use the consumed item in this fuction
}
void* producerRoutine(void* arg){
	while(1){
		sem_wait(&e);
		pthread_mutex_lock(&mutex);
		int item = produceNew();
		index++;
		buffer[index] = item;
		//item has been added to buffer
		pthread_mutex_unlock(&mutex);
		sem_post(&f);
	}
}

void* consumerRoutine(void* arg){
	while(1){
		sem_wait(&f);
		pthread_mutex_lock(&mutex);
		int item = buffer[index];
		index--;
		consumeOne(item);
		//item has been consumed
		pthread_mutex_unlock(&mutex);
		sem_post(&e);
	}
}

int main(){
	pthread_t p,c;
	initialize();
	pthread_create(&p,NULL,producerRoutine,NULL);
	pthread_create(&c,NULL,consumerRoutine,NULL);
	pthread_exit(NULL);
}