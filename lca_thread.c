#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int check[20]={0},tree[20]={-1},lca_ind;
pthread_mutex_t mutex;

void lca(void* lca_index)
{
	int p = (int)lca_index;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(check[p]==1)
		{
			lca_ind = p;
			pthread_mutex_unlock(&mutex);
			return;
		}
		check[p]=1;
		p/=2;
		pthread_mutex_unlock(&mutex);
	}
}
int main()
{
	pthread_t t1,t2;
	int no,i,j,k,a,b,nodea[20],nodeb[20],indexa=1,indexb=1;
	printf("Enter the no of nodes:");
	scanf("%d",&no);
	for(i=1;i<=no;i++)
		scanf("%d",&tree[i]);
	printf("Enter node to be searched for:");
	scanf("%d %d",&a,&b);

	for(i=1;i<=no;i++)
	{
		if(tree[i]==a)
		{	
			nodea[indexa] = i;
			indexa++;
		}
		if(tree[i]==b)
		{	
			nodeb[indexb] = i;
			indexb++;
		}
	}
	for(i=1;i<indexa;i++)
	{
		for(j=1;j<indexb;j++)
		{
			pthread_create(&t1,0,lca,(void*)nodea[i]);
			pthread_create(&t2,0,lca,(void*)nodeb[j]);
			pthread_join(t1,0);
			pthread_join(t2,0);
			printf("LCA is %d when nodea @ %d and nodeb @ %d\n",tree[lca_ind],nodea[i],nodeb[j]);
			for(k=0;k<20;k++)
				check[k]=0;
		}
	}
	return 0;
}