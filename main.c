#include <stdio.h>
#include <stdlib.h>
#include "proj3.h"
int main()
{
 // Function make main menu
char y;

sun t=NULL;
   do{ system ("cls");

    printf("\t\t\t~~~   Maen Khdour     1171944      sec:2  ~~~~~   \n");
    printf("\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\t\t ~           Book Store Using Tree              ~\n");
    printf("\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\n\t\t\t~ please select the number of instruction:~\n");
    printf("\n\n\t\t\t ~ 0 : Read From file                          ~\n");
    printf("\n\n\t\t\t ~ 1 : Insert new Book                         ~\n");
    printf("\n\n\t\t\t ~ 2 : Search for the Book by Name of Book     ~\n");
    printf("\n\n\t\t\t ~ 3 : Search for the Book by Name of Author   ~\n");
    printf("\n\n\t\t\t ~ 4 : Update a specific Book                  ~\n");
    printf("\n\n\t\t\t ~ 5 : Delete a specific Book                  ~\n");
    printf("\n\n\t\t\t ~ 6 : List Book by Category                   ~\n");
    printf("\n\n\t\t\t ~ 7 : Print the High of tree                  ~\n");
    printf("\n\n\t\t\t ~ 8 : Save to file                            ~\n");
    printf("\n\n\t\t\t ~ 9 : exit                                    ~\n");
    printf("\n\t\t\t~ the instruction number is :");
    fflush(stdin);
    scanf("%c", &y);
    system ("cls");
     fflush(stdin);

    if(y == '0')
    { t=readData();
     printf("Read and create tree is Successfully\n");
        sleep(1);
    }
    else if(y == '1')
    {
        insertMenu(t);
        sleep(1);

    }
    else if(y == '2')
    {
       searchBook(t);
        sleep(3);
    }
    else if(y == '3')
      {
        searchAuthor(t);
         sleep(3);
    }
    else if(y== '4'){

        updateMenu(t);
        sleep(1);
    }
    else if(y== '5')
    {
        deleteBook(t);
        sleep(2);
    }
    else if(y== '6')
    {
         showList(t);
         sleep(10);
    }
        else if(y== '7')
    {
        getHigh(t);
        sleep(1);
    }
    else if(y== '8')
    {
        saveToFile(t);
        printf("The Save Done \n");
        sleep(1);
    }
    else if(y== '9')
    {
        exit(0);
    }

    }while (1);

    return 0;
}
