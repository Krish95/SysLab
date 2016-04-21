#include<unistd.h> 
#include<dirent.h>
#include<stdio.h>
int main()
{
	int count,i;
	struct dirent **files;
	char pathname[4096];
	getcwd(pathname,sizeof(pathname));
	printf("%s\n",pathname);
	count=scandir(pathname,&files,NULL,alphasort);
	for(i=0;i<count;i++)
		printf("%s  %d\n",files[i]->d_name,files[i]->d_type);
	printf("\n");
}
