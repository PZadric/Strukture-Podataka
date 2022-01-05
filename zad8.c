#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _stablo;
typedef struct _stablo* poz;
typedef struct _stablo {
	int element;
	poz le;
	poz de;
} stablo;

poz Unesi(int element, poz root);
poz Stvoriel(int element);
int PrintInorder(poz root);
int PrintPreorder(poz root);
int PrintPostorder(poz root);
poz Trazi(int element, poz root);
poz TraziMin(poz root);
poz Brisi(int element, poz root);


poz Unesi(int element, poz root)
{
	poz P = root;
	poz noviel = NULL;

	if (P == NULL) {
		noviel = Stvoriel(element);
		return noviel;
	}
	else if (element < P->element) {
		P->le = Unesi(element, P->le);
	}
	else if (element > P->element) {
		P->de = Unesi(element, P->de);
	}

	return P;

}

poz Stvoriel(int element)
{
	poz noviel = NULL;

	noviel = (poz)malloc(sizeof(stablo));
	if (noviel == NULL) {
		printf("Nemoguce alocirati memoriju\n");
		return NULL;
	}
	noviel->element = element;
	noviel->le = NULL;
	noviel->de = NULL;

	return noviel;
}

int PrintInorder(poz root)
{
	poz P = root;

	if (P != NULL) {
		PrintInorder(P->le);
		printf("%d ", P->element);
		PrintInorder(P->de);
	}

	return 0;
}

int PrintPreorder(poz root)
{
	poz P = root;

	if (P != NULL) {
		printf("%d ", P->element);
		PrintPreorder(P->le);
		PrintPreorder(P->de);
	}

	return 0;
}

int PrintPostorder(poz root)
{
	poz P = root;

	if (P != NULL) {
		PrintPostorder(P->le);
		PrintPostorder(P->de);
		printf("%d ", P->element);
	}

	return 0;
}

poz Trazi(int element, poz root)
{
	poz P = root;

	if (P == NULL) {
		return NULL;
	}
	else if (element < P->element) {
		return Trazi(element, P->le);
	}
	else if (element > P->element) {
		return Trazi(element, P->de);
	}
	else {
		return P;
	}
}

poz TraziMin(poz root)
{

	poz P = root;

	while (P->le != NULL) {
		P = P->le;
	}

	return P;
}

poz Brisi(int element, poz root)
{
	poz P = root;
	poz temp = NULL;

	if (P == NULL) {
		printf("Nema elementa\n");
		return P;
	}
	else if (element < P->element) {
		P->le = Brisi(element, P->le);
	}
	else if (element > P->element) {
		P->de = Brisi(element, P->de);
	}
	else if (P->le != NULL && P->de != NULL) {
		temp = TraziMin(P->de);
		P->element = temp->element;
		P->de = Brisi(P->element, P->de);
	}
	else {
		temp = P;
		if (P->le == NULL) {
			P = P->de;
		}
		else {
			P = P->le;
		}
		free(temp);
	}

	return P;
}

int main()
{
	poz root = NULL;
	poz temp = NULL;

	int izbor = 0;
	int element = 0;

	do {
		printf("IZABERI: \n"
			"1 - Dodaj element u stablo\n"
			"2 - Ispisi stablo (inorder)\n"
			"3 - Ispisi stablo (preorder)\n"
			"4 - Ispisi stablo (postorder)\n"
			"5 - Pronadi element\n"
			"6 - Izbrisi element\n"
			"0 - Exit\n");

		scanf("%d", &izbor);

		switch (izbor)
		{
		case 1:
			printf("Unesi element: ");
			scanf("%d", &element);
			root = Unesi(element, root);
			break;
		case 2:
			PrintInorder(root);
			break;
		case 3:
			PrintPreorder(root);
			break;
		case 4:
			PrintPostorder(root);
			break;
		case 5:
			printf("\nUnesi element koji trazis: ");
			scanf("%d", &element);
			temp = Trazi(element, root);
			if (temp != NULL) {
				printf("Element %d je pronaden\n", temp->element);
			}
			else {
				printf("Element %d nije pronaden\n", element);
			}
			break;
		case 6:
			printf("Unesi element koji brises: ");
			scanf("%d", &element);
			root = Brisi(element, root);
		case 0:
			break;
		default:
			printf("Pogresan odabir\n");
		}

	} while (izbor != 0);

	return 0;
}