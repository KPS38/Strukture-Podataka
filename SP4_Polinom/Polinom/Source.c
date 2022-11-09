#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_ERROR (-1)
#define LINE_LENGTH 128

struct Polinom;
typedef struct Polinom* Position;
typedef struct Polinom {
	int coef;
	int exp;
	Position Next;
};

int UnosSort(Position P, Position Q);
int Suma(Position P, Position Q, Position Z);
int Umnozak(Position P, Position Q, Position U);


int main(void) {
	struct Polinom pHead = {		//prva lista
		.coef = 0,
		.exp = 0,
		.Next = NULL
	};					

	struct Polinom qHead = {		//druga lista
		.coef = 0,
		.exp = 0,
		.Next = NULL
	};

	struct Polinom zHead = {		//lista za zbroj
		.coef = 0,
		.exp = 0,
		.Next = NULL
	};

	struct Polinom uHead = {		//lista za umnozak
		.coef = 0,
		.exp = 0,
		.Next = NULL
	};

	UnosSort(&pHead, &qHead);

	Suma(&pHead, &qHead, &zHead);
	Umnozak(&pHead, &qHead, &uHead);
	return EXIT_SUCCESS;
}

int UnosSort(Position P, Position Q) {

	FILE* fp = NULL;										//otvaranje dokumenta
	fp = fopen("polinom.txt", "r");

	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument polinom.txt se nije otvorio!\r\n");
		return PROGRAM_ERROR;
	}

	int a = 0, c = 0;							//coef
	int b = 0, d = 0;							//exp
	int n = 0;
	char buffer[LINE_LENGTH];
	char* poi = NULL;							//pokazivac
	int cnt;


	/*
	while (P->Next != NULL && P->Next->El < Q->El);                    //funkcija za sortirani unos
	P = P->Next;

	Q->Next = P->Next;
	P->Next = Q;
	*/

	return EXIT_SUCCESS;
}

int Suma(Position P, Position Q, Position Z) {
	while (P->Next && Q->Next) {
		if (P->exp > Q->exp) {							//ako je potencija prvog veca od drugog
			Z->exp = P->exp;
			Z->coef = P->coef;
			P = P->Next;
		}

		else if (P->exp < Q->exp) {						//ako je potencija drugog veca od prvog
			Z->exp = Q->exp;
			P->coef = Q->coef;
			Q = Q->Next;
		}

		else {											//ako su iste potencije
			Z->exp = P->exp;
			Z->coef = P->coef + Q->coef;
			P = P->Next;
			Q = Q->Next;
		}

		Z->Next = (Position)malloc(sizeof(struct Polinom));
		Z = Z->Next;
		Z->Next = NULL;
	}

	while (P->Next || Q->Next) {						//ako ostane samo jedna
		if (P->Next) {
			Z->exp = P->exp;
			Z->coef = P->coef;
			P = P->Next;
		}
		if (Q->Next) {
			Z->exp = Q->exp;
			Z->coef = Q->coef;
			Q = Q->Next;
		}
		Z->Next = (Position)malloc(sizeof(struct Polinom));
		Z = Z->Next;
		Z->Next = NULL;
	}

	return EXIT_SUCCESS;
}

int Prikaz(Position P)
{
	while (P->Next != NULL) {
		printf("%dx^%d", P->coef, P->exp);
		P = P->Next;
		if (P->coef >= 0) {
			if (P->Next != NULL)
				printf(" + ");
		}
		printf("\n");
	}
	return EXIT_SUCCESS;
}

int Umnozak(Position P, Position Q, Position U) 
{
	




	return EXIT_SUCCESS;
}
