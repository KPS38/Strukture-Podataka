#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_ERROR (-1)									
#define MALLOC_ERROR (0)									//finito
#define LINE_LENGTH 128										

struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int coef;
	int exp;
	Position Next;
}Polinom;

Position Stvori(void);
int UnosDat(Position pHead, Position qHead);
int UnosSort(Position Head, int coef, int exp);
int Ispis(Position Head);
int DodajK(Position sum, int coef, int exp);
int Suma(Position pHead, Position qHead);
int Umnozak(Position pHead, Position qHead);
int MakniDuple(Position Head);						//poziva se u funkciji ispis
int BrisiNula(Position Head);							//poziva se u funkciji ispis
int BrisisSve(Position Head);

int main(void) {
	Position pHead = NULL;
	Position qHead = NULL;
	Position sHead = NULL;
	Position uHead = NULL;

	pHead = Stvori();
	qHead = Stvori();

	UnosDat(pHead, qHead);	

	printf("Prva lista:\n");
	Ispis(pHead);

	printf("\nDruga lista:\n");
	Ispis(qHead);


	sHead = Suma(pHead, qHead);
	if (sHead == NULL) {
		printf("\nGreska u zbrajanju!");
		return PROGRAM_ERROR;
	}

	printf("\nZbroj lista:\n");
	Ispis(sHead);

	uHead = Umnozak(pHead, qHead);
	if (uHead == NULL) {
		printf("\nGreska u mnozenju!");
		return PROGRAM_ERROR;
	}

	printf("\nLista umnoska:\n");
	Ispis(uHead);

	BrisisSve(pHead);

	BrisisSve(qHead);

	BrisisSve(sHead);

	BrisisSve(uHead);

	printf("\nObrisao sam sve, kad ce vecera?");

	return EXIT_SUCCESS;
}

Position Stvori(void) {
	Position Head = NULL;
	Head = (Position)malloc(sizeof(Polinom));

	if (Head == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return MALLOC_ERROR;
	}

	Head->Next = NULL;
	Head->exp = 0;
	Head->coef = 0;
	return Head;
}

int UnosDat(Position pHead, Position qHead) {

	int coef = 0, exp = 0, n = 0;
	char buffer[LINE_LENGTH] = { 0 };
	char* buf = NULL;
	int unos = 0;

	FILE* fp = NULL;										//otvaranje dokumenta
	fp = fopen("polinom.txt", "r");

	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument polinom.txt se nije otvorio!\r\n");
		return PROGRAM_ERROR;
	}

	fgets(buffer, LINE_LENGTH, fp);
	buf = buffer;

	while (strlen(buf) != 0) {
		sscanf_s(buf, "%d %d %n", &coef, &exp, &n);
		if (coef == 0) {
			buf += n;
		}
		else {
			unos = UnosSort(pHead, coef, exp);
			if (unos != 0)
				return PROGRAM_ERROR;
			buf += n;
		}
	}

	fgets(buffer, LINE_LENGTH, fp);
	buf = buffer;

	while (strlen(buf) != 0) {
		sscanf_s(buf, "%d %d %n", &coef, &exp, &n);
		if (coef == 0) {
			buf += n;
		}
		else {
			unos = UnosSort(qHead, coef, exp);
			if (unos != 0)
				return PROGRAM_ERROR;
			buf += n;
		}
	}

	return EXIT_SUCCESS;
}

int UnosSort(Position Head, int coef, int exp) {

	Position P = Head;
	Position Q = NULL;
	Position temp = NULL;

	while (P->Next != NULL && P->Next->exp >= exp) {
		P = P->Next;
	}

	Q = (Position)malloc(sizeof(Polinom));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	Q->coef = coef;
	Q->exp = exp;

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int Ispis(Position Head) {

	Position P = Head;
	MakniDuple(P);


	while (P->Next != NULL) {
		if (P->Next->exp != 0) {
			if (P->Next->coef > 0) {
				printf("%dx^%d", P->Next->coef, P->Next->exp);
				if (P->Next->Next != NULL) {
					printf(" + ");
				}
			}
			else if (P->Next->coef < 0) {
				printf("(%dx^%d)", P->Next->coef, P->Next->exp);
				if (P->Next->Next != NULL) {
					printf(" + ");
				}
			}
		}
		else if(P->Next->exp==0){
			printf("%d", P->Next->coef);
			if (P->Next->Next != NULL) {
				printf(" + ");
			}
		}
		P = P->Next;
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int DodajK(Position sum, int coef, int exp) {

	Position P = sum;
	Position Q = NULL;

	while (P->Next != NULL) {
		P = P->Next;
	}

	Q = (Position)malloc(sizeof(Polinom));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	Q->coef = coef;
	Q->exp = exp;

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int Suma(Position pHead, Position qHead) {

	Position P = pHead->Next;
	Position Q = qHead->Next;
	Position sum = NULL;

	sum = Stvori();

	while (P != NULL && Q != NULL) {

		if (P->exp > Q->exp) {							//ako je potencija prvog veca od drugog
			DodajK(sum, P->coef, P->exp);
			P = P->Next;
		}

		else if (P->exp < Q->exp) {						//ako je potencija drugog veca od prvog
			DodajK(sum, Q->coef, Q->exp);
			Q = Q->Next;
		}

		else if (P->exp == Q->exp){											//ako su iste potencije
			DodajK(sum, P->coef + Q->coef, P->exp);
			P = P->Next;
			Q = Q->Next;
		}
	}

	while (P != NULL) {									//ako ostane samo jedna
		DodajK(sum, P->coef, P->exp);
		P = P->Next;
	}
	while (Q != NULL) {
		DodajK(sum, Q->coef, Q->exp);
		Q = Q->Next;
	}

	return sum;
}

int Umnozak(Position pHead, Position qHead) {

	Position P = pHead->Next;
	Position Q = qHead->Next;
	Position umn = NULL;

	umn = Stvori();

	while (P != NULL) {
		while (Q != NULL) {
			UnosSort(umn, P->coef * Q->coef, P->exp + Q->exp);
			Q = Q->Next;
		}
		P = P->Next;
		Q = qHead->Next;
	}
	return umn;
}

int MakniDuple(Position Head)
{
	Position P = Head;
	Position Q  =NULL;

	if (P == NULL)
		return PROGRAM_ERROR;

	while (P->Next != NULL)
	{
		if (P->exp == P->Next->exp)					//ako uzastopne pozicije imaju isti eksponent, zbraja koeficijente, brise visak
		{
			P->coef = P->coef + P->Next->coef;
			Q = P->Next->Next;
			free(P->Next);
			P->Next = Q;
		}
		else
		{
			P = P->Next;
		}

	}
	BrisiNula(P);
	return EXIT_SUCCESS;
}

int BrisiNula(Position Head) {
	Position P = Head;
	Position temp = NULL;

	while (P->Next != NULL)
		{
			if (P->Next->coef == 0)
			{
				temp = P->Next;
				P->Next = P->Next->Next;
				free(temp);
				break;
			}
			else
				P = P->Next;
		}


	return EXIT_SUCCESS;
}

int BrisisSve(Position Head) {
	Position P = Head;
	Position temp = NULL;
	while (P ->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}
