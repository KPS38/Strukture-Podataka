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

Position Stvori(int k, int e);
int UnosSort(Position P, Position Q);

int main(void) {
	Polinom pHead;						//prva lista
	pHead.Next = NULL;

	Polinom qHead;						//druga lista
	qHead.Next = NULL;

	Polinom zHead;						//treca lista za zbroj
	zHead.Next = NULL;

	Polinom mHead;						//cetvrta lista za umnozak
	mHead.Next = NULL;

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

	int a = 0, b = 0;					//coef
	int c = 0, d = 0;					//exp
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

Position Stvori(int k, int e) {
	Position el = NULL;

	el = (Position)malloc(sizeof(Polinom));

	if (NULL == el) {
		printf("Memory allocation failed!\r\n");
		return PROGRAM_ERROR;
	}

	el->coef = k;
	el->exp = e;
	el->Next = NULL;

	return el;
}