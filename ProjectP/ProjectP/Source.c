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
int UnosSort(int x, Pozicija P);
int UnosIza(int x, int y, Pozicija P);
int UnosIspred(int x, int y, Pozicija P);

int Ispis(Pozicija P);

Pozicija Trazi(int x, Pozicija P);
Pozicija TraziPret(int x, Pozicija P);

int Brisi(int x, Pozicija P);
int BrisiMin(Pozicija P);
int BrisiSve(Pozicija P);
int BrisiSveMin(Pozicija P);

int main() {
	struct Cvor Head;
	Head.Next = NULL;
	Pozicija P;
	int T1, T2;

	UnosK(1, &Head);
	UnosP(3, &Head);
	UnosP(8, &Head);
	UnosP(2, &Head);
	UnosK(5, &Head);

	Ispis(Head.Next);

	T1=Trazi(5, Head.Next);
	printf("\nElement 5 nalazi se na %p adresi.\n", &T1);

	T2=TraziPret(1, Head.Next);
	printf("\nPrethodni element elementa 1 nalazi se na %p adresi.\n", &T2);

	Brisi(8, &Head);

	Ispis(Head.Next);

	printf("\n");

	BrisiSve(&Head);

	UnosSort(5, &Head);
	UnosSort(2, &Head);
	UnosSort(3, &Head);
	UnosSort(6, &Head);

	Ispis(Head.Next);

	printf("\n");

	UnosIza(1, 3, Head.Next);
	UnosIspred(7, 3, &Head);

	Ispis(Head.Next);

	BrisiSveMin(&Head);

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
	Q = (Pozicija)malloc(sizeof(struct Cvor));

	while (P->Next != NULL) {
		P = P->Next;
	}

	Q->El = x;
	P->Next = Q;
	Q->Next = NULL;

	return EXIT_SUCCESS;
}

int UnosSort(int x, Pozicija P) {
	Pozicija Q;
	Q = (Pozicija)malloc(sizeof(struct Cvor));

	while (P->Next != NULL && P->Next->El < x) {
		P = P->Next;
	}

	Q->El = x;
	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int UnosIza(int x, int y, Pozicija P) {
	Pozicija Q;
	
	P = Trazi(y, P);

	if (NULL == P) {
		printf("Greska!");
		return -1;
	}
	else {
		Q = (Pozicija)malloc(sizeof(struct Cvor));

		Q->El = x;
		Q->Next = P->Next;
		P->Next = Q;
	}
	return 0;
}

int UnosIspred(int x, int y, Pozicija P) {
	Pozicija Q;

	while (P->Next != NULL && P->Next->El != y) {
		P = P->Next;
	}

	if (NULL == P->Next) {
		printf("Greska!");
		return -1;
	}

	else {
		Q = (Pozicija)malloc(sizeof(struct Cvor));

		Q->El = x;
		Q->Next = P->Next;
		P->Next = Q;
	}
	return 0;
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

Pozicija TraziPret(int x, Pozicija P) {
	Pozicija Prev;

	Prev = P;
	P = P->Next;

	while (P != NULL && P->El != x) {
		Prev = Prev->Next;
		P = P->Next;
	}

	return Prev;
}


int Brisi(int x, Pozicija P) {
	Pozicija temp = NULL;

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

int BrisiMin(Pozicija P) {
	Pozicija min = P->Next;
	Pozicija prevMin = P;

	while (P->Next != NULL) {
		if (P->Next->El < min->El) {
			prevMin = P;
			min = P->Next;
		}
		P = P->Next;
	}
	prevMin->Next = min->Next;
	free(min);

	return EXIT_SUCCESS;
}

int BrisiSve(Pozicija P) {
	Pozicija temp;

	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int BrisiSveMin(Pozicija P) {

	while (P->Next != NULL)
		BrisiMin(P);

	return EXIT_SUCCESS;
}