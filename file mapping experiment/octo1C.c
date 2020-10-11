#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
void error(char *str, char *filename)
{
    printf(str, filename);
    exit(-1);
}
void createReadable(char *file)
{
     int c = open(file, O_RDONLY), rd;
     int f2=open("rdInt.txt",O_CREAT|O_RDWR);
     char buff[10];
    while (read(c, &rd, sizeof(int)) > 0)
    {
        sprintf(buff,"%3d", rd);
        write(f2,buff,strlen(buff));
    }
    close(c);
    close(f2);
}
void showStdout(char *file)
{
    int c = open(file, O_RDONLY), rd;
    while (read(c, &rd, sizeof(int)) > 0)
    {
        printf("|%d|", rd);
    }
    close(c);
}
int main()
{
    srand((unsigned)time(NULL));
    int f1, f2, rd, n;
    char file[] = "inte.txt", tmp[] = "ftmp.txt", buff[10];
    f1 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    f2 = open(tmp, O_CREAT | O_RDWR);
    for (int i = 0; i < 10; i++)
    {
        int a = rand() % 20;
        write(f1, &a, sizeof(int));
        if (a% 2 != 0)
            write(f2, &a, sizeof(int));
    }
     printf("current content in file:");
    showStdout(file);
    close(f1);
    close(f2);
    f1 = open(file, O_RDWR | O_TRUNC, 0644);
    f2 = open(tmp, O_RDONLY, 0644);
    while ((n = read(f2, &rd, sizeof(int))) > 0)
        if (write(f1, &rd, sizeof(int)) != n)
            error("error write:%s", file);
    printf("\n now current content in file:");
    showStdout(file);
    close(f1);
    close(f2);
    remove(tmp);
}

/////character style file
/*int f1, f2;
    char file[] = "fi.txt", tmp[] = "ftmp.txt", buff[10];
    f1 = open(file, O_RDONLY, 0644);
    int lenf = lseek(f1, 0, SEEK_END);
    lseek(f1, 0, SEEK_SET);
    char content[lenf];
    if (!(read(f1, content, lenf)))
        error("error occurs when reading file %s", file);
    f2 = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0777);
    int i = 0;
    for (i; content[i] != ' '; i++)
    {
        if (content[i + 1] == ' ' && ((content[i] - '0') % 2 != 0))
            (write(f2, content, i + 1));
    }
    int h;
    for (i; i < lenf; i++)
    {
        if (content[i] == ' ')
            h = i;
        if (content[i + 1] == ' ' && ((content[i] - '0') % 2 != 0))
            (write(f2, content + h, i + 1 - h));
        if (content[i + 1] == '\0' && ((content[i] - '0') % 2 != 0))
            (write(f2, content + h, i + 1 - h));
    }
    close(f1);
    close(f2);
    f1 = open(file, O_RDWR | O_TRUNC, 0644);
    f2 = open(tmp, O_RDONLY, 0644);
    while ((i = read(f2, buff, 10)) > 0)
        if (write(f1, buff, i) != i)
            error("error write:%s", file);
    close(f1);
    close(f2);
    remove(tmp);
}*/