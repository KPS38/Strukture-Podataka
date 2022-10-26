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

int UnosK(int x, Pozicija P);
int Ispis(Pozicija P);

int main() {
	struct Cvor Head;
	Head.Next = NULL;

	UnosK(3, &Head);
	UnosK(8, &Head);
	UnosK(2, &Head);
	Ispis(Head.Next);

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