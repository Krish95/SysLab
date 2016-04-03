#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


sem_t resource, mutex;
int readcount;

void* writer(void* n)
{
	while(1){
		printf("writer %d wants to write.\n", (int)n);
		sem_wait(&resource);
		printf("writer %d is writing.\n", (int)n);
		sem_post(&resource);
	}
	
}

void* reader(void *n)
{
	while(1){
		printf("reader %d wants to read.\n", (int)n);
		
		sem_wait(&mutex);
			readcount++;
			if(readcount == 1) sem_wait(&resource);
		sem_post(&mutex);
		
		printf("reader %d is reading.\n", (int)n);
		
		sem_wait(&mutex);
			readcount--;
			if(readcount == 0) sem_post(&resource);
		sem_post(&mutex);
		
	}
}


int main()
{
	pthread_t r[5], w[5];
	int i;
		
	sem_init(&resource, 0, 1);
	sem_init(&mutex, 0, 1);
	readcount = 0;
	
	for(i = 0; i < 5; i++){
		pthread_create(&r[i],NULL,reader,(void*)i);
		pthread_create(&w[i],NULL,writer,(void*)i);
	}
	for(i = 0; i < 5; i++){
		pthread_join(r[i],NULL); 
		pthread_join(w[i],NULL); 
	}
	return 0;
}
