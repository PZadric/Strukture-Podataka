#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 128

typedef struct stablo* Position;
typedef struct stablo {
	char* ime;
	Position child;
	Position sibling;
}Stablo;

typedef struct stog* pozStog;
typedef struct stog {
	Position direktorij;

	pozStog next;
	pozStog prev;
}Stog;

int NapraviDirektorij(Position);
int Meni(Position, pozStog);
int Dir(Position);
Position cd(Position, pozStog);
Position Nazad(Position, pozStog);
Position PronadiZadnji(char*, Position);
int PushStog(pozStog, Position);
Position PopStog(pozStog);
int Linija(pozStog, Position, Position);
pozStog PronadiZadnji(pozStog);

pozStog PronadiZadnji(pozStog head) {
	pozStog s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}

int NapraviDirektorij(Position currentFile) {
	Position direktorij;
	direktorij = (Position)malloc(sizeof(Stablo));
	direktorij->ime = (char*)malloc(MAX * sizeof(char));

	if (!direktorij)
		printf("Memorija nije uspjesno alocirana");

	if (currentFile->child != NULL) {
		currentFile = currentFile->child;
		while (currentFile->sibling != NULL) {
			currentFile = currentFile->sibling;
		}
		currentFile->sibling = direktorij;
	}

	else
		currentFile->child = direktorij;

	scanf(" %s", direktorij->ime);

	direktorij->sibling = NULL;
	direktorij->child = NULL;

	return 0;
}

int Dir(Position currentFile) {
	if (currentFile->child == NULL) {
		printf("Direktorij je prazan!\n");
		return 0;
	}

	currentFile = currentFile->child;

	printf("DIRECTORIES: \n");
	printf("\t- %s\n", currentFile->ime);

	while (currentFile->sibling != NULL) {
		printf("\t- %s\n", currentFile->sibling->ime);
		currentFile = currentFile->sibling;
	}

	return 0;
}

Position cd(Position currentFile, pozStog head)
{
	Position SearchedFile;
	char* imeDir;
	imeDir = (char*)malloc(MAX * sizeof(char));

	scanf("%s", imeDir);

	if (currentFile->child == NULL) {
		printf("Nema direktorija koji mozete otvoriti!\n");
		return currentFile;
	}

	SearchedFile = PronadiZadnji(imeDir, currentFile);
	if (SearchedFile == 0) {
		printf("Direktorij nije pronaden\n");
		return currentFile;
	}

	PushStog(head, currentFile);

	return SearchedFile;
}

int Meni(Position root, pozStog head) {
	Position CurrentFile = root;
	char command[MAX] = { 0 };


	printf("md <filename> - Dodaj direktorij\n");
	printf("cd <filename> - Otvori direktorij\n");
	printf("cd.. - Zatvori direktorij\n");
	printf("dir - Nabroji direktorije koji se nalaze u trenutnome\n");
	printf("exit - Izlaz\n");


	while (1) {
		Linija(head, root, CurrentFile);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			NapraviDirektorij(CurrentFile);
		}

		else if (!strcmp(command, "cd")) {
			CurrentFile = cd(CurrentFile, head);
		}

		else if (!strcmp(command, "cd..")) {
			CurrentFile = Nazad(CurrentFile, head);
		}

		else if (!strcmp(command, "dir")) {
			Dir(CurrentFile);
		}

		else if (!strcmp(command, "exit")) {
			return 1;
		}

		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}

int PushStog(pozStog head, Position direktorij) {
	pozStog q = (pozStog)malloc(sizeof(Stog));

	q->next = head->next;
	q->prev = head;
	if (head->next != NULL) {
		head->next->prev = q;
	}
	head->next = q;
	q->direktorij = direktorij;

	return 0;
}

Position PopStog(pozStog head) {
	pozStog q = (pozStog)malloc(sizeof(Stog));
	Position p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->direktorij;
	head->next = head->next->next;
	if (head->next != NULL)
		head->next->prev = head;
	free(q);

	return p;
}

Position Nazad(Position currentFile, pozStog head)
{
	Position SearchedFile;

	SearchedFile = PopStog(head);

	if (SearchedFile == NULL) {
		printf("Ne moze se izaci iz root direktorija!\n");
		SearchedFile = currentFile;
	}

	return SearchedFile;
}

int Linija(pozStog head, Position root, Position currentFile)
{
	pozStog s;

	s = PronadiZadnji(head);

	printf("\n");
	if (head->next == NULL) {
		printf("%s>", root->ime);
		return EXIT_SUCCESS;
	}

	while (s->prev != NULL) {
		printf("%s>", s->direktorij->ime);
		s = s->prev;
	}

	printf("%s>", currentFile->ime);

	return EXIT_SUCCESS;
	;
}

Position PronadiZadnji(char* name, Position currentFile) {
	if (currentFile->child == NULL) {
		printf("Direktorij je prazan!");
		return 0;
	}

	currentFile = currentFile->child;

	while (strcmp(name, currentFile->ime) != 0 && currentFile->sibling != NULL) {
		currentFile = currentFile->sibling;
	}

	if (currentFile->sibling == NULL) {
		if (strcmp(name, currentFile->ime) != 0)
			return 0;
		else
			return currentFile;
	}

	else
		return currentFile;
}

int main()
{
	Position root;
	root = (Position)malloc(sizeof(Stablo));
	root->child = NULL;
	root->sibling = NULL;
	Stog* head;
	head = (pozStog)malloc(sizeof(Stog));
	head->next = NULL;
	head->prev = NULL;
	int status = 0;
	root->ime = (char*)malloc(MAX * sizeof(char));
	root->ime = "C:";

	do {
		status = Meni(root, head);
	} while (!status);

	return 0;
}