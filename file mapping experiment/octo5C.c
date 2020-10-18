#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
void createWithTrace(char*file)
{
      int f1 = open(file, O_RDONLY, 0644);
     int file2=open("readImat.txt",O_CREAT|O_RDWR|O_TRUNC,0644);
     char inte[10];
     int a;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
           {
               read(f1,&a,sizeof(int));
               sprintf(inte,"%3d",a);
               write(file2,inte,strlen(inte));
               if(j==9&&i!=9)
               write(file2,"\n",1);
               else if(j!=9)
               write(file2," ",1);
           }
    }
    write(file2,"\n",1);
     sprintf(inte,"%4d",a);
    write(file2,"trace=",6);
      write(file2,inte,strlen(inte));
    close(f1);
    close(file2);
}
void stdoutMat(char*file){

      int f1 = open(file, O_RDONLY, 0644);
     int a;
     lseek(f1,2*sizeof(int),SEEK_SET);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
           {
               read(f1,&a,sizeof(int));
               printf("%3d",a);
               if(j==9&&i!=9)
             printf("\n");
               else if(j!=9)
              printf(" ");
           }
    }
    close(f1);
}
int main()
{
  int f1, trace=0, i, j,a;
  char ma[] = "Imatrix.txt";
  if ((f1 = open(ma, O_CREAT | O_RDONLY, 0644)) == -1)
    printf("error");
  lseek(f1,2*sizeof(int),SEEK_SET);
  for (i=0; i < 10; i++)
    {
        for (j=0; j < 10; j++)
        {
            read(f1, &a, sizeof(int));
            if (i == j)
            trace+=a;
        }
    }
    stdoutMat(ma);
  printf("\ntrace=%d",trace);
  close(f1);
}