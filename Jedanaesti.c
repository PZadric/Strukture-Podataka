#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX_LINE 1024
#define HASH 11

struct Cvor;
typedef struct Cvor* Pozicija;
struct _Cvor;
typedef struct _Cvor* Stablo;
struct _HashTablica;
typedef struct _HashTablica* HashTablicaP;

typedef struct Cvor {
	char ime[MAX_LINE];
	Pozicija root;
	Pozicija next;
}_Lista;

typedef struct _Cvor {
	char ime[MAX_LINE];
	int broj;
	Stablo lijevo;
	Stablo desno;
}_Stablo;

typedef struct _HashTablica
{
	int velicina;
	Pozicija tablica;
}_Hash;

Stablo Insert(Stablo trenutni, Stablo NoviEl);
Stablo StvoriNoviElement(char* ime, int broj);
int IzStablaUListu(Stablo B, Pozicija Lista);
int UnosIzDatoteke(HashTablicaP P, char* drzava);
Pozicija StvoriElementListe(Pozicija P, char* ime);
int Pronadi(char* drzava, int brojStan, Pozicija P);
int ProcitajIzDat(Pozicija P);
int Ispis(Pozicija P);
int DodajUStablo(Pozicija Head, char* imeDat);
int IspisGrada(int br, Stablo S);
int UnosUListu(Pozicija P, int br);
int UnosIza(Pozicija P, Pozicija Novi);
int Sortiranje(Pozicija Prvi, Pozicija Novi);
int UsporediGradove(Stablo S1, Stablo S2);
int IspisHashTablice(HashTablicaP P);
HashTablicaP InicijalizacijaTablice(int velicina);
int UnosUHashTablicu(HashTablicaP T, char* drzava, char* dat);
int HashKljuc(char* K);

int main()
{
	struct Cvor H = { .ime = " ", .root = NULL, .next = NULL };
	Pozicija P = &H;
	int odabir = 0;
	char drzava[MAX_LINE] = { 0 };
	Stablo S = NULL;
	_Hash T = { 0 };

	ProcitajIzDat(P);
	Ispis(P->next);

	printf("Upisi ime drzave i broj stanovnika (ispisuju se gradovi s vecim brojem stanovnika od toga): ");
	if (!scanf(" %s %d", drzava, &odabir)) printf("Pogresan unos\n");

	Pronadi(drzava, odabir, P);

	//11zad

	char ime[MAX_LINE];
	int br = 0;
	Pozicija P;
	HashTablicaP  H = NULL;

	H = InicijalizacijaTablice(11);

	char datoteka[] = "drzave.txt";
	Unosizdatd(H, datoteka);
	IspisHashTablice(H);

	return 0;
}

Stablo Insert(Stablo trenutni, Stablo NoviEl)
{
	if (trenutni == NULL) return NoviEl;
	if (trenutni->broj < NoviEl->broj) trenutni->desno = Insert(trenutni->desno, NoviEl);
	else if (trenutni->broj > NoviEl->broj) trenutni->lijevo = Insert(trenutni->lijevo, NoviEl);
	else free(NoviEl);
	return trenutni;
}

Stablo StvoriNoviElement(char* ime, int broj)
{
	Stablo S;

	S = (Stablo)malloc(sizeof(struct Cvor));
	if (S == NULL) perror("Greska kod alociranja memorije.\n");

	else
	{
		strcpy_s(S->ime, sizeof(S->ime), ime);
		S->broj = broj;
		S->desno = NULL;
		S->lijevo = NULL;
		return S;
	}
	return NULL;

}

int IzStablaUListu(Stablo B, Pozicija Lista)
{
	if (B == NULL) return 0;
	IzStablaUListu(B->desno, Lista);
	UnosUListu(Lista, B->broj);
	IzStablaUListu(B->lijevo, Lista);

	return 0;
}

int UnosIzDatoteke(HashTablicaP P, char* drzava)
{
	FILE* dat = NULL;
	int br = 0;
	char drzava[MAX_LINE] = { 0 };
	char drzava2[MAX_LINE] = { 0 };
	struct Cvor temp = { .ime = "", .root = NULL, .next = NULL };
	Pozicija Novi = &temp;

	dat = fopen(drzava, "r");
	if (!dat)
		return -1;

	while (!feof(dat))
	{
		if (!fscanf(dat, "%s %s\n", drzava, drzava2)) prinf("Greska\n");
		UnosUHashTablicu(P, drzava, drzava2);
	}

	fclose(dat);

	return 0;
}

Pozicija StvoriElementListe(Pozicija P, char* ime)
{
	Pozicija Novi = NULL;
	Novi = (Pozicija)malloc(sizeof(struct _Cvor));

	if (Novi == NULL)
	{
		perror("Greška!\n");
		return NULL;
	}

	strcpy_s(Novi->ime, sizeof(Novi->ime), ime);
	Novi->next = NULL;

	return Novi;
}

int Pronadi(char* drzava, int brojStan, Pozicija P)
{
	Pozicija temp = P->next;

	while (temp->next)
	{
		if (strcmp(drzava, temp->ime) == 0)
			break;
		temp = temp->next;
	}

	Stablo tren = temp->root;

	IspisGrada(brojStan, tren);

	return 0;
}

int ProcitajIzDat(Pozicija P)
{
	FILE* dat = NULL;
	char tIme[MAX_LINE] = { 0 };
	char NazivDat[MAX_LINE] = { 0 };

	dat = fopen("drzave.txt", "r");

	if (!dat)
	{
		printf("Pogreška pri otvaranju datoteke!\n");
		return -1;
	}

	while (dat != feof)
	{
		if (!scanf("%s %s", tIme, NazivDat)) prinf("Greska kod unosa imena datoteke\n");
		Unos(P, tIme, NazivDat);
	}

	fclose(dat);

	return 0;
}

int Ispis(Pozicija P)
{
	Pozicija temp = P->next;

	while (temp)
	{
		printf(" %s", temp->ime);
		IspisStabla(temp->root);
		temp = temp->next;

	}

	return 0;
}

int DodajUStablo(Pozicija Head, char* imeDat)
{
	Stablo H = NULL;
	FILE* dat = NULL;
	int br = 0;
	char ime[MAX_LINE];
	Stablo Grad = NULL;

	dat = fopen(imeDat, "r");
	if (!fscanf(dat, " %s %d", ime, &br)) prinf("Greska\n");

	Head->root = H;

	Grad = StvoriNoviElement(ime, br);
	H = Insert(Grad, H);

	return 0;
}

int IspisGrada(int br, Stablo S)
{
	if (!S)
		return 1;

	else if (br < S->broj)
	{
		printf(" %s", S->ime);
		PrintEl(br, S->desno);
	}

	else
		PrintEl(br, S->lijevo);

	return 0;
}

int UnosUListu(Pozicija P, int br)
{

	return 0;
}

int UnosIza(Pozicija P, Pozicija Novi)
{
	Novi->next = P->next;
	P->next = Novi;

	return 0;
}

int Sortiranje(Pozicija Prvi, Pozicija Novi)
{
	while (Prvi->next != NULL && strcmp(Prvi->next->ime, Novi->ime) < 0)
		Prvi = Prvi->next;

	UnosIza(Prvi, Novi);

	return 0;
}

int UsporediGradove(Stablo S1, Stablo S2)
{
	if (strcmp(S1->ime, S2->ime) > 0)
	{
		S1->lijevo = insert(S1->lijevo, S2);
	}

	if (strcmp(S1->ime, S2->ime) < 0)
	{
		S1->desno = insert(S1->desno, S2);
	}

	return 0;
}

int IspisHashTablice(HashTablicaP P)
{
	Pozicija Q = NULL;

	for (int i = 0; i < P->velicina; i++)
	{
		Q = P->tablica;
		while (Q != NULL)
		{
			printf("Drzava: %s\n", Q->ime);
			Ispis(Q->root);
			Q = Q->next;
		}

	}

	return 0;
}

HashTablicaP InicijalizacijaTablice(int velicina)
{
	HashTablicaP T;

	T = (HashTablicaP)malloc(sizeof(struct _HashTablica));

	if (T = NULL)
	{
		printf("Greska!\n");
		return 0;
	}

	T->velicina = velicina;
	T->tablica = (Pozicija*)malloc(sizeof(Pozicija) * T->velicina);

	if (T->tablica == NULL)
	{
		printf("Greska!\n");
		return 0;
	}

	for (int i = 0; i < velicina; i++)
		T->tablica[i] = NULL;

	return T;
}

int UnosUHashTablicu(HashTablicaP T, char* drzava, char* ime)
{
	Pozicija Novi = NULL, trenutni = NULL;
	int kljuc = HashKljuc(drzava);

	Novi = StvoriNoviElement(drzava, 0);

	if (Novi == NULL)
		return -1;

	Unos(Novi, ime);

	if (!T->tablica[kljuc])
		T->tablica[kljuc] = Novi;
	else
	{
		trenutni = T->tablica[kljuc];
		while (trenutni->next != NULL && strcmp(trenutni->next->ime, drzava) < 0)
			trenutni = trenutni->next;
		Novi->next = trenutni->next;
		trenutni->next = Novi;
	}
	return 0;
}

int HashKljuc(char* K)
{
	int Hash = 0, brojac = 0;

	printf("\n Hash %s=  ", K);

	while (brojac != 5) {
		printf("+%d", *K);
		Hash += *K++;
		brojac++;
	}

	return Hash % 11;
}