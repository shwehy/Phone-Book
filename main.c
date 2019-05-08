#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Phonebook.h"
#include "Utilities.h"
int main()
{
    int contactsNumbers = LOAD();
    printf("Contact loaded sucssufully\n");
    int NewNumberofContacts=contactsNumbers,Modifycheck=0,Savecheck=1,len;
    int Deletecheck=0,Printcheck=0;
    char order[10],choiceS[10];
    while(1)
    {
        printf("\n\tHow can I help you?\n");
        printf(" 1-Search \t\t 2-Add\n 3-Delete \t\t 4-Modify\n 5-Print \t\t 6-Save\n \t\t7-Exit \n");
        printf("\nEnter number between 1 and 7\n");
        scanf("\n%[^\n]s",&order);
        len = strlen(order);
        while(!(order[0]>=49 && order[0]<=55) || len!=1)
        {
            printf("!!ERROR: Please Enter NUMBER between 1 and 7\n");
            scanf("\n%[^\n]s",&order);
            len = strlen(order);
        }
        switch(order[0])
        {
        case 49:
            do
            {
                printf("Choose the way of Search\n");
                printf("1-LastName\t\t2-MultiSearch\n");
                scanf("\n%[^\n]s",choiceS);
            }while(!validChoice(choiceS,49,50));
            if(choiceS[0] == 49)
                Search(contactsNumbers);
            else if(choiceS[0] == 50)
            {
                printf("**Multi Search**\n");
                printf("Press 'Enter' or 'Space' to skip entry\n\n");
                MultiSearch(contactsNumbers);
            }
            break;
        case 50:
            printf("***Adding***\n");
            NewNumberofContacts = AddEntry(NewNumberofContacts)+1;
            Savecheck=0;
            break;
        case 51:
            printf("**Deleteing**\n");
            Deletecheck = Delete(contactsNumbers);
            if(Deletecheck)
            {
                NewNumberofContacts=contactsNumbers-1;
                Savecheck=0;
            }
            break;
        case 52:
            printf("***Modifying***\n");
            Modifycheck = Modify(contactsNumbers);
            Savecheck=0;
            break;
        case 53:
            printf("**Printing**\n");
            Print(contactsNumbers);
            Printcheck=1;
            Savecheck=0;
            break;
        case 54:
            printf("***Saving***\n");
            if(NewNumberofContacts!=contactsNumbers || Modifycheck!=0 || Printcheck!=0)
            {
                Savecheck = Save(NewNumberofContacts);
                contactsNumbers = NewNumberofContacts;
                Modifycheck=0;
                Printcheck=0;
            }
            else
            {
                printf("You haven't made any changes\n");
                Savecheck =1;
            }
            contactsNumbers = LOAD();
            break;
        case 55:
            if(Savecheck)
            {
                printf("Goodbye\n");
                exit(0);
            }
            else
            {
                do{
                    printf("Your changes haven't been saved?\n");
                    printf("\tAre you sure you want to exit?\n");
                    printf("\t\t1-Yes\t2-No\n");
                    scanf("%s",&choiceS);
                }while(!validChoice(choiceS,49,50));
                if(choiceS[0]==49)
                {
                    printf("Goodbye\n");
                    exit(0);
                }
            }

        }
    }
    return 0;
}
