#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (1024)

struct _person;
typedef struct _person* Position;
typedef struct _person {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int godina;
	Position Next;
}osoba;

int UnosIspred(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);
int UnosIza(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);
int Trazi(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);
int Brisi(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);
void Ispis(Position P);


int main(void) {
	int op = 0;
	osoba* Head = NULL;					//inicijalizacija memorije, doda sam nas dvojicu cisto da ne bude prazno 
	osoba* Prvi = NULL;
	osoba* Drugi = NULL;
	osoba* tmp = NULL;

	Prvi = (osoba*)malloc(sizeof(osoba));		//alociranje
	Drugi = (osoba*)malloc(sizeof(osoba));


	strcpy(Prvi->ime, "Pjero Toni");						//pridodavanje vrijednosti
	strcpy(Prvi->prezime, "Radiq");
	Prvi->godina = 2002;

	strcpy(Drugi->ime, "Kristijan");						//pridodavanje vrijednosti
	strcpy(Drugi->prezime, "Padovan Saviq");
	Drugi->godina = 2002;

	Prvi->Next = Drugi;						//povezivanje liste
	Drugi->Next = NULL;

	Head = Prvi;

		do {
			printf("Odaberite zeljenu operaciju:\n1) Dodaj na pocetak\n2) Dodaj na kraj\n3) Trazi po prezimenu\n4) Brisi zeljeni element\n5) Ispis liste\n0) Izlaz\n");
			scanf("%d", &op);

			switch (op) {													//radi jebeno
				case 1:
					printf("Odabrali ste unos na pocetak:\n");
					break;
				case 2:
					printf("Odabrali ste unos na kraj:\n");
					break;
				case 3:
					printf("Odabrali ste trazenje po prezimenu:\n");
					break;
				case 4:
					printf("Odabrali ste brisanje elementa:\n");
					break;
				case 5:
					printf("Odabrali ste ispis liste:\n");
					Ispis(Head);
					break;
				case 0:
					printf("Odabrali ste izlaz:\n");
					break;
			}
		
		
		
		
		
		} while (op != 0);

		printf("Ciscenje memorije je vrlo vazno...");
		while (Head != NULL)										//ciscenje alocirane memorije na kraju
		{
			tmp = Head;
			Head = Head->Next;
			free(tmp);
		}
		return EXIT_SUCCESS;
	}
	
int UnosIspred(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);				//sritno ti s ovim meni se spajki
int UnosIza(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);				
int Trazi(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);
int Brisi(char ime[MAX_LINE], char prezime[MAX_LINE], int godina, Position P);

void Ispis(Position temp) {														//ka napravia sam samom ispis
	while (temp!= NULL) {
		printf("%s ", temp->ime);
		printf("%s ", temp->prezime);
		printf("%d\n", temp->godina);
		temp = temp->Next;
	}
	printf("\n");
}