#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024

#define DIDNT_OPEN -1
#define MALLOC_ERROR -1
#define POSTFIX_ERROR -2

#define EXIT_SUCCESS 1

struct _cvor;
typedef struct _cvor* Position;

typedef struct _cvor {
	float el;
	Position Next;
}cvor;

int citajDatoteku(char[], Position);

int Push(float, Position);
float Pop(Position);


int main()
{
	cvor Head;
	Head.Next = NULL;
	char filename[MAX_LINE_SIZE] = { 0 };
	float temp = 0;
	int provjera = 0;

	printf("Unesi ime .txt datoteke (bez .txt): ");
	scanf(" %s", filename);
	strcat(filename, ".txt");

	while (citajDatoteku(filename, &Head) == DIDNT_OPEN)
	{
		printf("\nNepravilno ime datoteke.\nUnesi ime .txt datoteke (bez .txt): ");
		scanf(" %s", filename);
		strcat(filename, ".txt");
		provjera = citajDatoteku(filename, &Head);
	}

	if (provjera == POSTFIX_ERROR)
	{
		printf("Nepravilan postfix izraz.");
		return 0;
	}

	temp = Pop(&Head);
	printf("\nRjesenje je: %f\n", temp);

	while (Head.Next != NULL) {

	}
	return 0;
}

int citajDatoteku(char filename[], Position Head)
{
	FILE* fp = NULL;
	int n = 0, brojacEl = 0;
	char buffer[MAX_LINE_SIZE] = { 0 };
	float temp = 0.0;

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		return DIDNT_OPEN;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s ", buffer);

		if ((sscanf(buffer, "%d ", &n)) == 1)
		{
			Push((float)n, Head);
			brojacEl++;
		}

		else
		{
			switch (buffer[0])
			{
			case '*':
				if (brojacEl < 2)
				{
					return POSTFIX_ERROR;
				}
				temp = Pop(Head);
				Push(Pop(Head) * temp, Head);
				brojacEl--;
				break;

			case '+':
				if (brojacEl < 2)
				{
					return POSTFIX_ERROR;
				}
				temp = Pop(Head);
				Push(Pop(Head) + temp, Head);
				brojacEl--;
				break;

			case '-':
				if (brojacEl < 2)
				{
					return POSTFIX_ERROR;
				}
				temp = Pop(Head);
				Push(Pop(Head) - temp, Head);
				brojacEl--;
				break;

			case '/':
				if (brojacEl < 2)
				{
					return POSTFIX_ERROR;
				}
				temp = Pop(Head);
				if (temp == 0)
				{
					printf("Ne dili sa 0!\n");
					return POSTFIX_ERROR;
				}
				Push(Pop(Head) / temp, Head);
				brojacEl--;
				break;

			default:
				return POSTFIX_ERROR;
			}

		}

	}

	if (brojacEl != 1)
	{
		return POSTFIX_ERROR;
	}

	else
	{
		return EXIT_SUCCESS;
	}

}

int Push(float x, Position Head)
{
	Position q = NULL;
	q = (Position)malloc(sizeof(cvor));

	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return MALLOC_ERROR;
	}

	q->el = x;
	q->Next = Head->Next;
	Head->Next = q;

	return EXIT_SUCCESS;
}

float Pop(Position Head)
{
	Position temp = NULL;
	float pom = 0.0;

	pom = Head->Next->el;

	temp = Head->Next;
	Head->Next = temp->Next;
	free(temp);

	return pom;
}