#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	double broj;
	Position next;
}Element;

Position StvoriElement(double broj);

int UnesiNakon(Position pozicija, Position noviEl);
int Push(Position head, double broj);
int IzbrisiNakon(Position pozicija);
int Pop(double* rezultat, Position head);
int Operacija(Position head, char operacija);
int IzracunajPostfixIzDat(double* rezultat, char* nazivDat);
int IzbrisiSve(Position head);

int main() {

	Element head = { .broj = 0,.next = NULL };
	Position p = &head;

	return 0;
}

Position StvoriElement(double broj)
{
	Position noviEl = NULL;

	noviEl = (Position)malloc(sizeof(Element));
	if (!noviEl)
	{
		perror("Nije moguce alocirati\n");
		return EXIT_FAILURE;
	}

	noviEl->broj = broj;
	noviEl->next = NULL;

	return noviEl;
}

int UnesiNakon(Position pozicija, Position noviEl)
{
	noviEl->next = pozicija->next;
	pozicija->next = noviEl;

	return EXIT_SUCCESS;
}

int Push(Position head, double broj)
{
	Position noviEl = NULL;

	noviEl = StvoriElement(broj);
	if (!noviEl)
	{
		printf("Nije moguce stvoriti element\n");
		return EXIT_FAILURE;
	}

	UnesiNakon(head, noviEl);

	return EXIT_SUCCESS;
}

int IzbrisiNakon(Position pozicija)
{
	Position temp = pozicija->next;

	if (!temp)
	{
		return EXIT_SUCCESS;
	}

	pozicija->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Pop(double* rezultat, Position head)
{
	Position prvi = head->next;

	if (!prvi)
	{
		perror("Postfix nije validan!\n");
		return EXIT_FAILURE;
	}

	*rezultat = prvi->broj;
	IzbrisiNakon(head);

	return EXIT_SUCCESS;
}

int Operacija(Position head, char operacija)
{
	double operand1 = 0;
	double operand2 = 0;
	double rezultat = 0;
	int s1 = EXIT_SUCCESS;
	int s2 = EXIT_SUCCESS;

	s2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	s1 = Pop(&operand1, head);
	if (s1 != EXIT_SUCCESS)
	{
		return -2;
	}

	switch (operacija)
	{
	case '+':
		rezultat = operand1 + operand2;
		break;
	case '-':
		rezultat = operand1 - operand2;
		break;
	case '*':
		rezultat = operand1 * operand2;
		break;
	case '/':
		if (operand2 == 0)
		{
			perror("Nemoguce djeliti s nulom!\n");
			return EXIT_FAILURE;
		}
		rezultat = operand1 / operand2;
		break;
	default:
		printf("Niste unijeli validnu operaciju!\n");
		return EXIT_FAILURE;
	}

	return Push(head, rezultat);
}

int IzracunajPostfixIzDat(double* rezultat, char* nazivDat)
{
	FILE* dat = NULL;
	int fileLength = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	int broj = 0;
	int status = 0;
	char operacija = 0;
	Element head = { .next = NULL,.broj = 0 };

	dat = fopen(nazivDat, "rb");
	if (!dat)
	{
		perror("Nije moguce otvoriti datoteku!\n");
		return EXIT_FAILURE;
	}

	fseek(dat, 0, SEEK_END);
	fileLength = ftell(dat);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Nije moguce alocirati memoriju!\n");
		return EXIT_FAILURE;
	}

	rewind(dat);
	fread(buffer, sizeof(char), fileLength, dat);
	printf("|%s|\n", buffer);
	fclose(dat);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &broj, &numBytes);
		if (status == 1)
		{
			status = Push(&head, broj);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return EXIT_FAILURE;
			}
			currentBuffer += numBytes;
		}
		else
		{
			sscanf(currentBuffer, " %c %n", &operacija, &numBytes);
			status = Operacija(&head, operacija);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return EXIT_FAILURE;
			}
			currentBuffer += numBytes;
		}
	}
	free(buffer);

	status = Pop(rezultat, &head);
	if (status != EXIT_SUCCESS)
	{
		IzbrisiSve(&head);
		return EXIT_FAILURE;
	}

	if (head.next)
	{
		printf("Postfix nije validan!\n");
		IzbrisiSve(&head);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int IzbrisiSve(Position head)
{
	while (head->next)
	{
		IzbrisiNakon(head);
	}

	return EXIT_SUCCESS;
}
