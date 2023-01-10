#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<process.h>
#include<stdlib.h>
#include<dir.h>


int check_string(char cmd[],int a,char str[]);
void check_cmd(char cmd[]);
void creat_folder(char *name);
void creattxt(char *name);
void File(cmd);
void cut_my_file_name(char cmd[]);


int main()
{

   char cmd[1000];
    //while(1)
   // {
        gets(cmd);
        check_cmd(cmd);
  //  }
    return 0;
    //createfile --file /root/dir1/dir2/file.txt
    //createfile --file "/root/dir 1/dir 2/file 2.txt"
}


int check_string(char cmd[],int a,char str[])
{
    int b = strlen(str)+a;
    int size = b-a;
    char temp[size+1];
    int i;
    for (i=0;i<size;i++)
        temp[i]=cmd[a+i];
    temp[size]='\0';
    return strcmp(temp,str);
}


void check_cmd(char cmd[])
{
    if (check_string(cmd,0,"createfile --file ")==0)
    File(cmd);
    else
    {
       printf("wrongg");
    }
}
void creat_folder(char *name)
{
    mkdir(name);
}
void File(char cmd[])
{
     cut_my_file_name(cmd);
     char temp[1000];
     int i;
     for (i=0;cmd[i];i++)
     {
         temp[i]=cmd[i];
         temp[i+1]='\0';
         if (cmd[i+1]=='/')
         {
             creat_folder(temp);
         }

     }
//     creattxt(temp);
}
void cut_my_file_name(char cmd[])
{
    char temp[1000];
    int size=0;
    int i=strlen("createfile --file ");
    if (cmd[i]=='\"')
    {

        for (i=i+2;cmd[i]!='\"';i++)
            temp[size++]=cmd[i];
    }
    else
    {
        for (i=i+1;cmd[i];i++)
            temp[size++]=cmd[i];
    }
    temp[size]='\0';
    strcpy(cmd,temp);
    cmd[size]='\0';

}
