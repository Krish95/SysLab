#include<stdio.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>

int table_used=1,generated_item[2],generated=0;
char *item[]={"Tobacco","Paper","Matches"};
sem_t table;

void *agent(void *arg)
{
	int i,j,k=0;
	while(1)
		{
			sleep(1);
			sem_wait(&table);
			if(table_used==1)
				{
					i=k;
					j=i+1;
					if(j==3) j=0;
					k=j;
					
					generated_item[0]=i;
					generated_item[1]=j;
					printf("Agent produced %s, %s \n",item[i],item[j]);
					generated=1;
					table_used=0;
				}
			sem_post(&table);
		}
}

void *smokeri(int j)
{
int i=(int) j;
	while(1)
	{
		sleep(1);
		sem_wait(&table);
		if(table_used==0)
		{	
		if(generated && generated_item[0]!=i && generated_item[1]!=i)
			{
			printf("Smoker_%d completed his smoking \n\n",i);
			table_used=1;
			generated=0;
			}
		}
	sem_post(&table);
	}
}

main()
{
printf("\nSmoker_0 has Tobacco\nSmoker_1 has Paper\nSmoker_2 has Matches\n\n");
pthread_t smkr0,smkr1,smkr2,agnt;
sem_init(&table,0,1);
pthread_create(&agnt,NULL,agent,(void*) 0);
pthread_create(&smkr0,NULL,smokeri,(void*) 0);
pthread_create(&smkr1,NULL,smokeri,(void*) 1);
pthread_create(&smkr2,NULL,smokeri,(void*) 2);
while(1);
} 
