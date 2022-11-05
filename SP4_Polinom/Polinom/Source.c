#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PROGRAM_ERROR (-1)

struct polinom;
typedef struct polinom* Position;
struct polinom {
	int El;
	int c;
	int e;
	Position Next;
};

int UnosSort(Position P, Position Q);

int main(void) {
	struct polinom Head = {
		.El = 0,
		.c = 0,
		.e = 0,
		.Next = NULL
	};

	return EXIT_SUCCESS;
}

int UnosSort(Position P) {
	Position Q;

	Q = (Position)malloc(sizeof(struct polinom));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	while (P->Next != NULL && P->Next->El < Q->El);
	P = P->Next;

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}
