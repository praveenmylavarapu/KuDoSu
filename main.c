/*  KuDoSu, the Sudoku solver and game
                                             -> By Sai Praveen Mylavarapu    */

#include<stdio.h>
#include<time.h>
#include "rlutil.h"


struct winner       // For leader boards
{
    int s;
    char name[20];
}w;

void solve();
void leaderboards();
void play();

void printsudoku(int n[10][10])     // A function to print Sudoku
{
    setColor(GREEN);
    int i,j,k;
    printf("\n\n\t");
    for(k=0;k<44;k++)
        printf("-");
    printf("\n");
    for(i=1;i<10;i++)
    {
        printf("\t");
        for(j=1;j<10;j++)
        {
            if(j==1)
                printf("|");
            else
                printf(" ");

            if(n[i][j]==0)
            {
                setColor(RED);
                printf(" ? ");
                setColor(GREEN);
            }
            else
            {
                setColor(WHITE);
                printf(" %d ", n[i][j]);
                setColor(GREEN);
            }

            if(j%3==0)
                printf(" | ");

            if(i%3==0 && j==9)
            {
                printf("\n\t|");
                for(k=0;k<42;k++)
                    printf("-");
                printf("|");
            }
        }
        if(i<9)
            printf("\n\t|            |              |              |\n");
    }
    printf("\n\n");
    setColor(WHITE);
}


void menu()     // Displays main menu
{
    setColor(WHITE);
    int option;
    printf("\n\n\n1. Play\n\n2. Leader boards\n\n3. Solution for a Sudoku\n\n4. Exit\n\t\t\t\t -> ");
    scanf("%d",&option);
    system("cls");

    switch(option)
    {
    case 1: play();          break;
    case 2: leaderboards();  break;
    case 3: solve();         break;
    case 4:                  break;
    default:printf("\nInvalid input\n");
            menu();
    }
}


int main()
{
    setColor(YELLOW);
    printf("\n\t\t\t<<<  Welcome to KuDoSu  >>>\n");
    menu();
    return 0;
}

void solve()
{
    int n[10][10]={},i,j,key=1,value=0,c=0;
    char option;
    FILE *fp;

    printf("\n\t\tSolve a Sudoku :- \n\n1. Enter the inputs row wise and enter 0 for unknown:\n\n2. Get from sudoku.txt file\n\n\t\t->");
lop:    scanf("%d", &i);

    switch(i)       // Getting input, an unsolved Sudoku
    {
        case 1:     for(i=1;i<10;i++)
                    {
                        for(j=1;j<10;j++)
                        {
                            printf("Enter (%d,%d) = ",i,j);
                            scanf("%d",&n[i][j]);
                        }
                    }

                    break;
        case 2:

                    fp=fopen("sudoku.txt","r");
                    for(i=1;i<10;i++)
                    {
                        for(j=1;j<10;j++)
                        {
                            fscanf(fp,"%d",&n[i][j]);
                        }
                    }
                    fclose(fp);

                    break;

        default:    goto lop;

    }

l1:
    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
            if(n[i][j]<0 || n[i][j]>9)
            {
                printf("Re enter (%d,%d) = ",i,j);
                scanf("%d",&n[i][j]);
            }
        }
    }

    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
            if(n[i][j]==0)
                c++;
        }
    }

    system("cls");
    printf("Your given Sudoku is...\n");
    printsudoku(n);
    printf("Number of unknowns = %d\n", c);
    c=0;
    choice:  printf("\nDo you want to make any changes? (y/n) - ");

    scanf("%*c%c",&option);

    switch(option)
    {
    case 'y':
    case 'Y':

wre:            printf("Where (i,j) = ");
                scanf("%d,%d",&i,&j);
                if(i<1 || i>9 || j<1 || j>9)
                {
                    printf("\nInvalid input\n");
                    goto wre;
                }
                printf("New value  = ");
                scanf("%d",&n[i][j]);
                goto l1;
                break;

    case 'n':
    case 'N':
        break;

    default:    goto choice;

    }



    int checkpossible(int n[10][10],int x, int y)   // Function to check possible values in (x,y) cell
    {
        int i,j,k=1,b1,b2,l,possvals[10];

        for(i=0;i<10;i++)    // 1 to 9
            possvals[i]=i;


        for(i=1;i<10;i++)   // row check
        {
            for(l=1;l<=9;l++)
            {
                if(n[i][y]==l)
                {
                    possvals[l]=0;
                    break;
                }
            }

        }


        for(j=1;j<10;j++)   // column check
        {
            for(l=1;l<=9;l++)
            {
                if(n[x][j]==l)
                {
                    possvals[l]=0;
                    break;
                }
            }
        }


                            // finding box and checking that box
        b1= 1+(x-1)/3;
        b2= 1+(y-1)/3;

        if(b2==2)
            b2=4;

        else if(b2==3)
            b2=7;


        if(b1==2)
            b1=4;
        else if(b1==3)
            b1=7;

        for(i=b1; i<(b1+3) ;i++)
        {
            for(j=b2; j<(b2+3) ; j++)
            {
                for(l=1;l<=9;l++)
                {
                    if(n[i][j]==l)
                    {
                        possvals[l]=0;
                    }
                }
            }
        }

        for(i=0;i<10;i++)
        {
            if(possvals[i]!=0)
            {
                value=possvals[i];
                k++;
                break;
            }
        }

        return (--k);   // Returns number of possible values
    }

    while(key!=0)
    {
        key=0;

        for(i=1;i<10;i++)           // Checking all the 81 elements
        {
            for(j=1;j<10;j++)
            {
                if( n[i][j]==0 && checkpossible(n,i,j)==1 )     // If the element is unknown and there's only one possible, fill it.
                {
                    n[i][j]=value;
                    c++;
                }
            }
        }

        for(i=1;i<10;i++)           //If all elements are filled, come out of the loop. Else, repeat all the processes again.
        {
            for(j=1;j<10;j++)
            {
                if(n[i][j]==0)
                {
                    key=1;
                    break;
                }
            }

            if(key==1)
                break;
        }
    }


    system("cls");

    printf("      Voila! Sudoku Solved! Here it is.....\n");
    printsudoku(n);
    printf("Number of elements found = %d\n\n", c);
    menu();

}


void leaderboards()     // Displaying leader boards text file
{
    FILE *fp;
    setColor(YELLOW);
    fp=fopen("Leaderboards.txt","r");
    printf("\n\t\t<<<---   KuDoSu Leader boards   --->>>\n\n\t");
    setColor(GREEN);
    printf("Name\t\t\t\tTime\n");
    setColor(CYAN);
    while(!feof(fp))
    {
        fscanf(fp,"%d%s",&w.s,w.name);
        printf("\n\t%s\t\t\t\t%d\n",w.name,w.s);
    }

    fclose(fp);
    printf("\n\n\n");
    setColor(LIGHTGREEN);
    menu();
}

void play()
{

    int n[10][10]={},m[10][10]={},i,j,k,l=1;
    char opt;
    time_t s1,s2;
    FILE *fp;

    fp=fopen("sudoku.txt","r");     // n is sudoku to be solved and m is answer
    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
            fscanf(fp,"%d",&n[i][j]);
        }
    }
    fclose(fp);

    fp=fopen("sudoku_main.txt","r");
    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
            fscanf(fp,"%d",&m[i][j]);
        }
    }
    fclose(fp);

    s1=time(NULL);
    printf("\nSolve this..\n\n");
    printsudoku(n);

sol:    //Getting solutions

    printf("\n\nEnter solutions:\n");

    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
            if(l)
            {
                if(n[i][j]==0)
                {
                    printf("\n(%d,%d) = ",i,j);
                    scanf("%d",&n[i][j]);
                }
            }
            else
            {
                    printf("\n(%d,%d) = ",i,j);
                    scanf("%d",&n[i][j]);
            }
        }
    }



    s2 = time(NULL);
    system("cls");
    printf("Your solved Sudoku is:\n");
    printsudoku(n);

    for(i=1;i<10;i++)
    {
        for(j=1;j<10;j++)
        {
                if(n[i][j]!=m[i][j])
                {
                    k=0;
                    printf("\nWrong Answer\n");
                    break;
                }
        }
        if(k==0)
                    break;
    }

    if(k)           // Adding name to leader board if it's correct answer.
    {
        w.s = s2-s1;
        printf("\n\nCongratulations!!!!! Correct answer!!!\n\nTime taken to solve = %d seconds\n",w.s);
        printf("\nPlease enter your name for leader boards : ");
        scanf("%s",w.name);
        system("cls");
        fp=fopen("Leaderboards.txt","a+");
        fprintf(fp," %d ",w.s);
        fprintf(fp,w.name);
        fclose(fp);
    }
    else        // Option to try again if wrong
    {
        chs: printf("\nWanna try again? (y/n): ");
        scanf("%*c%c", &opt);

        switch(opt)            // Displaying correct answer if the user dosen't want to repeat
        {
            case 'Y':
            case 'y':   l=0;
                        goto sol;
                        break;
            case 'N':
            case 'n':   system("cls");
                        printf("\nCorrect answer is... \n\n");
                        printsudoku(m);
                        break;

            default: goto chs;
        }
    }


    menu();

}
