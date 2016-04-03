#include <sys/statvfs.h>
#include <stdio.h>

int main()
{
	struct statvfs buffer;
	char path[4096];
	
	scanf("%s", path);
	
	if((statvfs(path, &buffer)) ==  -1)
		return 1;
	
	printf("%u\n%u\n", buffer.f_bsize * buffer.f_blocks, buffer.f_bsize * buffer.f_bfree);
	
	return 0;
}
