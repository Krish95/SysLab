#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct proc{
    int at;
    int bt;
}process;

int main()
{
    int no;process temp;int curtime=0,min;
    printf("Enter the no of processes:");
    scanf("%d",&no);
    process* list = malloc(sizeof(process) * no);

    for(int i=0;i<no;i++)
    {
	printf("Enter arrival time of process %d: ",i);
	scanf("%d",&list[i].at);
	printf("Enter burst time: ");
	scanf("%d",&list[i].bt);
    }

    for(int i=0;i<no;i++)
    {
	for(int j=0;j<no-i-1;j++)
	{
	    if(list[j].at > list[j+1].at)
	    {
		temp.at = list[j+1].at;
		temp.bt = list[j+1].bt;
		list[j+1].at = list[j].at;
		list[j+1].bt = list[j].bt;
		list[j].at = temp.at;
		list[j].bt = temp.bt;
	    }
	}
    }

    temp.at = INT_MAX;
    temp.bt = INT_MAX;
    for(int j=0;j<no;j++)
    {
	for(int i=0;i<no;i++)
	{
	    if(list[i].at <= curtime)
	    {
		if(temp.bt>list[i].bt)
		{
		    temp.at = list[i].at;
		    temp.bt = list[i].bt;
		    min = i;
		}
	    }
	}

	printf("Process %d executed at %d\n",min+1,curtime);
	curtime += temp.bt;
	list[min].at = INT_MAX;
	list[min].bt = INT_MAX;
	temp.at = INT_MAX;
	temp.bt = INT_MAX;

    }
    /* for(int i=0;i<no;i++) */
    /* { */
    /* 	printf("Process %d Arrival time is %d, Burst time is %d\n",i,list[i].at,list[i].bt); */
    /* } */
    return 0;
}
