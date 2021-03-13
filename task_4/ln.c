#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int i = 1;
    int flags = 0;

    if (argc < 3)
    {
        printf("few arguments \n");
        exit(1);
    }
    if (!strcmp(argv[1], "-s"))
    {
        flags = 1;
        i = 2;
    }
    if (argv[i] == NULL)
    {
        printf("error with %d arg \n", i);
        exit(2);
    }
    if (argv[i + 1] == NULL)
    {
        printf("error with %d arg \n", i + 1);
        exit(3);
    }
    /* #include <unistd.h>
       int link(const char *path1, const char *path2);
       The link() function shall create a new link (directory entry) for the existing file, path1.
    */
    if (!flags)
        link(argv[i], argv[i + 1]);
    else /* symlink - make a symbolic link to a file */
        symlink(argv[i], argv[i + 1]);
    return 0;
}
