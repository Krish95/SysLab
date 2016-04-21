#include <sys/statvfs.h>
#include <stdio.h>

int main()
{
	struct statvfs buffer;
	char path[4096];
	
	scanf("%s", path);
	
	if((statvfs(path, &buffer)) ==  -1)
		return 1;
	
	unsigned long total = buffer.f_blocks * buffer.f_frsize / 1024;
	unsigned long available = buffer.f_bavail * buffer.f_frsize / 1024;
	unsigned long free = buffer.f_bfree * buffer.f_frsize / 1024;
	unsigned long used = total - free;

	printf("Total: %luK\n", total);
	printf("Available: %luK\n", available);
	printf("Used: %luK\n", used);
	printf("Free: %luK\n", free);

	// Calculate % used based on f_bavail not f_bfree.  This is still giving out a different answer to df???
	printf("Use%%: %f%%\n",  (buffer.f_blocks - buffer.f_bavail) / (double)(buffer.f_blocks) * 100.0); 

	
	return 0;
}
