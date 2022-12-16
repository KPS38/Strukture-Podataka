#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM_ERROR (-1)									
#define MALLOC_ERROR (0)									
#define LINE_LENGTH 128		

struct tree_node;
typedef struct tree_node* Position;

typedef struct tree_node
{
	char naziv[LINE_LENGTH];
	Position child;
	Position sibling;
}Dir;

struct stack;
typedef struct stack* Pos;

typedef struct stack
{
	Position Prethodna;
	Pos Next;
}Stog;

char direktoriji[LINE_LENGTH] = "User";
// "md" - napravi novi direktorij
// "cd dir" - promjena direktorija 
// "cd.." - povratak na roditeljski direktorij
//"dir" - vidi sadrzaje direktorija
//"izlaz" - obrisi sve i kraj programa

int Stvori(Position S);
Position Ulaz(Position S, Pos P);
int DodajNaStog(Position S, Pos P);
Position VracanjeNatrag(Pos P);
int MakniSaStoga(Pos P);
int Ispis(Position S);
int BrisiSve(Position S);
int BrisiStog(Pos P);
char* strremove(char* str, const char* sub);

int main(void) {

	Dir Root = {
		.naziv = "User",
		.child = NULL,
		.sibling = NULL
	};

	Stog Head = {
		.Next = NULL,
		.Prethodna = NULL,
	};

	Position current = &Root;
	Position temp = NULL;

	char cmd[LINE_LENGTH] = { '\0' };
	int status = 0;

	while (strcmp(cmd, "izlaz") != 0) {

		printf("\nPostojece komande: md /cd dir /cd.. /dir /izlaz ");
		printf("\nc:\\%s>", direktoriji);
		fgets(cmd, LINE_LENGTH, stdin);
		int len = strlen(cmd);
		cmd[len - 1] = '\0';

		if (strcmp(cmd, "md") == 0)
		{
			status = Stvori(current);
			if (status != 0) {
				return MALLOC_ERROR;
			}
		}
		else if (strcmp(cmd, "cd dir") == 0)
		{
			temp = Ulaz(current, &Head);
			if (temp != NULL) {
				current = temp;
			}
			else {
				printf("\nNije pronaden odgovarajuci direktorij!");
			}
		}
		else if (strcmp(cmd, "cd..") == 0)
		{
			if (current == &Root) {
				printf("\nVec ste u tom folderu!\n");
			}
			else {
				current = VracanjeNatrag(&Head);
				if (NULL == current) {
					return MALLOC_ERROR;
				}
			}
		}
		else if (strcmp(cmd, "dir") == 0)
		{
			Ispis(current);
		}
		else if (strcmp(cmd, "izlaz") == 0) {
			printf("***Brisanje stabla***\n");
			BrisiStog(Head.Next);
			BrisiSve(Root.child);
		}
		else
		{
			printf("\nNepostojeca komanda :(");
		}
		(void)getchar();
	}

	printf("Kraj programa\n");

	return EXIT_SUCCESS;
}

int Stvori(Position S) {
	Position P = S;
	Position Q = NULL;
	char dir_name[LINE_LENGTH] = { '\0' };

	printf("\nUnesite ime> ");
	scanf_s(" %s", dir_name, LINE_LENGTH);

	if (NULL == P->child) {

		Q = (Position)malloc(sizeof(Dir));
		if (NULL == Q) {
			printf("\nGreska u alociranju memorije!");
			return MALLOC_ERROR;
		}

		P->child = Q;
		Q->sibling = NULL;
		strcpy(Q->naziv, dir_name);
		Q->child = NULL;

		printf("\nKreiran novi direktorij: %s", dir_name);

		return EXIT_SUCCESS;
	}
	else {
		if (strcmp(P->child->naziv, dir_name) > 0) {

			Q = (Position)malloc(sizeof(Dir));
			if (NULL == Q) {
				printf("\nGreska u alociranju memorije!");
				return MALLOC_ERROR;
			}
			Q->sibling = P->child;
			P->child = Q;
			strcpy(Q->naziv, dir_name);
			Q->child = NULL;

			printf("\nKreiran novi direktorij: %s", dir_name);

			return EXIT_SUCCESS;
		}
		P = P->child;
		while (P->sibling != NULL && strcmp(P->sibling->naziv, dir_name) < 0) {
			P = P->sibling;
		}
		Q = (Position)malloc(sizeof(Dir));
		if (NULL == Q) {
			printf("\nGreska u alociranju memorije!");
			return MALLOC_ERROR;
		}

		Q->sibling = P->sibling;
		P->sibling = Q;
		strcpy(Q->naziv, dir_name);
		Q->child = NULL;

		printf("\nKreiran novi direktorij: %s!", dir_name);
	}

	return EXIT_SUCCESS;
}

Position Ulaz(Position S, Pos P) {
	char dir_name[LINE_LENGTH] = { 0 };

	printf("\nUnesite ime odabranog direktorija: ");
	scanf_s("%s", dir_name, LINE_LENGTH);

	Position Q = S->child;
	int status = 0;

	while (Q != NULL && strcmp(Q->naziv, dir_name) != 0) {
		Q = Q->sibling;
	}
	if (NULL == Q) {
		return NULL;
	}
	status = DodajNaStog(S, P);
	if (status != 0) {
		return NULL;
	}
	S = Q;
	strcat(direktoriji, "\\");
	strcat(direktoriji, dir_name);
	printf("\nOdabran direktorij: %s!", S->naziv);

	return S;
}

int DodajNaStog(Position S, Pos P) {
	Pos Q = NULL;
	Q = (Pos)malloc(sizeof(Stog));
	if (NULL == Q) {
		return MALLOC_ERROR;
	}

	Q->Next = P->Next;
	P->Next = Q;

	Q->Prethodna = S;

	return EXIT_SUCCESS;
}

Position VracanjeNatrag(Pos P) {
	Position current = NULL;
	current = P->Next->Prethodna;
	strremove(&direktoriji, &current->child->naziv);
	MakniSaStoga(P);

	printf("\nVratili ste se u direktorij %s", current->naziv);
	return current;
}

int MakniSaStoga(Pos P) {
	Pos temp = NULL;

	temp = P->Next;
	P->Next = temp->Next;
	free(temp);

	return EXIT_SUCCESS;
}

int Ispis(Position S) {
	Position P = S->child;
	printf("\nDatoteke u direktoriju %s su: ", S->naziv);
	while (P != NULL) {
		printf("\n> %s", P->naziv);
		P = P->sibling;
	}
	printf("\n*****************************");
	return EXIT_SUCCESS;
}

int BrisiStog(Pos P) {
	if (NULL == P) {
		return EXIT_SUCCESS;
	}
	if (P->Next != NULL) {
		BrisiStog(P->Next);
	}
	free(P);

	return EXIT_SUCCESS;
}

int BrisiSve(Position S) {
	if (NULL == S) {
		return EXIT_SUCCESS;
	}
	if (S->child != NULL) {
		BrisiSve(S->child);
	}
	if (S->sibling != NULL) {
		BrisiSve(S->sibling);
	}
	free(S);

	return EXIT_SUCCESS;
}

char* strremove(char* str, const char* sub) {
	char* p, * q, * r;
	if (*sub && (q = r = strstr(str, sub)) != NULL) {
		size_t len = strlen(sub);
		while ((r = strstr(p = r + len, sub)) != NULL) {
			memmove(q, p, r - p);
			q += r - p;
		}
		memmove(q, p, strlen(p) + 1);
	}
	return str;
}
