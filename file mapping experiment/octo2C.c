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
    int file2 = open("readImat.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
    lseek(f1, 2 * sizeof(int), SEEK_SET);
    char inte[10];
    int a;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            read(f1, &a, sizeof(int));
            sprintf(inte, "%3d", a);
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
    int c = open(file, O_RDONLY, 0644), rd;
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

void wrRowInfo(int file, int row)
{
    write(file, &row, sizeof(int));
}
void wrColumnInfo(int file, int column)
{
    write(file, &column, sizeof(int));
}
int main()
{
    int fd, a[10][10], i = 0, j = 0;
    char ma[] = "Imatrix.txt";
    fd = open(ma, O_CREAT | O_RDWR | O_TRUNC, 0644);
    generateMat100(a);
    wrRowInfo(fd, 10);
    wrColumnInfo(fd, 10);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int q = a[i][j];
            write(fd, &q, sizeof(int));
        }
    }
    close(fd);
    createReadable(ma);
    showStdout(ma);
}