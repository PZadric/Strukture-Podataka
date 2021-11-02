#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 50
#define VEL 1024


struct _person;
typedef struct _person* Position;
typedef struct _person {

	char name[MAX];
	char surname[MAX];
	int DatumRodjenja;
	
	Position next;

}Person;

typedef struct {
	char name[MAX];
	char surname[MAX];
	int DatumRodjenja;
	Position next;
} Sortirana;

Position CreatePer(char* name, char* surname, int DatumRodjenja);

int PreppandList(Position Head, char* name, char* surname, int DatumRodjenja);
int InsertAfter(Position position, Position person);
int PrintList(Position first);
int AppandList(Position Head, char* name, char* surname, int DatumRodjenja);

Position FindLast(Position Head);
Position FindBySurname(Position first, char* surname);
Position deleteEl(Position head, char* surname);
Position FindBefore(Position first, char* surname);

int AddAfterEl(Position Head, char* sur, char* name, char* surname, int DatumRodjenja);
int AddBeforeEl(Position Head, char* sur, char* name, char* surname, int DatumRodjenja);
int InsertBefore(Position position, Position person, char* sur);
int printInDat(Position first, char* nazivDat);
int ProcitajIzDat(char* nazivDat);
void InsertSort(Position head, char* name, char* surname, int DatumRodjenja);
Position FindPrev(Position head, Position el);
int IspisDatoteke(char* imeDat);


int main(int argc, char** argv)
	{

	Person Head = { .name = {0}, .surname = {0}, .DatumRodjenja = 0, .next = NULL };
	Sortirana head = { .name = {0}, .surname = {0}, .DatumRodjenja = 0, .next = NULL };
	Position p = &Head;
	Position s = &head;
	Position temp = NULL;
	char name[MAX], surname[MAX], sur[MAX];
	int DatumRodjenja, br, odabir;


printf("\nUnesi podatke ososbe: ");
scanf("%s", name);
scanf("%s", surname);
scanf("%d", &DatumRodjenja);
	if (PreppandList(p, name, surname, DatumRodjenja) == 1)
		printf("Neuspjesno dodavanje elemenata!\n");
		InsertSort(s, name, surname, DatumRodjenja);

			printf("\nUnesi osobu: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &DatumRodjenja);
			if (AppandList(p, name, surname, DatumRodjenja) == 1)
				printf("\nNeuspjesno dodavanje elemenata!\n");
			InsertSort(s, name, surname, DatumRodjenja);

			printf("\nIspis liste: \n");
			PrintList(p->next);

			printf("\nUnesi prezime: ");
			scanf("%s", surname);
			temp = FindBySurname(p, surname);
			if (temp)	
				printf("\nOsoba:\n %s %s %d", temp->name, temp->surname, temp->DatumRodjenja);
			else
				printf("\nOsobe nema na listi.\n");

			printf("\nKoji element zelite obrisati?\n");
			scanf("%s", surname);
			deleteEl(p, surname);
			deleteEl(s, surname);

			printf("\nUnesite prezime osobe iza koje zelite dodati novi element:");
			scanf("%s", sur);
			printf("\nUnesite podatke o osobi: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &DatumRodjenja);
			if (AddAfterEl(p, sur, name, surname, DatumRodjenja) == 1)
				printf("\nNeuspiješno dodavanje elementa!\n");
			InsertSort(s, name, surname, DatumRodjenja);

			printf("\nUnesite prezime osobe ispred koje zelite dodati novi element:");
			scanf("%s", sur);
			printf("\nUnesite podatke o osobi: ");
			scanf("%s", name);
			scanf("%s", surname);
			scanf("%d", &DatumRodjenja);
			if (AddBeforeEl(p, sur, name, surname, DatumRodjenja) == 1)
				printf("Neuspiješno dodavanje elementa!\n");
			InsertSort(s, name, surname, DatumRodjenja);

			printInDat(p->next, "lista.txt");


			br = ProcitajIzDat("lista.txt");
			IspisDatoteke("lista.txt");


			printf("Ispis sortirane liste: \n");
			PrintList(s->next);

	}


int PreppandList(Position Head, char* name, char* surname, int DatumRodjenja)
{
	Position newPer = NULL;
	newPer = CreatePer(name, surname, DatumRodjenja);
	if (!newPer)
		return 1;

	InsertAfter(Head, newPer);
	
	return EXIT_SUCCESS;

}

Position CreatePer(char* name, char* surname, int DatumRodjenja)
{
	Position newPer = NULL;
	newPer = (Position)malloc(sizeof(Person));
	if (!newPer)
	{
		perror("Cant allocate memory!\n");
		return NULL;
	}
	strcpy(newPer->name, name);
	strcpy(newPer->surname, surname);
	newPer->DatumRodjenja = DatumRodjenja;
	newPer->next = NULL;

	return newPer;

}

int InsertAfter(Position position, Position person)
{
	person->next = position->next;
	position->next = person;

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;

	while (temp)
	{
		printf("%s %s %d\n", temp->surname, temp->name, temp->DatumRodjenja);
		temp = temp->next;
	}

	return EXIT_SUCCESS;

}

int AppandList(Position Head, char* name, char* surname, int DatumRodjenja)
{
	
	Position last = NULL;
	Position newPer = NULL;

	newPer = CreatePer(name, surname, DatumRodjenja);
	if (!newPer)
		return 1;

	last = FindLast(Head);

	InsertAfter(last, newPer);

	return EXIT_SUCCESS;

	

	

}

Position FindLast(Position Head) 
{
	Position temp = Head;

	while (temp->next)
	{
		temp = temp->next;
	}

	return temp;

}

Position FindBySurname(Position first, char* surname)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
			return temp;

		temp = temp->next;

	}

	return NULL;
}

Position deleteEl(Position head, char* surname)
{
	Position before = NULL;
	Position elem = NULL;

	before = FindBefore(head, surname);
	if (before == 0)
		printf("Osobe nema na listi!\n");
	else
	{
		elem = before->next;
		before->next = elem->next;
	}

	return NULL;
}

Position FindPrev(Position head, Position el)
{
	Position temp = head;

	while (temp->next != el)
		temp = temp->next;

	return temp;

	
}

int AddAfterEl(Position Head, char* sur, char* name, char* surname, int DatumRodjenja)
{
	Position newP = NULL;
	Position position = NULL;

	newP = CreatePer(name, surname, DatumRodjenja);
	if (!newP)
		return 1;

	
	if (FindBySurname(Head->next, sur) != NULL)
		position = FindBySurname(Head->next, sur);
	else
		return 1;

		
	InsertAfter(position, newP);

}

int AddBeforeEl(Position Head, char* sur, char* name, char* surname, int DatumRodjenja)
{
	Position newPer = NULL;
	Position position = NULL;
	

	newPer = CreatePer(name, surname, DatumRodjenja);
	if (!newPer)
		return 1;


	if (FindBefore(Head, sur) != NULL)
		position = FindBefore(Head, sur);
	else
		return 1;



	InsertAfter(position, newPer);
		
}

int InsertBefore(Position position, Position person, char* sur)
{
	
	
	person->next = position->next;
	position->next = person;

	return EXIT_SUCCESS;
}

int printInDat(Position first, char* nazivDat)
{
	FILE* fp = NULL;
	fp = fopen(nazivDat, "w");
	Position temp = first;
	if (!fp)
	{
		printf("Neuspijesno otvaranje datoteke!\n");
		return 1;
	}

	while (temp)
	{
		fprintf(fp, "%s %s %d\n", temp->name, temp->surname, temp->DatumRodjenja);
		temp = temp->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int ProcitajIzDat(char* nazivDat)
{
	FILE* fp = NULL;
	char niz[MAX] = { 0 };
	int br = 0;
	fp = fopen(nazivDat, "r");
	if (!fp)
	{
		printf("Neuspijesno otvaranje datoteke!\n");
		return 1;
	}

	while (!(feof(fp)))
	{
		fgets(niz, VEL, fp);
		br++;
	}
	fclose(fp);

	return br;

}


Position FindBefore(Position first, char* surname)
{
	Position temp = first;

	for (temp; temp->next; temp = temp->next) {
		if (!strcmp(surname, temp->next->surname)) {
			return temp;
		}
	}

	return NULL;

}

void InsertSort(Position head, char* name, char* surname, int DatumRodjenja)
{
	Position person = NULL;

	person = CreatePer(name, surname, DatumRodjenja);
	if (!person)
		return 1;
	Position before = NULL;
	Position temp = head->next;

	if (!temp)
	{
		InsertAfter(head, person);
	}
	else
	{
		while (temp && strcmp(surname, temp->surname))
			temp = temp->next;

		before = FindPrev(head, temp);
		InsertAfter(before, person);
	}

	return EXIT_SUCCESS;
}

int IspisDatoteke(char* imeDat)
{
	FILE* fp = NULL;
	char buffer;
	fp = fopen(imeDat, "r");
	if (!fp)
		return 1;

	while (!feof(fp))
	{
		buffer = fgetc(fp);
		printf("%c", buffer);
	}
	fclose(fp);

	return EXIT_SUCCESS;
}
