#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 40
#define MAX_SIZE 1024

struct _drzava;
typedef struct _drzava* PozD;
struct _grad;
typedef struct _grad* PozG;

typedef struct _drzava {
	char naziv_drzave[MAX];
	PozD next;
	PozG root;
} drzava;

typedef struct _grad {
	char naziv_grada[MAX];
	int broj_st;
	PozG le;
	PozG de;
} grad;

int br_drz(char* NazivDatoteke);
PozD kreiraj_drz(char* naziv_drzave);
PozG kreiraj_grad(char* naziv_grada, int broj_st);

void drz_dat(char* NazivDatoteke, int broj_drzava, PozD head);
void unesi_drz(char* buffer, PozD head);
int br_grad(char* nazivDatoteke);
PozG gradovi_dat(char* nazivDatoteke, int brojGradova, PozG root);
PozG unesi_grad(char* naziv_grada, int broj_st, PozG root);





int br_drz(char* nazivDatoteke) {
	FILE* fp = NULL;
	int brojDrzava = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(nazivDatoteke, "r");

	//if (fp == NULL) {
	//	printf("Neuspjesno otvaranje datoteke!\n");
	//	return -1;
	//}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		if (strlen(buffer) != 1)
			brojDrzava++;
	}

	fclose(fp);

	return brojDrzava;
}

void drz_dat(char* nazivDatoteke, int broj_drzava, PozD head) {
	FILE* fp = NULL;
	fp = fopen(nazivDatoteke, "r");
	char buffer[MAX_LINE] = { 0 };

	if (fp == NULL) {
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	for (int i = 0; i < brojDrzava; i++) {
		fgets(buffer, MAX_LINE, fp);
		unesi_drz(buffer, head);
	}

	fclose(fp);
}

void unesi_drz(char* buffer, PozD head) {
	PozD temp = head;
	PozD novaDrzava = NULL;
	char naziv_drzave[MAX] = { 0 };
	char nazivDatoteke[MAX_SIZE] = { 0 };
	int brojGradova = 0;

	if (sscanf(buffer, "%s %s", naziv_drzave, nazivDatoteke) != 2) {
		printf("Greska!\n");
		return -1;
	}

	novaDrzava = kreiraj_drz(naziv_drzave);

	if (novaDrzava == NULL) {
		return -1;
	}

	while (temp->next != NULL && strcmp(temp->naziv_drzave, naziv_drzave) < 0) {
		temp = temp->next;
	}

	novaDrzava->next = temp->next;
	temp->next = novaDrzava;

	brojGradova = br_grad(nazivDatoteke);
	novaDrzava->root = gradovi_dat(nazivDatoteke, brojGradova, novaDrzava->root);
}

PozD kreiraj_drz(char* nazivDrzave) {
	PozD novaDrzava = NULL;

	novaDrzava = (PoznD)malloc(sizeof(drzava));

	if (novaDrzava == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	strcpy(novaDrzava->naziv_drzave, nazivDrzave);
	novaDrzava->next = NULL;
	novaDrzava->root = NULL;

	return novaDrzava;
}



int br_grad(char* nazivDatoteke) {
	FILE* fp = NULL;
	int brojGradova = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(nazivDatoteke, "r");

	if (fp == NULL) {
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		if (strlen(buffer) != 1)
			brojGradova++;
	}

	fclose(fp);

	return brojGradova;
}


PozG gradovi_dat(char* nazivDatoteke, int brojGradova, PozG root) {
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	char nazivGrada[MAX_SIZE] = { 0 };
	int brojStanovnika = 0;

	fp = fopen(nazivDatoteke, "r");

	if (fp == NULL) {
		printf("Neuspjesno otvaranje datoteke!\n");
		return NULL;
	}

	for (int i = 0; i < brojGradova; i++) {
		fgets(buffer, MAX_LINE, fp);
		if (sscanf(buffer, "%s %d", nazivGrada, &broj_stanovnika) != 2) {
			printf("Pogreska!\n");
			return NULL;
		}
		root = unesi_grad(nazivGrada, broj_stanovnika root);
	}

	fclose(fp);

	return root;
}

PozG unesi_grad(char* naziv_grada, int broj_st, PozG root) {
	PozG current = root;
	PozG noviGrad = NULL;

	if (current == NULL) {
		noviGrad = kreiraj_grad(naziv_grada, broj_st);
		return noviGrad;
	}

	else if (brojStanovnika < current->brojStanovnika) {
		current->le = unesi_grad(naziv_grada, broj_st, current->le);
	}

	else if (brojStanovnika > current->brojStanovnika) {
		current->de = unesi_grad(naziv_grada, broj_st, current->de);
	}

	return current;
}

PozG kreiraj_grad(char* naziv_grada, int broj_st) {
	PozG noviGrad = NULL;

	noviGrad = (PozG)malloc(sizeof(grad));

	if (noviGrad == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	strcpy(noviGrad->naziv_grada, naziv_grada);
	noviGrad->broj_st = broj_st;
	noviGrad->le = NULL;
	noviGrad->de = NULL;

	return noviGrad;
}