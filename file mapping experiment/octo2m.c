#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
int randNum()
{
    int num;
    return num = rand() % 20;
}
void generateMat100(int a[10][10])
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            a[i][j] = randNum();
    }
}
void createReadable(char *file)
{
    int f1 = open(file, O_RDONLY, 0644);
    int file2 = open("readImatMap.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    char inte[10];
    int a;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            read(f1, &a, sizeof(int));
            sprintf(inte, "%3ld", a);
            write(file2, inte, strlen(inte));
            if (j == 9 && i != 9)
                write(file2, "\n", 1);
            else if (j != 9)
                write(file2, " ", 1);
        }
    }
    close(f1);
    close(file2);
}
void showStdout(char *file)
{
    int c = open(file, O_RDONLY), rd;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            read(c, &rd, sizeof(int));
            printf("%3d", rd);
            if (j == 9 && i != 9)
                printf("\n");
            else if (j != 9)
                printf(" ");
        }
    }
    close(c);
}
int main()
{
    struct stat sta;
    off_t size;
    int *map;
    int f1, a[10][10], i = 0, j = 0, pgSize;
    char ma[] = "Imatrixmap.txt";
    f1 = open(ma, O_CREAT | O_RDWR | O_TRUNC, 0644);
    lseek(f1,sizeof(int)*100-1, SEEK_SET);
    write(f1, "", 1);
    lseek(f1, 0, SEEK_SET);
    generateMat100(a);
    fstat(f1, &sta);
    pgSize = sysconf(_SC_PAGESIZE); //размер страницы
    size = sta.st_size;
    map = (int *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, f1, 0);
    close(f1);
    memcpy(map, a, 400);
    createReadable(ma);
    showStdout(ma);
}