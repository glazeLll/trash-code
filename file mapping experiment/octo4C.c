#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
int randNum()
{
    int num;
    return num = rand() % 20;
}
void showStdout(char *file)
{
    int c = open(file, O_RDONLY), rd;
    lseek(c, 2 * sizeof(int), SEEK_SET);
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
    int f1, i, j;
    char ma[] = "Imatrix.txt";
    if ((f1 = open(ma, O_RDONLY, 0644)) == -1)
        printf("error");
    showStdout(ma);
    lseek(f1, 2 * sizeof(int), SEEK_SET);
    printf("\n upper diagonal elements:\n");
    int a;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            read(f1, &a, sizeof(int));
            if (j <= i)
                printf("    ");
            else
            {
                printf("%3d", a);
                if (j == 9 && i != 9)
                    printf("\n");
                if (j != 9)
                    printf(" ");
            }
        }
    }
    close(f1);
}
