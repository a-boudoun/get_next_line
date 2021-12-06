#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int fd;
    int i;
    char buf[100];
    int count = 8;

    fd = open("test.txt", O_RDONLY);
    i = read(fd, buf, count);
    printf("%d\n", i);
    printf("%d\n", fd);
    printf("%s\n", buf);
}