#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <stdlib.h>
#include <dir.h>
#include <dirent.h>

int check_string(char cmd[], int a, char str[]);
void check_cmd(char cmd[]);
void creat_folder(char *name);
void File(cmd);
void cut_my_file_name(char cmd[]);
void creat_txt_file(char adress[]);
void insert(char cmd[]);
void write_if_file(char address[], char text[][100], int size);
void cat(char cmd[]);
void find(char cmd[]);
void findat(char cmd[]);
void findall(char cmd[]);
void replace(char cmd[]);
void replaceat(char cmd[]);
void replaceall(char cmd[]);
void removeandadd(char address[], char book[][100], char str1[], char str2[], int a, int b, int size);
void remove_txt(char cmd[]);
void text_comparator(char cmd[]);
int tree(char k[], int a);
int pretree(char cmd[]);
int max(int a, int b);
int grep(char cmd[]);
void autoindent(char cmd[]);
void writeinfileinsert(char address[], char text[][100], char str[], int a, int b, int size);
void undo(char adress[]);
void undosave(char text[][100]);
void arman(char cmd[]);
void copy(char cmd[]);
void paste(char cmd[]);


int plus =0;
int findbycount = 0;
int findbyat = 0;
int findbyword = 0;
int flag = 0;
int typec = 0;
int typel = 0;
int clipboardtype = 0;
int cut = 0;
char clipboard[100000];
char undomemory[100][100];
char armann[100][100];

int main()
{
   char cmd[1000];
    while (1)
    {
        findbycount = 0;
        findbyword = 0;
        clipboardtype = 0;
        cut = 0;
        flag = 0;
        typec = 0;
        typel = 0;
        gets(cmd);
        check_cmd(cmd);
    }
    return 0;
}
/*
CREATEFILE:

    createfile --file /root/dir1/dir2/file.txt
    createfile --file "/root/dir 1/dir 2/file.txt"

INSERT:

    insertstr --file /root/pouyan.txt -str salam --pos 1:0
    insertstr --file /root/pouyan.txt -str "Salam man\npouyan hastam" --pos 2:5

CAT:

    cat --file /root/dir1/dir2/file.txt
    cat --file "/root/dir 1/dir 2/file.txt"

REMOVE:
    removestr --file /root/pouyan.txt --pos 2:1 -size 3 -b
    removestr --file /root/pouyan.txt --pos 2:1 -size 3 -f
    removestr --file /root/pouyan.txt --pos 2:5 -size 5 -b


COPY_CUT_PASTE:
    copystr --file /root/pouyan.txt --pos 1:1 -size 3 f
    copystr --file /root/pouyan.txt --pos 1:12 -size 3 b
    pastestr --file /root/pouyan2.txt --pos 1:0
    cutstr --file /root/pouyan.txt --pos 2:1 -size 3 -f
    cutstr --file /root/pouyan.txt --pos 3:5 -size 8 -f

FIND:

    find --str "this is an expression containing white-space." --file /root/pouyan.txt
    find --str pouyan --file /root/pouyan.txt -count
    find --str pouyan --file /root/dir1/dir2/file.txt -byword
    find --str pouyan --file /root/dir1/dir2/file.txt -all
    find --str file test --file /root/dir1/dir2/file.txt
    find --str "pouyan shams" --file /root/dir1/dir2/file.txt
    find --str "file test" --file /root/dir1/dir2/file.txt


REPLACE:
    replace --str1 pouyan --str2 mobin --file /root/pouyan.txt
    replace --str1 pouyan --str2 mobin --file /root/pouyan.txt -at 3
    replace --str1 yeadambadbakht --str2 "pouyan shams" --file /root/pouyan.txt

GREP:
    grep --str pouyan --files /root/pouyan.txt
    grep -c --str pouyan --files /root/pouyan.txt
    grep --str pouyan --files /root/pouyan.txt /root/pouyan2.txt
    grep -l --str pouyan --files /root/pouyan.txt /root/pouyan2.txt

UNDO:
    undo /root/pouyan.txt

COMPARE:
    compare /root/pouyan.txt /root/pouyan2.txt

CLOSING PAIRS:
    auto-indent /root/pouyan.txt
*/

int check_string(char cmd[], int a, char str[])
{
    int b = strlen(str) + a;
    int size = b - a;
    char temp[size + 1];
    for (int i = 0; i < size; i++)
        temp[i] = cmd[a + i];
    temp[size] = '\0';
    return strcmp(temp, str);
}

void check_cmd(char cmd[])
{
    if (check_string(cmd, 0, "createfile --file ") == 0)
        File(cmd);
    else if (check_string(cmd, 0, "insertstr --file ") == 0)
        insert(cmd);
    else if (check_string(cmd, 0, "cat --file ") == 0)
        cat(cmd);
    else if (check_string(cmd, 0, "find --str ") == 0 && strstr(cmd, "count") == 0 && strstr(cmd, "at") == 0 && strstr(cmd, "all") == 0 && strstr(cmd, "byword") == 0 )
        find(cmd);

    else if (check_string(cmd, 0, "find --str ") == 0 && strstr(cmd, "count") == 0 && strstr(cmd, "at") == 0 && strstr(cmd, "all") == 0 && strstr(cmd, "-byword") != 0 )
    {
       findbyword=1;
        find(cmd);
    }
    else if (check_string(cmd, 0, "find --str ") == 0 && strstr(cmd, "count") != 0 && strstr(cmd, "at") == 0 && strstr(cmd, "all") == 0)
    {
        findbycount = 1;
        find(cmd);
    }
    else if (check_string(cmd, 0, "find --str ") == 0 && strstr(cmd, "count") == 0 && strstr(cmd, "at") != 0 && strstr(cmd, "all") == 0)
    {
        findat(cmd);
    }
    else if (check_string(cmd, 0, "find --str ") == 0 && strstr(cmd, "count") == 0 && strstr(cmd, "at") == 0 && strstr(cmd, "all") != 0)
    {
        findall(cmd);
    }



    else if (check_string(cmd, 0, "replace --str1") == 0 )
        replace(cmd + strlen("replace --str1 "));

    else if (check_string(cmd, 0, "replace --str1") == 0 && strstr(cmd, "-all") == 1 )
        replace(cmd + strlen("replace --str1 "));


    else if (check_string(cmd, 0, "removestr --file") == 0)
        remove_txt(cmd + strlen("removestr --file "));
    else if (check_string(cmd, 0, "compare ") == 0)
        text_comparator(cmd + strlen("compare "));
    else if (check_string(cmd, 0, "tree ") == 0 && strstr(cmd, "=D") == 0)
        pretree(cmd);
    else if (check_string(cmd, 0, "grep --str ") == 0)
        grep(cmd + strlen("grep --str  "));
    else if (check_string(cmd, 0, "grep -c --str ") == 0)
    {
        typec = 1;
        grep(cmd + strlen("grep -c --str  "));
    }
    else if (check_string(cmd, 0, "grep -l --str ") == 0)
    {
        typel = 1;
        grep(cmd + strlen("grep -l --str  "));
    }
    else if (check_string(cmd, 0, "auto-indent") == 0)
        autoindent(cmd + strlen("auto-indent "));
    else if (check_string(cmd, 0, "undo --file") == 0)
        undo(cmd + strlen("undo --file "));
    else if (strstr(cmd, "=D"))
    {
        flag = 1;
        arman(cmd);
    }
    else if (check_string(cmd, 0, "copystr --file ") == 0)
        copy(cmd + strlen("copystr --file "));
    else if (check_string(cmd, 0, "cutstr --file ") == 0)
    {
        clipboardtype = 1;
        remove_txt(cmd + strlen("cutstr --file "));
    }
    else if (check_string(cmd, 0, "pastestr --file ") == 0)
    {

        paste(cmd + strlen("pastestr --file "));
    }
    else
        printf("invalid command\n");
}

void creat_folder(char *name)
{
    mkdir(name);
}

void File(char cmd[])
{
    cut_my_file_name(cmd);
    char temp[1000];
    for (int i = 0; cmd[i]; i++)
    {
        temp[i] = cmd[i];
        temp[i + 1] = '\0';
        if (cmd[i + 1] == '/')
        {
            creat_folder(temp);
        }
    }
    creat_txt_file(temp);
}

void cut_my_file_name(char cmd[])
{
    char temp[1000];
    int size = 0;
    int i = strlen("createfile --file ");
    if (cmd[i] == '\"')
    {

        for (i = i + 2; cmd[i] != '\"'; i++)
            temp[size++] = cmd[i];
    }
    else
    {
        for (i = i + 1; cmd[i]; i++)
            temp[size++] = cmd[i];
    }
    temp[size] = '\0';
    strcpy(cmd, temp);
    cmd[size] = '\0';
}

void creat_txt_file(char adress[])
{
    FILE *f;
    f = fopen(adress, "r");
    if (f == NULL)
    {
        f = fopen(adress, "w");
        printf("file created\n");
    }
    else
    {
        printf("File Vojod Darad\n");
    }
}

// insertstr --file /root/dir1/dir2/file.txt -str salam --pos 1:0
// pastestr --file /root/dir1/dir2/file.txt -str salam --pos 1:0

void insert(char cmd[])
{
    char temp[1000];
    int size = 0;
    int i = strlen("insertstr --file ");
    if (cmd[i] == '\"')
    {

        for (i = i + 2; cmd[i] != '\"'; i++)
            temp[size++] = cmd[i];
        temp[size] = '\0';
    }
    else
    {
        for (i = i + 1; cmd[i]; i++)
        {
            if (cmd[i] == ' ')
                break;
            temp[size++] = cmd[i];
        }
        temp[size] = '\0';
    }

    FILE *f;
    f = fopen(temp, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {
        char book[100][100];
        int size = 0;
        while (fgets(book[size], 100, f))
            size++;
        i += 6;
        undosave(book);
        char str[1000];
        int str_count = 0;
        if (cmd[i] == '\"')
        {
            for (i = i + 1; cmd[i]; i++)
            {

                if (check_string(cmd, i, "\" --pos") == 0)
                    break;
                str[str_count++] = cmd[i];
            }
            i++;
        }
        else
        {
            for (i = i; cmd[i]; i++)
            {
                if (check_string(cmd, i, " --pos") == 0)
                    break;
                str[str_count++] = cmd[i];
            }
        }
        str[str_count] = '\0';
        int a = 0, b = 0;
        i += 7;
        // printf("%c",cmd[i]);
        while (cmd[i] && cmd[i] != ':')
            a = a * 10 + (cmd[i++] - '0');
        a--;
        i++;
        while (cmd[i])
            b = b * 10 + (cmd[i++] - '0');

        int j, z;

        if (a >= size || a < 0)
        {
            printf("to mahdode nist\n");
            return 1;
        }
        if (flag == 1)
            writeinfileinsert(temp, book, armann, a, b, size);
        else
            writeinfileinsert(temp, book, str, a, b, size);
    }

    fclose(f);
}


void writeinfileinsert(char address[], char text[][100], char str[], int a, int b, int size)
{

    FILE *f1;
    f1 = fopen(address, "w");

    for (int i = 0; i < size; i++)
    {

        for (int j = 0; text[i][j]; j++)
        {

            if (i == a && j == b)
            {


                for (int k=0;k<strlen(str);k++)
                {
                    if (str[k]== '\\'  && str[k+1]=='\\' && str[k+2]=='n')
                        {

                           fprintf(f1, "%s","\\n");
                           k+=3;

                        }
                   else if (str[k]== '\\'  && str[k+1]=='n')
                        {
                           fprintf(f1, "\n");
                             k+=2;

                        }
                    fprintf(f1, "%c", str[k]);
                }



                fprintf(f1, "%c", text[i][j]);
            }
            else
                fprintf(f1, "%c", text[i][j]);
        }

    }


    printf("Ebarat Mored Nazar Ezafe Shod Jenab\n");
    fclose(f1);
}

void write_if_file(char address[], char text[][100], int size)
{
    int num;
    char tab = "\n";
    FILE *fptr;
    fptr = fopen(address, "w");
    if (fptr == NULL)
        printf("Error!\n");
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; text[i][j]; j++)
                if (text[i][j] == '\\' && text[i][j + 1] == 'n')
                {
                    fprintf(fptr, "%c", "\n");
                    j++;
                }
                else if (text[i][j] == '\\' && text[i][j + 1] == '\\' && text[i][j + 2] == 'n')
                {
                    fprintf(fptr, "\\n");
                    j += 2;
                }
                else
                {
                    fprintf(fptr, "%c", text[i][j]);
                }
        }
        printf("finish\n");
    }

    fclose(fptr);
}

void cat(char cmd[])
{
    char temp[1000];
    int size = 0;
    int i = strlen("cat --file ");
    if (cmd[i] == '\"')
    {

        for (i = i + 2; cmd[i + 1]; i++)
            temp[size++] = cmd[i];
    }
    else
    {
        for (i = i + 1; cmd[i]; i++)
            temp[size++] = cmd[i];
    }
    temp[size] = '\0';
    FILE *f;
    f = fopen(temp, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {
        char book[100];
        int size = 0;
        while (fgets(book, 100, f))
            printf("%s", book);
        printf("\n");
    }
}

// replace --str1 mobin --str2 pouyan --file /root/pouyan.txt
// find --str pouyan --file /root/pouyan.txt -count
void find(char cmd[])
{
    char temp[1000], address[100];
    int size = 0;
    int i = strlen("find --str ");
    if (cmd[i] == '\"')
    {

        for (i = i + 1; cmd[i]; i++)
        {
            // printf("%c",cmd[i]);
            if (check_string(cmd, i, "\" --file") == 0)
            {
                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    else
    {
        for (i = i; cmd[i]; i++)
        {
            // printf("%c",cmd[i]);
            if (check_string(cmd, i, " --file") == 0)
            {

                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    i = i + 2;
    while (cmd[i] && cmd[i] != ' ')
        i++;
    i += 2;
    int j;
    for (j = 0; cmd[i] && cmd[i] != ' '; i++, j++)
        address[j] = cmd[i];
    address[j] = '\0';

    FILE *f;
    f = fopen(address, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {
        if (findbycount == 1)
        {
            int check = 0;
            char book[100][100];
            int txtsize = 0;
            while (fgets(book[txtsize], 100, f))
                txtsize++;

            for (int i = 0; i < txtsize; i++)
            {
                for (int j = 0; book[i][j]; j++)
                    if (check_string(book[i], j, temp) == 0)
                    {
                        check++;
                    }

            }

            printf("%d\n", check);
        }
        else if (findbyword==1)
        {

           {
            int check = 0;
            int space=1;
            char book[100][100];
            int txtsize = 0;
            while (fgets(book[txtsize], 100, f))
                txtsize++;

            for (int i = 0; i < txtsize; i++)
            {
                for (int j = 0; book[i][j]; j++){
                     if (check_string(book[i], j, temp) == 0)
                    {
                        check=-1;
                        break;
                    }

                   if(book[i][j]==' ' || book[i][j]=='\n')
                         space++;
                }
                if (check==-1)
                    break;
            }

            printf("%d\n", space);
        }





        }
        // find adi


        else
        {
            int check = -1;
            int counter = 0;
            char book[100][100];
            int txtsize = 0;
            while (fgets(book[txtsize], 100, f))
                txtsize++;

            for (int i = 0; i < txtsize; i++)
            {
                for (int j = 0; book[i][j]; j++, counter++)
                    if (check_string(book[i], j, temp) == 0)
                    {
                        check = 1;
                        break;
                    }
                if (check == 1)
                    break;
            }
            if (check == -1)
                counter = -1;
            printf("%d\n", counter);
        }
    }
}

findat(char cmd[])
{

    char temp[1000], address[100];
    int size = 0;
    int i = strlen("find --str ");
    if (cmd[i] == '\"')
    {

        for (i = i + 1; cmd[i]; i++)
        {
            // printf("%c",cmd[i]);
            if (check_string(cmd, i, "\" --file") == 0)
            {
                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    else
    {
        for (i = i; cmd[i]; i++)
        {
            // printf("%c",cmd[i]);
            if (check_string(cmd, i, " --file") == 0)
            {

                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    i = i + 2;
    while (cmd[i] && cmd[i] != ' ')
        i++;
    i += 2;
    int j;
    for (j = 0; cmd[i] && cmd[i] != ' '; i++, j++)
        address[j] = cmd[i];
    address[j] = '\0';
    i += 5;
    int n = cmd[i] - '0';

    FILE *f;
    f = fopen(address, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {

        int check = 0;
        int counter = 0;
        int flag = 1;
        char book[100][100];
        int txtsize = 0;
        while (fgets(book[txtsize], 100, f))
            txtsize++;

        for (int i = 0; i < txtsize; i++)
        {
            for (int j = 0; book[i][j]; j++, counter++)
                if (check_string(book[i], j, temp) == 0)
                {
                    if (n == flag)
                    {
                        check = 1;
                        break;
                    }
                    else
                        flag++;
                }
            if (check == 1)
                break;
        }
        if (check == -1 || flag != n)
            counter = -1;
        printf("%d\n", counter);
    }
}



//find --str pouyan --file /root/dir1/dir2/file.txt -all
findall(char cmd[])
{
    char temp[1000], address[100];
    int size = 0;
    int i = strlen("find --str ");
    if (cmd[i] == '\"')
    {

        for (i = i + 1; cmd[i]; i++)
        {
            // printf("%c",cmd[i]);
            if (check_string(cmd, i, "\" --file") == 0)
            {
                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    else
    {
        for (i = i; cmd[i]; i++)
        {
            // printf("%c",cmd[i]);
            if (check_string(cmd, i, " --file") == 0)
            {

                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    i = i + 2;


    while (cmd[i] && cmd[i] != ' ')
        i++;
    i += 2;
    int j;
    for (j = 0; cmd[i] && cmd[i] != ' '; i++, j++)
        address[j] = cmd[i];
    address[j] = '\0';

    FILE *f;
    f = fopen(address, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {

            int check = -1;
            int counter = 0;
            char book[100][100];
            int txtsize = 0;
            while (fgets(book[txtsize], 100, f))
                txtsize++;

            for (int i = 0; i < txtsize; i++)
            {
                for (int j = 0; book[i][j]; j++, counter++)
                    if (check_string(book[i], j, temp) == 0)
                    {
                        printf("%d ",counter);
                        check=1;
                    }

            }
            if (check == -1)
                printf("-1\n");
}

}



// replace --str1 mobin --str2 pouyan --file /root/pouyan.txt
void replace(char cmd[])
{

    char temp[1000];
    int size = 0;
    int i = 0;
    if (cmd[i] == '\"')
    {

        for (i = 1; cmd[i] != '\"'; i++)
            temp[size++] = cmd[i];
    }
    else
    {
        for (i = 0; cmd[i] != ' '; i++)
            temp[size++] = cmd[i];
    }
    temp[size] = '\0';
    strcpy(cmd, temp);
    cmd[size] = '\0';
    i += 8;
    size = 0;
    char str2[1000];

    if (cmd[i] == '\"')
    {
        i++;
        for (; cmd[i] != '\"'; i++)
            str2[size++] = cmd[i];
        str2[size] = '\0';
    }
    else
    {
        for (i; cmd[i] != ' '; i++)
            str2[size++] = cmd[i];
    }
    str2[size] = '\0';
    i += 8;
    int w = 0;
    char address[100];
    for (i; cmd[i]!=' ' && cmd[i]!=NULL; i++, w++)
        address[w] = cmd[i];
    address[w] = '\0';

int d=0;
int k=0;

    if(cmd[i+1]=='-'){
    k=cmd[i+5]-'0';
    k-=1;}


    FILE *f;
    f = fopen(address + 1, "r");
    if (f == NULL)
    {
        printf("hamchin file i vojod nadare jenab\n");
    }
    else
    {
        char book[100][100];
        int size = 0;
        while (fgets(book[size], 100, f))
            size++;
        int check = 0;
        int a, b;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; book[i][j]; j++)

                if (check_string(book[i], j, temp) == 0 )
                {


                    if (k==d){
                        printf("%d %d",k,d);
                       check = 1;
                       a = i;
                       b = j;
                       break;}
                    else
                        d++;

                }
            if (check == 1)
               break;
        }

        removeandadd(address, book, temp, str2, a, b, size);
    }


}
// replace --str1 pouyan --str2 mobin --file /root/pouyan.txt

void removeandadd(char address[], char book[][100], char str1[], char str2[], int a, int b, int size)
{
     printf("");
    int n = strlen(str1);

    int index = n + b;
    int k = b;
    int w = 0;
    for (index; book[a][index]; index++, k++)
    {
        book[a][k] = book[a][index];
    }

    book[a][k] = '\0';

    FILE *fptr;
    fptr = fopen(address + 1, "w");
    if (fptr == NULL)
        printf("Error!\n");
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; book[i][j]; j++)
            {

                if (i == a && j == b)
                {
                    fprintf(fptr, "%s", str2);
                    fprintf(fptr, "%c", book[i][j]);
                }
                else
                    fprintf(fptr, "%c", book[i][j]);
            }
        }
        printf("finish\n");
    }

    fclose(fptr);
}
//removestr --file /root/pouyan.txt --pos 2:1 -size 3 -b
//cutstr --file /root/pouyan.txt --pos 2:1 -size 3 -f
void remove_txt(char cmd[])
{
    puts(cmd);
    char temp[1000], address[100];
    int size = 0;
    int i = 0;
    if (cmd[i] == '\"')
    {

        for (i = i + 2; cmd[i]; i++)
        {

            if (check_string(cmd, i, "\" --pos ") == 0)
            {
                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    else
    {
        for (i = i + 1; cmd[i]; i++)
        {
            // printf("%c",cmd[i]);
            if (check_string(cmd, i, " --pos ") == 0)
            {

                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    FILE *f;
    f = fopen(temp, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {
        char book[100][100];
        int txtsize = 0;
        while (fgets(book[txtsize], 100, f))
            txtsize++;

        undosave(book);

        while (cmd[i] < '0' || cmd[i] > '9')
            i++;

        int a = 0, b = 0, size = 0;
        while (cmd[i] && cmd[i] != ':')
            a = a * 10 + (cmd[i++] - '0');
        i++;
        while (cmd[i] >= '0' && cmd[i] <= '9')
            b = b * 10 + (cmd[i++] - '0');

        i += 7;

        while (cmd[i] && cmd[i] != ' ')
        {
            size = size * 10 + (cmd[i] - '0');
            i++;
        }
        // printf("%d",size);

        char chr = cmd[strlen(cmd) - 1];
        a--;
        // printf("%c",chr);
        if (chr == 'f')
        {
            int index = size + b;
            int k = b;
            int w = 0;
            // printf("%c",book[a][k]);
            if (clipboardtype == 1)
            {
                for (w = 0; w < size; w++, k++)
                {
                    clipboard[w] = book[a][k];
                }
                clipboard[w+1]='\0';

            }

            k = b;
            for (index; book[a][index]; index++, k++)
            {
                // printf("hello");
                book[a][k] = book[a][index];
            }

            book[a][k] = '\0';
        }
        else
        {
            int size2=0;
             if (clipboardtype == 1)
            {
                for (int i = size - 1; i >= 0; i--, b--)
                clipboard[i] = book[a][b-1];
                clipboard[i+1]='\0';

            }


            int index;
            if (size>b)
            {
            size2 = size-b-1;
            size=b;
            plus=1;
            }


            for (index = b; book[a][b]; b++)
               book[a][b - size] = book[a][b];
            book[a][b - size] = '\0';

             if (plus==1)
            {
            int p=0;
            int bb=0;
            for (bb;book[a-1][bb];bb++);
            bb-=2;

             for (p=0;p<size2 ; bb--,p++){

                     book[a-1][bb] = NULL;

                      }
            }

        }
       write_if_file(temp, book, txtsize);

        getch();
    }}
//removestr --file /root/pouyan.txt --pos 2:1 -size 3 -b
void text_comparator(char cmd[])
{
    char address1[100], address2[100];
    int cmd_count = 0;
    if (cmd[0] == '\"')
    {
        for (cmd_count = 1; cmd[cmd_count] && cmd[cmd_count] != '\"'; cmd_count++)
            address1[cmd_count - 1] = cmd[cmd_count];
        address1[cmd_count - 1] = '\0';
    }
    else
    {
        for (cmd_count = 1; cmd[cmd_count] && cmd[cmd_count] != ' '; cmd_count++)
            address1[cmd_count - 1] = cmd[cmd_count];
        address1[cmd_count - 1] = '\0';
    }
    cmd_count++;
    if (cmd[cmd_count] == '\"')
    {
        cmd_count++;
        int i;
        for (i = 0; cmd[cmd_count]; cmd_count++, i++)
            address2[i] = cmd[cmd_count];
        address2[i] = '\0';
    }
    else
    {
        int i;
        cmd_count++;
        for (int i = 0; cmd[cmd_count]; cmd_count++, i++)
            address2[i] = cmd[cmd_count];
    }
    FILE *f1, *f2;
    f1 = fopen(address1, "r");
    f2 = fopen(address2, "r");
    if (f1 == NULL || f2 == NULL)
        printf("file not fond...\n");
    else
    {
        char book1[100][100], book2[100][100];
        int size1 = 0, size2 = 0;
        while (fgets(book1[size1], 100, f1))
            size1++;
        while (fgets(book2[size2], 100, f2))
            size2++;

        for (int i = 0; i < max(size1, size2); i++)
        {

            if (strcmp(book1[i], book2[i]) != 0)
            {
                printf("\n================#%d================\n", i + 1);
                printf("%s\n", book1[i]);
                printf("%s\n", book2[i]);
            }
        }
    }
}

pretree(char cmd[])
{
    int a;
    char trr[10];
    sscanf(cmd, "%s %d", trr, &a);

    tree("root", a);
}

tree(char k[], int a)
{

    int m = 0;
    if (a == 1)
    {
        DIR *d;
        struct dirent *dir;
        d = opendir(k);
        if (d)
        {
            while ((dir = readdir(d)) != NULL)
            {

                if (flag == 1)
                {

                    strcpy(armann[m], dir->d_name);
                    m++;
                }
                else if (k[4] == '/')
                    printf("-------%s\n", dir->d_name);
                else
                    printf("%s\n", dir->d_name);
            }
            closedir(d);
        }
    }
       else if (a == 2)
    {

        DIR *d;
        struct dirent *dir;
        d = opendir(k);
        if (d)
        {

            while ((dir = readdir(d)) != NULL)
            {
                printf("%s\n", dir->d_name);
                // char temp[]="root/";
                if (!strchr(dir->d_name, '.'))
                {
                    char temp[100] = "root/";
                    strcat(temp, dir->d_name);
                    tree(temp, a - 1);
                }
            }
            closedir(d);
        }
    }
    else
        printf("Invalid Depth\n");
}

grep(char cmd[])
{
    int space = 0;
    int counter = 0;
    for (int i = 0; i < strlen(cmd); i++)
    {

        if (cmd[i] == ' ')
            space++;
    }

    if (space == 2)
    {
        char ebarat[40];
        char chert[10];
        char address[50];
        sscanf(cmd, "%s %s %s", ebarat, chert, address);
        ebarat[strlen(ebarat) - 1] = '\0';

        FILE *f;
        f = fopen(address + 1, "r");
        if (f == NULL)
            printf("file not fond!\n");
        else
        {

            // printf("%s",ebarat);
            int size = 0;
            char book[100][100];
            int txtsize = 0;
            while (fgets(book[txtsize], 100, f))
                txtsize++;
            for (int i = 0; i < txtsize; i++)
            {

                if (strstr(book[i], ebarat) != 0)
                {
                    if (typec == 0 && typel == 0)
                        printf("%s: %s", address, book[i]);
                    else if (typel == 1)
                    {
                        printf("%s\n", address);
                        return 1;
                    }
                    else if (typec == 1)
                        counter++;
                }
            }
        }
        if (typec == 1)
            printf("%d\n", counter);
    }

    // 2ta file
    if (space == 3)
    {
        char ebarat[40];
        char chert[10];
        char address[50];
        char address2[50];
        sscanf(cmd, "%s %s %s %s", ebarat, chert, address, address2);
        ebarat[strlen(ebarat) - 1] = '\0';

        FILE *f;
        f = fopen(address + 1, "r");
        if (f == NULL)
            printf("file not fond!\n");
        else
        {

            int size = 0;
            char book[100][100];
            int txtsize = 0;
            while (fgets(book[txtsize], 100, f))
                txtsize++;
            for (int i = 0; i < txtsize; i++)
            {

                if (strstr(book[i], ebarat) != 0)
                {

                    if (typec == 0 && typel == 0)
                        printf("%s: %s", address, book[i]);
                    else if (typel == 1)
                    {
                        printf("%s\n", address);
                        break;
                    }
                    else if (typec == 1)
                        counter++;
                }
            }
        }
        FILE *f2;
        f2 = fopen(address2 + 1, "r");
        if (f == NULL)
            printf("file not fond!\n");
        else
        {

            int size = 0;
            char book[100][100];
            int txtsize = 0;
            while (fgets(book[txtsize], 100, f2))
                txtsize++;
            for (int i = 0; i < txtsize; i++)
            {
                if (strstr(book[i], ebarat) != 0)
                {

                    if (typec == 0 && typel == 0)
                        printf("%s: %s", address2, book[i]);
                    else if (typel == 1)
                    {
                        printf("%s\n", address2);
                        break;
                    }
                    else if (typec == 1)
                        counter++;
                }
            }
            if (typec == 1)
                printf("%d\n", counter);
        }
    }
}

autoindent(char cmd[])
{
    char temp[100];
    int size = 0;
    if (cmd[0] == '\"')
    {

        for (int i = 2; cmd[i] != '\"'; i++)
            temp[size++] = cmd[i];
    }
    else
    {
        for (int i = 1; cmd[i]; i++)
            temp[size++] = cmd[i];
    }
    temp[size] = '\0';
    // puts(temp);
    FILE *f;
    f = fopen(temp, "r");
    if (f == NULL)
    {
        printf("file not found!\n");
        return 1;
    }
    else
    {

        char book[100][100];
        int txtsize = 0;
        while (fgets(book[txtsize], 100, f))
            txtsize++;

        undosave(book);

        writeinfileauto(temp, book, txtsize);
    }
}

// auto-indent /root/pouyan.txt

// grep --str "proj" --files root/pouyan1.txt do se
// grep --str "proj" --files root/pouyan1.txt root/pouyan2.txt

void writeinfileauto(char address[], char text[][100], int size)
{
    int num;
    int k = 0;
    FILE *f;
    f = fopen(address, "w");
     int open=0;
     int close=0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; text[i][j]; j++)
        {
            if (text[i][j]!=' ' && text[i][j+1]=='(')
                {
                    fprintf(f, "%c", text[i][j]);
                    fprintf(f, "%c", " ");

                }

            if (text[i][j]=='{')
                {
                    open++;
                    fprintf(f, "%c", text[i][j]);
                    fprintf(f, "\n");
                    for (int k=0;k<open;k++)
                        fprintf(f,"%s","    ");
                }
            else if (text[i][j]=='}')
            {
                close++;
                fprintf(f, "\n");
                for (int k=0;k<open-close;k++)
                        fprintf(f,"%s","    ");
                fprintf(f, "%c", text[i][j]);

            }


            else
                fprintf(f, "%c", text[i][j]);
        }
    }
    printf("finish\n");

    fclose(f);
}
//

void undosave(char text[][100])
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)

            undomemory[i][j] = text[i][j];
    }
}

undo(char cmd[])
{

    char temp[100];
    int size = 0;
    if (cmd[0] == '\"')
    {

        for (int i = 2; cmd[i] != '\"'; i++)
            temp[size++] = cmd[i];
    }
    else
    {
        for (int i = 1; cmd[i]; i++)
            temp[size++] = cmd[i];
    }
    temp[size] = '\0';

    int i = 0, j = 0, counter = 0;
    while (undomemory[i][j])
    {
        counter++;
        i++;
    }

    FILE *f;
    f = fopen(temp, "w");
    if (f == NULL)
        printf("Error!\n");
    else
    {
        for (int i = 0; i < counter; i++)
        {

            for (int j = 0; undomemory[i][j]; j++)
            {
                fprintf(f, "%c", undomemory[i][j]);
            }
        }

        printf("Ba Movafaqiat Undo shod\n");
        fclose(f);
    }
}

int max(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}

void arman(char cmd[])
{

    if (cmd[0] == 't' && strstr(cmd, "insertstr"))
    {
        tree("root", 1);
    }

    printf("%s", armann[2]);
}

copy(char cmd[])
{

    //puts(cmd);
    char temp[1000], address[100];
    int size = 0;
    int i = 0;
    if (cmd[i] == '\"')
    {

        for (i = i + 2; cmd[i]; i++)
        {

            if (check_string(cmd, i, "\" --pos ") == 0)
            {
                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    else
    {
        for (i = i + 1; cmd[i]; i++)
        {

            if (check_string(cmd, i, " --pos ") == 0)
            {

                temp[size] = '\0';
                break;
            }
            temp[size++] = cmd[i];
        }
    }
    FILE *f;
    f = fopen(temp, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {
        char book[100][100];
        int txtsize = 0;
        while (fgets(book[txtsize], 100, f))
            txtsize++;

        while (cmd[i] < '0' || cmd[i] > '9')
            i++;

        int a = 0, b = 0, size = 0;
        while (cmd[i] && cmd[i] != ':')
            a = a * 10 + (cmd[i++] - '0');
        i++;
        while (cmd[i] >= '0' && cmd[i] <= '9')
            b = b * 10 + (cmd[i++] - '0');
        i += 7;

        while (cmd[i] && cmd[i] != ' ')
        {
            size = size * 10 + (cmd[i] - '0');
            i++;
        }

        char chr = cmd[strlen(cmd) - 1];

        // printf("%d %d %c %d",a,b,chr,size);
        a--;
        if (chr == 'f')
        {
            for (int i = 0; i < size; i++, b++)
                clipboard[i] = book[a][b];
            puts(clipboard);
        }
        else
        {

            for (int i = size - 1; i >= 0; i--, b--)
                clipboard[i] = book[a][b-1];

        }

        printf("copy shod jenab!\n");
        printf("Ebarat Zakhire shode = %s\n",clipboard);

        getch();
    }

    fclose(f);
}

paste(char cmd[])
{

    char str[1000];
    int i = 0;
    char temp[1000];
    int size = 0;
    if (cmd[i] == '\"')
    {

        for (i = i + 2; cmd[i] != '\"'; i++)
            temp[size++] = cmd[i];
        temp[size] = '\0';
    }
    else
    {
        for (i = i + 1; cmd[i]; i++)
        {
            if (cmd[i] == ' ')
                break;
            temp[size++] = cmd[i];
        }
        temp[size] = '\0';
    }

    int a = 0;
    int b = 0;
    while (cmd[i] < '0' || cmd[i] > '9')
        i++;

    // printf("%d %d",a,b);
    FILE *f;
    f = fopen(temp, "r");
    if (f == NULL)
        printf("file not fond!\n");
    else
    {
        // printf("%c",cmd[i+1]);
        char book[100][100];
        int size = 0;
        while (fgets(book[size], 100, f))
            size++;
        while (cmd[i] && cmd[i] != ':')
        {
            a = a * 10 + (cmd[i++] - '0');
        }
        a--;
        i++;
        while (cmd[i])
        {
            b = b * 10 + (cmd[i++] - '0');
        }
        undosave(book);
        writeinfileinsert(temp, book, clipboard, a, b, size);
    }
    close(f);
}
