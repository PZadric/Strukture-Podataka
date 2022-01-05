#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>

struct cvor;
typedef struct cvor* poz;
typedef struct cvor {
	int el;
	poz le;
	poz de;
}cvor;

struct lista;
typedef struct lista* pozList;
typedef struct lista {
	int el;
	pozList next;
}lista;

poz insert(poz, int);
void ispis(poz);
int replace(poz);
void upis_u_dat(poz);

poz insert(poz root, int p)
{
	if (root == NULL) {
		root = (poz)malloc(sizeof(cvor));
		root->el = p;
		root->le = root->de = NULL;
		return root;
	}

	else if (p >= root->el) {
		root->le = insert(root->le, p);
	}

	else if (p < root->el) {
		root->de = insert(root->de, p);
	}

	return root;
}

void ispis(poz root)
{
	if (root)
	{
		ispis(root->le);
		printf("%d\n", root->el);
		ispis(root->de);
	}
}

int replace(poz root)
{
	int temp = 0;
	if (root == NULL) {
		return 0;
	}
	temp = root->el;
	root->el = replace(root->le) + replace(root->de);
	return temp + root->el;
}

void upis_u_dat(pozList P, char* ime)
{
	FILE* file = NULL;
	file = fopen(ime, "a"); // datoteka? */

	while (P != NULL)
	{
		fprintf(file, "%d ", P->el);
		P = P->next;
	}
	fprintf(file, "\n");
	fclose(file);

}

int main()
{
	poz root = NULL;
	int i = 0;
	int elementi[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

	while (i < 10) {
		root = insert(root, elementi[i]);
		i++;
	}
	ispis(root);
	upis_u_dat(root, "datoteka.txt");



	root->el = replace(root->le) + replace(root->de);
	ispis(root);
	upis_u_dat(root, "datoteka.txt");


	srand(time(NULL));
	poz root_rand;

	struct lista head = { .el = 0, .next = NULL };

	root_rand = (poz)malloc(sizeof(cvor));
	root_rand->el = rand() % 80 + 10;
	root_rand->le = NULL;
	root_rand->de = NULL;

	for (i = 1; i < 10; i++)
	{
		root_rand = insert(root_rand, rand() % 80 + 10);
	}
	printf("\n");
	ispis(root_rand);

	upis_u_dat(root_rand, "datoteka.txt");

	return 0;
}
