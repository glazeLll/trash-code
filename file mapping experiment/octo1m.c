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
    int f2 = open("rdInt.txt", O_CREAT | O_RDWR);
    char buff[10];
    while (read(c, &rd, sizeof(int)) > 0)
    {
        sprintf(buff, "%3d", rd);
        write(f2, buff, strlen(buff));
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
      printf("\n");
    close(c);
}
int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    struct stat sta;
    off_t len;
    int *map;
    int fd, pgSize, sz;
    int countOdd = 0, save[countOdd];
    char ch[] = "intemap.txt";
    fd = open(ch, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd == 1)
    {
        perror("open");
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        int a = rand() % 20;
        if (a % 2 != 0)
        {
            save[countOdd] = a;
            countOdd++;
        }
        write(fd, &a, sizeof(int));
    }
    printf("current content in file:");
    showStdout(ch);
    ftruncate(fd, sizeof(int) * countOdd);/////change file size
    if (fstat(fd, &sta) == 1)
    {
        perror("fstat");
        return 1;
    }
    if (!S_ISREG(sta.st_mode))
    {
        fprintf(stderr, "%s is not a file n", "fi.txt");
        return 1;
    }
    pgSize = sysconf(_SC_PAGESIZE); //размер страницы
    sz = sta.st_size;               //минимальное число больше исходного и кратное размеру
    //страниц ((sb.st_size - 1) / pgs + 1) * pgs;
    map = (int *)mmap(0, sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }
    if (close(fd) == 1)
    {
        perror("close");
        return 1;
    }
    memset(map, '\0', sz);
    memcpy(map, save, sizeof(int) * (countOdd));
    munmap(map, sz);
    printf("now content in file:");
    showStdout(ch);
}

/*int main()
{
    struct stat sta;
    off_t len;
    int f1, f2,pgSize,size;
    char file[] = "fi.txt", tmp[] = "ftmp.txt", buff[10];
    f1 = open(file, O_RDWR, 0644);
     if (fstat(f1, &sta) == 1)
    {
        perror("fstat");
        return 1;
    }
     if (!S_ISREG(sta.st_mode))
    {
        fprintf(stderr, "%s is not a file n",file);
        return 1;
    }
pgSize=sysconf(_SC_PAGESIZE);
size= ((sta.st_size - 1) /pgSize + 1) * pgSize;
if((map= mmap(0, size, PROT_READ, MAP_SHARED,f1,0))==(caddr_t)-1);
{printf("mmap error");
return 0;
}
close(f1);
printf("%s",map);
}*/
