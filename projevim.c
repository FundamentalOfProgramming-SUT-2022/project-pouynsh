#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
int main () {
int x=1;
int g=0;
int i=0;
initscr();
noecho();
start_color();
char what;
char mode[20]="NORMAL";
char cmd[100000];
char address[1000];
char textfile[100][100]={' '};
char highlight[100][100]={' '};
char c='k';
char filename[100]="NO NAME";
init_pair(1, COLOR_BLACK, COLOR_WHITE);
init_pair(2, COLOR_YELLOW, COLOR_BLACK);
init_pair(3, COLOR_CYAN, COLOR_BLACK);
init_pair(4, COLOR_RED, COLOR_BLUE);
init_pair(5,COLOR_BLACK,COLOR_WHITE);


while(1){
attron(COLOR_PAIR(2));
for (int i=0;i<LINES-3;i++){
    if (i>=g)
     mvprintw(i,0,"~");
}
attroff(COLOR_PAIR(2));
attron(COLOR_PAIR(x));
mvprintw(LINES-3,0,"%s",mode);
attroff(COLOR_PAIR(x));

attron(COLOR_PAIR(5));
mvprintw(LINES-3,8,"%s",filename);
attroff(COLOR_PAIR(5));

c=getch();
if (c== ':'){
 i=0;
  while(c!='\n'){
    c=getch();
    cmd[i]=c;
    cmd[i+1]='\0';
    mvprintw(LINES-2,0,"%s",cmd);
    
      
      i++;
     }
  for (int j=0;j<COLS; j++)
  {
    mvprintw(LINES-2,j," ");
  }
  }

  if (strstr(cmd,"open"))
  {         
          //mvprintw(4,6,"%c",cmd[i]);
          
          int w=0;
            
          for (int i=5;cmd[i];i++,w++){
              address[w]=cmd[i];
              filename[w]=cmd[i];
          }
          
          address[w-1]='\0';
          filename[w-1]='\0';

           FILE *f;
           //mvprintw(10,10,"%s",filename);
            f = fopen(address, "r");
    if (f == NULL)
    {
         f = fopen(address, "w");
    }
    else
      {    
        //mvprintw(4,6,"Hst hamchin filei");
        //root/pouyan.txt
        char book[100][100];
        int size = 0;
        while (fgets(book[size], 100, f))
                  size++;
              g=size;
            
              int k;
              for(int i=0;i<size;i++,k++){
                mvprintw(i,0,"%c",' ');
                mvprintw(i,1,"%d-",k+1);
                  for (int j=0;j<100;j++)
                      mvprintw(i,j+4,"%c",book[i][j]);
              } 
          
              k=0;
              
      } 
      
             //mvprintw(4,6,"%s",address);
  }


  if (strstr(cmd,"save"))
  {
      
            FILE *f;
            f = fopen(address, "w");
            for(int i=0;i<100;i++)
                  fprintf(f,"%s",highlight[i]);

  }

if (c==27){
    
     what=getch();
     if (what=='q'){
        mvprintw(LINES-2,0,"q");
        endwin();
        exit(0);}
    else if (what=='v')
         {
           mvprintw(LINES-2,0,"v");
           strcpy(mode,"VISUAL");
           mvprintw(LINES-3,0,"VISUAL");
           x=2;
           int a=0;
           int b=0;
           char p='l';
           move(a,b);
           while(p!=27)
           {
            p=getch();
            if (p =='a')
                 move(a,--b);
            else if (p=='d')
                 move(a,++b);
            else if (p =='w')
                 move(--a,b);
            else if (p =='s')
                 move(++a,b);
             else if (p == '\n'){
              b=0;
              move(++a,b);
              }
            else if (p==27)
            {
              for (int i=0;i<a+1;i++)
                for (int j=0;j<100;j++)
                      highlight[i][j]=textfile[i][j];
            }
            
           
         }
     
         
         }
    else if (what=='n')
         {
           mvprintw(LINES-2,0,"n");
           strcpy(mode,"NORMAL");
           x=1;
           
         }
         else if (what=='i')
         {
           mvprintw(LINES-3,0,"INSERT");
           mvprintw(LINES-2,0,"i");
           strcpy(mode,"INSERT");
           x=3;
           int a=0;
           int b=0;
           move(a,b);
           char p='l';
            while(p!=27)
           {
            p=getch();
            if (p =='a')
                 move(a,--b);
            else if (p=='d')
                 move(a,++b);
            else if (p =='w')
                 move(--a,b);
            else if (p =='s')
                 move(++a,b);
             else if (p == '\n'){
              b=0;
              move(++a,b);
              }
            else if (p==27)
                 break;  
            else{
            textfile[a][b]=p;
            mvprintw(a,b,"%c",p);
            move(a,b++);}
           }
         }
         
     else {
       mvprintw(LINES-1,0,"invalid command");
       }
}
 }


endwin();

return 0; 
}