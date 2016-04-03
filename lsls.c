#include <unistd.h> // getcwd
#include <dirent.h> // scandir, alphasort

int main()
{
    int count,i;
    struct dirent **files;
	char pathname[4096];

    getcwd(pathname, sizeof(pathname));

    printf("%s\n",pathname);
    
	count = scandir(pathname, &files, NULL, alphasort);
    
    for (i=0; i<count; ++i)
        printf("%s\n", files[i]->d_name);
    printf("\n");
}
