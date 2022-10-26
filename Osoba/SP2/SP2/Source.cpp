#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (1024)
#define PROGRAM_ERROR (-1)


typedef struct osoba* Position;
struct osoba {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int godina;
	Position Next;
};

int BrisiSve(Position P);
int UnosP(Position P);
int UnosK(Position P);
Position Trazi(Position P);
int Brisi(Position P);
int Ispis(Position P);


int main(void) {
	struct osoba Head;
	Head.Next = NULL;
	int op = 0;
	Position P;

		do {
			printf("Odaberite zeljenu operaciju:\n1) Dodaj na pocetak\n2) Dodaj na kraj\n3) Trazi po prezimenu\n4) Brisi zeljeni element\n5) Ispis liste\n0) Izlaz\n");
			scanf("%d", &op);

			switch (op) {													//radi jebeno
				case 1:
					printf("Odabrali ste unos na pocetak:\n");
					UnosP(&Head);
					break;
				case 2:
					printf("Odabrali ste unos na kraj:\n");
					UnosK(&Head);
					break;
				case 3:
					printf("Odabrali ste trazenje po prezimenu:\n");
					Trazi(Head.Next);
					printf("Trazena osoba nalazi se na %p adresi.\n", &P);
					break;
				case 4:
					printf("Odabrali ste brisanje elementa:\n");
					Brisi(&Head);
					break;
				case 5:
					printf("Odabrali ste ispis liste:\n");
					Ispis(Head.Next);
					break;
				case 0:
					printf("Odabrali ste izlaz:\n");
					break;
			}
		
		
		
		
		
		} while (op != 0);

		printf("Ciscenje memorije je vrlo vazno...\n");
		BrisiSve(&Head);
		return EXIT_SUCCESS;
	}

int BrisiSve(Position P) {
	Position temp;
	while (P->Next != NULL)										//konacno brisanje stavljeno u posebnu funkciju
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}
	
int UnosP(Position P) {
	char novoIme[MAX_LINE] = { 0 };
	char novoPrezime[MAX_LINE] = { 0 };
	int novaGodina = 0;
	Position Q;

	Q = (Position)malloc(sizeof(struct osoba));

	printf("Ime nove osobe: ");
	scanf("%s", novoIme);
	strcpy(Q->ime, novoIme);
	printf("Prezime nove osobe: ");
	scanf("%s", novoPrezime);
	strcpy(Q->prezime, novoPrezime);
	printf("Godina rodenja nove osobe: ");
	scanf("%d", &novaGodina);
	Q->godina = novaGodina;
	
	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int UnosK(Position P) {	
	char novoIme[MAX_LINE] = { 0 };
	char novoPrezime[MAX_LINE] = { 0 };
	int novaGodina = 0;
	Position Q;

	while (P->Next != NULL) {
		P = P->Next;
	}

	Q = (Position)malloc(sizeof(struct osoba));

	printf("Ime nove osobe: ");
	scanf("%s", novoIme);
	strcpy(Q->ime, novoIme);
	printf("Prezime nove osobe: ");
	scanf("%s", novoPrezime);
	strcpy(Q->prezime, novoPrezime);
	printf("Godina rodenja nove osobe: ");
	scanf("%d", &novaGodina);
	Q->godina = novaGodina;
	P->Next = Q;
	Q->Next = NULL;

	return EXIT_SUCCESS;
}
Position Trazi(Position P) {											//ispisuje mi istu adresu za sve
	char trazenoPrezime[MAX_LINE] = { 0 };
	Position Q;

	Q = (Position)malloc(sizeof(struct osoba));

	while (P != NULL && P->prezime != trazenoPrezime) {
		P = P->Next;
	}

	printf("Prezime trazene osobe: ");
	scanf("%s", trazenoPrezime);
	strcpy(Q->prezime, trazenoPrezime);

	return P;
}
int Brisi(Position P) {
	char tempIme[MAX_LINE] = { 0 };
	Position Q;
	Position temp = NULL, prev;

	Q = (Position)malloc(sizeof(struct osoba));

	printf("Ime osobe koju zelite izbrisati: ");
	scanf("%s", tempIme);
	strcpy(Q->ime, tempIme);

	while (P-> Next != NULL && P-> Next-> prezime != tempIme){
		P = P->Next;
	}
	if (NULL == P) {
		printf("Trazena osoba nije upisana u strukturu");
		return PROGRAM_ERROR;
	}
	else {
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int Ispis(Position P) {
	while (P != NULL) {
		printf("%s ", P->ime);
		printf("%s ", P->prezime);
		printf("%d\n", P->godina);
		P = P->Next;
	}
	printf("\n");
	return EXIT_SUCCESS;
}