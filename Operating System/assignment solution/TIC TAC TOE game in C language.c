#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int completed = 0;   
char arr[3][3];
int platu = 0;
int gamedraw=0;
// int condition = 0;
// pthread_cond_t cond;
// pthread_mutex_t mutex;

void* iniboard();
void* printboard();
int checkspace(int rop, int cop);
int checkspace1(int rop, int cop);
int checkfilled();
void* playthrd();
void* compthred();
int checkwin(char ch);

void* iniboard() 
{
    for (int i = 0; i < 3; i++)
     {
        for (int j = 0; j < 3; j++)
         {
            arr[i][j] = ' ';
        }
    }
}

void* printboard() 
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            printf("%c | ", arr[i][j]);
        }
        printf("\n");
    }
}

int checkspace(int rop, int cop) 
{
    if (arr[rop][cop] == ' ') 
    {
        return 1;
    }
    printf(" enter nahi kar sakte ch he wahan \n\n");
    return 0;
}
int checkspace1(int rop, int cop) 
{
    rop-=1;
    cop-=1;
    if (arr[rop][cop] == ' ') 
    {
        return 1;
    }
    printf(" enter nahi kar sakte ch he wahan \n\n");
    return 0;
}
int checkfilled() 
{
    for (int i = 0; i < 3; i++)
     {
        for (int j = 0; j < 3; j++) 
        {
            if (arr[i][j] == ' ') 
            {
                return 0;
            }
        }
    }
    printf(" board is filled : Game Draw \n\n");

    return 1;
}

void* playthrd() 
{
    int rop, cop;
    printf("enter row & col: ");
    scanf("%d %d", &rop, &cop);

    while (rop < 1 || rop > 3 || cop < 1 || cop > 3 || !checkspace1(rop, cop))
    {
        printf("enter to sahi karo : ");
        scanf("%d %d", &rop, &cop);
    }
rop-=1;
cop-=1;
    arr[rop][cop] = 'X';

    if (checkwin('X'))
    {
         arr[rop][cop] = 'X';
        printf("you won\n");
        completed = 1;
    }
}

void* compthred() 
{
   int rop, cop;
    rop = rand() % 3;
    cop = rand() % 3;

    while (!checkspace(rop, cop))
    {
        rop = rand() % 3;
        cop = rand() % 3;
    }

    arr[rop][cop] = 'O';

    if (checkwin('O'))
    {arr[rop][cop] = 'O';
        printf("you lose :  computer won\n");
         
        completed = 1;
    }
}
int checkwin(char ch)
 {
    int i;
    
    if (arr[0][0] == ch)
       { 
        if (arr[1][1] == ch)
            {
                if (arr[2][2] == ch)
                {
                    return 1;
                }
            }
        }

    if (arr[0][2] == ch)
        {
            if (arr[1][1] == ch)
            {
                if (arr[2][0] == ch)
                {
                    return 1;
                }
            }
        }

    for (i = 0; i < 3; i++) 
    {
        if (arr[i][0] == ch)
            {
                if (arr[i][1] == ch)
                {
                    if (arr[i][2] == ch)
                    { 
                     return 1;
                    }
                }
            }
    }

    for (i = 0; i < 3; i++) 
    {
        if (arr[0][i] == ch)
           { 
            if (arr[1][i] == ch)
               { 
                if (arr[2][i] == ch)
                    {
                        return 1;
                    }
                }
            }
    }

    return 0;
}

int main() {
    srand(time(NULL));
    pthread_t player, computer;

   // pthread_mutex_init(&mutex, NULL);
    //pthread_cond_init(&cond, NULL);

    iniboard();

 while (!completed && !checkfilled())
    {
        if (platu)
        {
            printboard();
           pthread_create(&player, NULL, playthrd, NULL);

     pthread_join(player, NULL);
            platu = 0;
        }
        else
        {
            pthread_create(&computer, NULL, compthred, NULL);
pthread_join(computer, NULL);
            platu = 1;
        }
    }
    
    printboard();

    return 0;
}