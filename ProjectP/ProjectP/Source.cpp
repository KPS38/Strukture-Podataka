#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PROGRAM_ERROR (-1)

typedef struct Cvor* Pozicija;
struct Cvor {
	int El;
	Pozicija Next;
};

int UnosP(int x, Pozicija P);
int UnosK(int x, Pozicija P);
int Ispis(Pozicija P);
Pozicija Trazi(int x, Pozicija P);
int Brisi(int x, Pozicija P);
int BrisiSve(Pozicija P);

int main() {
	struct Cvor Head;
	Head.Next = NULL;
	Pozicija P;

	UnosK(1, &Head);
	UnosP(3, &Head);
	UnosP(8, &Head);
	UnosP(2, &Head);
	UnosK(5, &Head);
	Ispis(Head.Next);
	Trazi(5, Head.Next);
	printf("\nElement 5 nalazi se na %p adresi.\n", &P);
	Trazi(1, Head.Next);
	printf("\nElement 1 nalazi se na %p adresi.\n", &P);
	Brisi(8, &Head);
	Ispis(Head.Next);
	BrisiSve(Head.Next);

	return EXIT_SUCCESS;
}

int UnosP(int x, Pozicija P) {
	Pozicija Q;
	Q = (Pozicija)malloc(sizeof(struct Cvor));
	Q->El = x;
	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}
int UnosK(int x, Pozicija P) {
	Pozicija Q;
	while (P->Next != NULL) {
		P = P->Next;
	}
	Q = (Pozicija)malloc(sizeof(struct Cvor));
	Q->El = x;
	P->Next = Q;
	Q->Next = NULL;

	return EXIT_SUCCESS;
}

int Ispis(Pozicija P) {
	while (P != NULL) {
		printf(" %d", P->El);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

Pozicija Trazi(int x, Pozicija P) {
	while (P != NULL && P->El != x) {
		P = P->Next;
	}
	return P;
}

int Brisi(int x, Pozicija P) {
	Pozicija prev, temp;
	while (P->Next != NULL && P->Next->El != x){
		P = P->Next;
	}
	if (NULL == P) {
		printf("Nema ga");
		return PROGRAM_ERROR;
	}
	else {
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int BrisiSve(Pozicija P) {
	Pozicija temp;
	while (P->Next != NULL)										//ciscenje alocirane memorije na kraju
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}