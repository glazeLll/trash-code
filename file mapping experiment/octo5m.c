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
void showStdout(char *file)

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
    int f1, i, j,trace=0;
    int*map;
    off_t size;
    struct stat sta;
    char ma[] = "Imatrixmap.txt";
    if ((f1 = open(ma, O_RDONLY, 0644)) == -1)
        printf("error");
    showStdout(ma);
    fstat(f1,&sta);
    size=sta.st_size;
    map=(int*)mmap(0,size,PROT_READ,MAP_SHARED,f1,0);
    int q=0;
     close(f1);
    for (i=0; i < 10; i++)
    {
        for (j=0; j < 10; j++)
        {
            if (j == i)
              trace+=map[q];
             q++;
        }
    }
    munmap(map,size);
      printf("\ntrace:%d",trace);
}
