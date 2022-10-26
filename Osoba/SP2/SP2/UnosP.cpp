#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (1024)
#define PROGRAM_ERROR (-1)


typedef struct Cvor* Pozicija;
struct Cvor{
	int El;
	Pozicija Next;
};

int UnosP(int x, Pozicija P);
int Ispis(Pozicija P);

int main() {
	struct Cvor Head;
	Head.Next = NULL;

	UnosP(3, &Head);
	UnosP(8, &Head);
	UnosP(2, &Head);

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

int Ispis(Pozicija P) {
	while (P != NULL) {
		printf(" %d", P->El);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}