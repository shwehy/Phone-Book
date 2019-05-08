#ifndef PHONEBOOK_H_INCLUDED
#define PHONEBOOK_H_INCLUDED

int LOAD();
int AddEntry (int);
int Modify(int);
void print(int);
int Delete(int);
void Search(int);
int Save(int);
void MultiSearch(int);
void sortingLastname(int);
void Sortingdate(int);
void Removing(int,int);

#endif // PHONEBOOK_H_INCLUDED
