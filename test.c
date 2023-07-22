#include<unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("file", O_RDONLY);
    dup2(fd,STDIN_FILENO);
    char *args[] = {"cat", NULL};
    execve("/bin/cat",args, NULL);
}