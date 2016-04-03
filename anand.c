#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define	left(i)		(i)
#define	right(i)	(((i) + 1) % 5)

sem_t fork[5], footman;

void get_forks(int i)
{
	sem_wait(&footman);
	sem_wait(&fork[right(i)]);
	sem_wait(&fork[left(i)]);
}

void put_forks(int i)
{
	sem_post(&fork[right(i)]);
	sem_post(&fork[left(i)]);
	sem_post(&footman);
}


void* philosopher(void* n)
{
	while(1){
		printf("%d. thinking\n", (int)n);
		sleep(1);
		
		get_forks((int)n);
		
		printf("%d. eating\n", (int)n);
		sleep(1);
		
		put_forks((int)n);
		
	}
}


int main()
{
	pthread_t p[5];
	int i;
		
	sem_init(&footman, 0, 4);
	for(i = 0; i < 5; i++)
		sem_init(&fork[i],0,1);
	for(i = 0; i < 5; i++)
		pthread_create(&p[i],NULL,philosopher,(void*)i);
	for(i = 0; i < 5; i++)
		pthread_join(p[i],NULL); 
	return 0;
}
