#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_ERROR (-1)
#define LINE_LENGTH 128

struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int coef;
	int exp;
	Position Next;
}Polinom;

int UnosSort(Position P, Position Q);

int main(void) {
	Polinom pHead;						//prva lista
	pHead.Next = NULL;

	Polinom qHead;						//druga lista
	qHead.Next = NULL;

	UnosSort(&pHead, &qHead);

	return EXIT_SUCCESS;
}

int UnosSort(Position P, Position Q) {

	FILE* fp = NULL;										//otvaranje dokumenta
	fp = fopen("polinom.txt", "r");

	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument polinom.txt se nije otvorio!\r\n");
		return PROGRAM_ERROR;
	}

	int a = 0, c = 0;					//coef
	int b = 0, d = 0;					//exp
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
