#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilities.h"
struct date
{
    int day;
    int month;
    int year;
};
struct contact
{
    char name[30], lastname[30], address[50], phoneNumber[30], Email[30];
    struct date birthday;
};
struct contact contacts[100];
struct contact Temp= {0};
int Searched[20];
char order[10];
int
LOAD ()
{
    FILE *phonebook1;
    phonebook1 = fopen ("D:\\Downloads\\PhoneBookProject.-20190508T025817Z-001\\PhoneBookProject\\phone1.txt", "r");
    if (phonebook1 == NULL)
    {
        printf ("\nERROR!!: can't find such a file\n");
        exit (0);
    }
    else
    {
        printf ("\nFile opened sucssufully\n");
    }
    int i = 0;
    do
    {
        fscanf (phonebook1, "%[^,],", &contacts[i].name);
        fscanf (phonebook1, "%[^,],", &contacts[i].lastname);
        fscanf (phonebook1, "%d-", &contacts[i].birthday.day);
        fscanf (phonebook1, "%d-", &contacts[i].birthday.month);
        fscanf (phonebook1, "%d,", &contacts[i].birthday.year);
        fscanf (phonebook1, "%[^,],", &contacts[i].address);
        fscanf (phonebook1, "%[^,],", &contacts[i].Email);
        fscanf (phonebook1, "%s\n", &contacts[i].phoneNumber);
        i++;
    }
    while (!feof (phonebook1));
    printf ("Number of Contacts: %d\n", i);
    fclose (phonebook1);
    return i;
}
int
GetSearched (int numbers)
{
    char TobeSearched[20];
    int j = 0, i;
    printf ("Enter the LastName: ");
    scanf ("%s", TobeSearched);
    for (i = 0; i < numbers; i++)
    {
        if (strcasecmp (contacts[i].lastname, TobeSearched) == 0)
        {
            Searched[j] = i;
            j++;
        }
    }
    return j;
}

void Sortingdate (int number)
{
    struct contact temp;
    int i, j, compared;
    for (i = 0; i < number - 1; i++)
    {
        for (j = 0; j < number - i - 1; j++)
        {
            compared =
                (contacts[j].birthday.year - contacts[j + 1].birthday.year);
            if (compared < 0)
            {
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
            else if (compared == 0)
            {
                compared =
                    (contacts[j].birthday.month - contacts[j + 1].birthday.month);
                if (compared < 0)
                {
                    temp = contacts[j];
                    contacts[j] = contacts[j + 1];
                    contacts[j + 1] = temp;
                }
                else if (compared == 0)
                {
                    compared =
                        (contacts[j].birthday.day - contacts[j + 1].birthday.day);
                    if (compared < 0)
                    {
                        temp = contacts[j];
                        contacts[j] = contacts[j + 1];
                        contacts[j + 1] = temp;
                    }
                }
            }
        }
    }
}

void
sortingLastname (int number)
{
    struct contact temp;
    int i, j, compare;
    for (i = 0; i < number - 1; i++)
    {
        for (j = 0; j < number - i - 1; j++)
        {
            compare =
                strcasecmp (contacts[j].lastname, contacts[j + 1].lastname);
            if (compare > 0)
            {
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
            else if (compare == 0)
            {
                compare = strcasecmp (contacts[j].name, contacts[j + 1].name);
                if (compare > 0)
                {
                    temp = contacts[j];
                    contacts[j] = contacts[j + 1];
                    contacts[j + 1] = temp;
                }
                else if (compare == 0)
                {
                    compare =
                        strcasecmp (contacts[j].phoneNumber,
                                    contacts[j + 1].phoneNumber);
                    if (compare > 0)
                    {
                        temp = contacts[j];
                        contacts[j] = contacts[j + 1];
                        contacts[j + 1] = temp;
                    }
                }
            }
        }
    }
}

void Removing (int index, int numbers)
{
    struct contact temp;
    int i;
    for (i = index; i < numbers; i++)
    {
        temp = contacts[i];
        contacts[i] = contacts[i + 1];
        contacts[i + 1] = temp;
    }
    printf ("**Contact Removed**\n");
    printf ("\nPress save'6' to save your changes\n");

}

int AddEntry (int x)
{
    int check;

    do
    {
        printf ("First Name: ");
        scanf ("%s", &contacts[x].name);
    }
    while (!validString (contacts[x].name));
    do
    {
        printf ("Last Name: ");
        scanf ("%s", &contacts[x].lastname);
    }
    while (!validString (contacts[x].lastname));
    do
    {
        printf ("Date, Day: ");
        scanf ("%d", &contacts[x].birthday.day);
        printf ("Date, Month: ");
        scanf ("%d", &contacts[x].birthday.month);
        printf ("Date, year: ");
        scanf ("%d", &contacts[x].birthday.year);
    }
    while (!validDate
            (contacts[x].birthday.day, contacts[x].birthday.month,
             contacts[x].birthday.year));
    printf ("Address: ");
    scanf (" %[^\n]s", &contacts[x].address);
    do
    {
        printf ("Email: ");
        scanf ("%s", &contacts[x].Email);
    }
    while (!validEmail (contacts[x].Email));
    do
    {
        printf ("phoneNumber: ");
        scanf ("%s", &contacts[x].phoneNumber);
    }
    while (!validNumber (contacts[x].phoneNumber));
    printf
    ("\nA new contact is successfully added, Press Save'6' to save it.\n");
    return x;
}

int Delete (int number)
{
    int numberOfRepetetion = GetSearched (number);
    int Flag = 0, i;
    int choice;
    if (numberOfRepetetion == 0)
    {
        printf ("Contact not Found\n");
    }
    else if (numberOfRepetetion == 1)
    {
        printf ("Only one Contact with this lastname Found\n");
        printf ("\t\t First name: %s\n", contacts[Searched[0]].name);
        printf ("\t\t Last name: %s\n", contacts[Searched[0]].lastname);
        printf ("\t\t Date: %d-%d-%d \n", contacts[Searched[0]].birthday.day,
                contacts[Searched[0]].birthday.month,
                contacts[Searched[0]].birthday.year);
        printf ("\t\t Address: %s\n", contacts[Searched[0]].address);
        printf ("\t\t Email: %s\n", contacts[Searched[0]].Email);
        printf ("\t\t phoneNumber: %s\n", contacts[Searched[0]].phoneNumber);

        printf ("\n\tAre you sure you want to Delete?\n");
        do
        {
            printf ("\t\t1-Yes\t2-No\n");
            scanf("\n%[^\n]s",&order);
        }
        while(!validChoice(order,49,50));
        if (order[0] == 49)
        {
            Removing (Searched[0], number);
            return 1;
        }
    }
    else
    {
        char TobeSearched[20];
        printf ("Enter the FirstName: ");
        scanf ("%s", TobeSearched);
        for (i = 0; i < numberOfRepetetion; i++)
        {
            if (strcmp (contacts[Searched[i]].name, TobeSearched) == 0)
            {
                printf ("Contact Found\n");
                printf ("\t\t First name: %s\n", contacts[Searched[i]].name);
                printf ("\t\t Last name: %s\n", contacts[Searched[i]].lastname);
                printf ("\t\t Date: %d-%d-%d \n",
                        contacts[Searched[i]].birthday.day,
                        contacts[Searched[i]].birthday.month,
                        contacts[Searched[i]].birthday.year);
                printf ("\t\t Address: %s\n", contacts[Searched[i]].address);
                printf ("\t\t Email: %s\n", contacts[Searched[i]].Email);
                printf ("\t\t phoneNumber: %s\n",
                        contacts[Searched[i]].phoneNumber);
                printf ("\n\tAre you sure you want to Delete?\n");
                do
                {
                    printf ("\t\t1-Yes\t2-No\n");
                    scanf("\n%[^\n]s",&order);
                }
                while(!validChoice(order,49,50));


                if (order[0] == 49)
                {
                    if (Searched[i] == number)
                    {
                        return 1;
                    }
                    Removing (Searched[i], number);
                    return 1;
                }
                Flag = 1;
            }
        }
        if (Flag != 1)
        {
            printf ("Contact not Found\n");
        }
    }
    return 0;
}

int
Modify (int number)
{
    char tempdate[10],tempmonth[10],tempyear[10];
    int numberOfRepetetion = GetSearched (number);
    int i,nb;
    if (numberOfRepetetion != 0)
    {
        for (i = 0; i < numberOfRepetetion; i++)
        {
            printf ("\nContact number[%d]\n", i + 1);
            printf ("\t\t First name: %s\n", contacts[Searched[i]].name);
            printf ("\t\t Last name: %s\n", contacts[Searched[i]].lastname);
            printf ("\t\t Date: %d-%d-%d \n",
                    contacts[Searched[i]].birthday.day,
                    contacts[Searched[i]].birthday.month,
                    contacts[Searched[i]].birthday.year);
            printf ("\t\t Address: %s\n", contacts[Searched[i]].address);
            printf ("\t\t Email: %s\n", contacts[Searched[i]].Email);
            printf ("\t\t phoneNumber: %s\n",
                    contacts[Searched[i]].phoneNumber);
        }
        if (numberOfRepetetion > 1)
        {
            do
            {
                printf ("Enter number of contact[1:%d] you want to Modify\n",
                        numberOfRepetetion);
                scanf("\n%[^\n]s",&order);
            }
            while(!validChoice(order,49,48+numberOfRepetetion));
            nb = order[0] - '0';
        }
        else
        {
            nb = 0;
        }
        do
        {
            printf ("Modify the First name: ");
            scanf ("%s", contacts[Searched[nb]].name);
        }
        while (!validString (contacts[Searched[nb]].name));
        do
        {
            printf ("Modify the Last name: ");
            scanf ("%s", contacts[Searched[nb]].lastname);
        }
        while (!validString (contacts[Searched[nb]].name));
        do
        {
            printf ("Modify the Date, Day: ");
            scanf ("%d", &contacts[Searched[nb]].birthday.day);
            printf ("Modify the Date, Month: ");
            scanf ("%d", &contacts[Searched[nb]].birthday.month);
            printf ("Modify the Date, Year: ");
            scanf ("%d", &contacts[Searched[nb]].birthday.year);
    }while (!validDate
                (contacts[Searched[nb]].birthday.day,
                 contacts[Searched[nb]].birthday.month,
                 contacts[Searched[nb]].birthday.year));
        //
        printf ("Modify the Address: ");
        scanf (" %[^\n]s", contacts[Searched[nb]].address);
        do
        {
            printf ("Modify the Email: ");
            scanf ("%s", contacts[Searched[nb]].Email);
        }
        while (!validEmail (contacts[Searched[nb]].Email));
        do
        {
            printf ("Modify the phoneNumber: ");
            scanf ("%s", contacts[Searched[nb]].phoneNumber);
        }
        while (!validNumber (contacts[Searched[nb]].phoneNumber));
        printf ("\nPress save'6' to save your changes\n");
    }
    else
    {
        printf ("This name is not saved\n");
    }
    return 1;
}



void
Print (int number)
{
    int i;
    do
    {
        printf ("Select the way of sorting:\n\t1-Alphabetics\t2-Birth dates\n");
        scanf("\n%[^\n]s",&order);
    }
    while(!validChoice(order,49,50));
    if (order[0] == 49)
    {
        sortingLastname (number);
        for (i = 0; i < number; i++)
        {
            printf ("\nContact number[%d]\n", i + 1);
            printf ("\t\t First name: %s\n", contacts[i].name);
            printf ("\t\t Last name: %s\n", contacts[i].lastname);
            printf ("\t\t Date: %d-%d-%d \n", contacts[i].birthday.day,
                    contacts[i].birthday.month, contacts[i].birthday.year);
            printf ("\t\t Address: %s\n", contacts[i].address);
            printf ("\t\t Email: %s\n", contacts[i].Email);
            printf ("\t\t phoneNumber: %s\n", contacts[i].phoneNumber);
        }

    }

    else if (order[0] == 50)
    {
        Sortingdate (number);
        for (i = 0; i < number; i++)
        {
            printf ("\nContact number[%d]\n", i + 1);
            printf ("\t\t First name: %s\n", contacts[i].name);
            printf ("\t\t Last name: %s\n", contacts[i].lastname);
            printf ("\t\t Date: %d-%d-%d \n", contacts[i].birthday.day,
                    contacts[i].birthday.month, contacts[i].birthday.year);
            printf ("\t\t Address: %s\n", contacts[i].address);
            printf ("\t\t Email: %s\n", contacts[i].Email);
            printf ("\t\t phoneNumber: %s\n", contacts[i].phoneNumber);
        }

    }

    printf ("\nPress save '6' to save your changes\n");
}


int
Save (int number)
{
    int i;
    FILE *phonebook1 =
        fopen ("/Users/MahmoudElkarargy/Desktop/DOOOOOOOOONEEEE\!\!\!/Finalll_ali/phone1.txt", "w");
    for (i = 0; i < number; i++)
    {
        if (i == 0)
        {
            fprintf (phonebook1, "%s,", contacts[i].name);
        }
        else
        {
            fprintf (phonebook1, "\n%s,", contacts[i].name);
        }
        fprintf (phonebook1, "%s,", contacts[i].lastname);
        fprintf (phonebook1, "%d-", contacts[i].birthday.day);
        fprintf (phonebook1, "%d-", contacts[i].birthday.month);
        fprintf (phonebook1, "%d,", contacts[i].birthday.year);
        fprintf (phonebook1, "%s,", contacts[i].address);
        fprintf (phonebook1, "%s,", contacts[i].Email);
        fprintf (phonebook1, "%s", contacts[i].phoneNumber);
    }
    fclose (phonebook1);
    printf ("All changes have been saved\n");
    return 1;
}

void
Search (int numbers)
{
    int numberOfRepetetion = GetSearched (numbers);
    int i;
    if (numberOfRepetetion != 0)
    {
        for (i = 0; i < numberOfRepetetion; i++)
        {
            printf ("\nContact number[%d]\n", i + 1);
            printf ("\t\t First name: %s\n", contacts[Searched[i]].name);
            printf ("\t\t Last name: %s\n", contacts[Searched[i]].lastname);
            printf ("\t\t Date: %d-%d-%d \n", contacts[i].birthday.day,contacts[i].birthday.month, contacts[i].birthday.year);
            printf ("\t\t Address: %s\n", contacts[Searched[i]].address);
            printf ("\t\t Email: %s\n", contacts[Searched[i]].Email);
            printf ("\t\t phoneNumber: %s\n",
                    contacts[Searched[i]].phoneNumber);
        }
    }
    else
    {
        printf ("This name is not saved\n");
    }
}
void MultiSearch(int number)
{
    int Flag[6] = {0},i,j=0,k;
    int Multi[20];
    int firstThing=1;
    char TempDay[20]= {0},TempMonth[20]= {0},TempYear[20]= {0};
    int aha;
    printf ("Enter the first name: ");
    fflush (stdin);
    scanf ("%[^\n]s",Temp.name);
    fflush (stdin);
    printf ("Enter the last Name: ");
    scanf ("%[^\n]s", Temp.lastname);
    fflush (stdin);
    printf ("Enter Day of birth: ");
    scanf ("%[^\n]s",TempDay);
    fflush (stdin);
    if (TempDay[0]==32||TempDay[0]==0)
    {
        fflush(stdin);
        Flag[2] = 1;
    }
    else
    {
        fflush (stdin);
        printf ("Enter Month of birth: ");
        scanf ("%[^\n]s", TempMonth);
        if (TempMonth[0]==32||TempMonth[0]==0)
        {
            Flag[2] = 1;
        }
        else
        {
            fflush (stdin);
            printf ("Enter Year of birth: ");
            scanf ("%[^\n]s",TempYear);
            if (TempYear[0]==32||TempYear[0]==0)
            {
                fflush (stdin);
                Flag[2] = 1;
            }
            else
            {
                Temp.birthday.day = atoi(TempDay);
                Temp.birthday.month = atoi(TempMonth);
                Temp.birthday.year = atoi(TempYear);
            }
        }
    }
    fflush(stdin);
    printf ("Enter the Address: ");
    scanf ("%[^\n]s", Temp.address);
    fflush (stdin);
    printf ("Enter the Email: ");
    scanf ("%[^\n]s", Temp.Email);
    fflush (stdin);
    printf ("Enter the phone number: ");
    scanf ("%[^\n]s", Temp.phoneNumber);
    fflush (stdin);
    int UpdateNumbers = number;
    if(Temp.name[0]==32||Temp.name[0]==0)
    {
        Flag[0] = 1;
    }
    if(Temp.lastname[0]==32||Temp.lastname[0]==0)
    {
        Flag[1] = 1;
    }
    if(Temp.address[0]==32||Temp.address[0]==0)
    {
        Flag[3] = 1;
    }
    if(Temp.Email[0]==32||Temp.Email[0]==0)
    {
        Flag[4] = 1;
    }
    if(Temp.phoneNumber[0]==32||Temp.phoneNumber[0]==0)
    {
        Flag[5] = 1;
    }
    for(k=0; k<6; k++)
    {
        if(Flag[k])
        {
            continue;
        }
        else
        {
            if(!Flag[0]&&k==0)
            {
                for (i=0; i<number; i++)
                {
                    if (strcasecmp(contacts[i].name,Temp.name) == 0)
                    {
                        Multi[j] = i;
                        j++;
                    }
                }
                number = j;
                firstThing =0;
            }
            else if(!Flag[1]&&k==1)
            {
                j=0;
                if(firstThing)
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[i].lastname,Temp.lastname) == 0)
                        {
                            Multi[j] = i;
                            j++;
                        }
                    }
                    number = j;
                    firstThing=0;

                }
                else
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[Multi[i]].lastname,Temp.lastname) == 0)
                        {
                            Multi[j] = Multi[i];
                            j++;
                        }
                    }
                    number =j;
                }
//
                firstThing =0;
            }
            else if(!Flag[2]&&k==2)
            {
                j=0;
                if(firstThing)
                {
                    for (i=0; i<number; i++)
                    {
                        if (contacts[i].birthday.day == Temp.birthday.day && contacts[i].birthday.month == Temp.birthday.month && contacts[i].birthday.year == Temp.birthday.year)
                        {
                            Multi[j] = i;
                            j++;
                        }
                    }
                    number = j;
                    firstThing=0;

                }
                else
                {
                    for (i=0; i<number; i++)
                    {
                        if (contacts[Multi[i]].birthday.day == Temp.birthday.day && contacts[Multi[i]].birthday.month == Temp.birthday.month && contacts[Multi[i]].birthday.year == Temp.birthday.year)
                        {
                            Multi[j] = Multi[i];
                            j++;
                        }
                    }
                    number =j;
                }
                firstThing =0;
            }
            else if(!Flag[3]&&k==3)
            {
                j=0;
                if(firstThing)
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[i].address,Temp.address) == 0)
                        {
                            Multi[j] = i;
                            j++;
                        }
                    }

                    number = j;
                    firstThing=0;
                }
                else
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[Multi[i]].address,Temp.address) == 0)
                        {
                            Multi[j] = Multi[i];
                            j++;
                        }
                    }
                    number =j;
                    firstThing =0;
                }

            }
            else if(!Flag[4]&&k==4)
            {
                j=0;
                if(firstThing)
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[i].Email,Temp.Email) == 0)
                        {
                            Multi[j] = i;
                            j++;
                        }
                    }
                    number = j;
                    firstThing=0;

                }
                else
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[Multi[i]].Email,Temp.Email) == 0)
                        {
                            Multi[j] = Multi[i];
                            j++;
                        }
                    }
                    number =j;
                    firstThing =0;
                }

            }
            else if(!Flag[5]&&k==5)
            {
                j=0;
                if(firstThing)
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[i].phoneNumber,Temp.phoneNumber) == 0)
                        {
                            Multi[j] = i;
                            j++;
                        }
                    }
                    number = j;
                    firstThing=0;
                }
                else
                {
                    for (i=0; i<number; i++)
                    {
                        if (strcasecmp(contacts[Multi[i]].phoneNumber,Temp.phoneNumber) == 0)
                        {
                            Multi[j] = Multi[i];
                            j++;
                        }
                    }
                    number =j;
                    firstThing =0;
                }
            }
        }
    }
    if(number==UpdateNumbers||number==0)
    {
        printf("Contact not found\n");
    }
    else
    {
        for(i=0; i<number; i++)
        {
            printf ("\nContact number[%d]\n", i + 1);
            printf ("\t\t First name: %s\n", contacts[Multi[i]].name);
            printf ("\t\t Last name: %s\n", contacts[Multi[i]].lastname);
            printf ("\t\t Date: %d-%d-%d \n", contacts[Multi[i]].birthday.day,contacts[Multi[i]].birthday.month, contacts[Multi[i]].birthday.year);
            printf ("\t\t Address: %s\n", contacts[Multi[i]].address);
            printf ("\t\t Email: %s\n", contacts[Multi[i]].Email);
            printf ("\t\t phoneNumber: %s\n",contacts[Multi[i]].phoneNumber);
        }
    }
}
