#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_SIZE 1024

#define DIDNT_OPEN -1
#define PROGRAM_ERROR -1								
#define MALLOC_ERROR 0									
#define LINE_LENGTH 128		
#define MIN_CITY 500

struct tree_node;
typedef struct tree_node* Tree;

typedef struct tree_node
{
	char Name[MAX_LINE_SIZE];
	int BrS;
	Tree left;
	Tree right;
}City;

struct _country;
typedef struct _country* Position;

typedef struct _country {
	char CName[MAX_LINE_SIZE];
	char FName[MAX_LINE_SIZE];
	Position Next;
	Tree File;
}Country;

int citajDatoteku(char filename[], Position Head);
Tree citajDruguDatoteku(char filename[], Tree Root);

Tree SortTree(Tree P, Tree Q);
int InsertionSort(Position P, Position Head);
int cityCmp(City* c1, City* c2);

int DeleteTree(Tree S);
int DeleteList(Position Head);

int Print(Position Head, int br);
int PrintInorder(Tree Root, int br);

int main(void) {

	Country Head = {
		.CName = {0},
		.FName = {0},
		.Next = NULL,
		.File = NULL
	};

	int provjera = 0;
	int brStanovnika = 0;
	FILE* fp = NULL;
	char filename[MAX_LINE_SIZE];
	printf("Unesi ime .txt datoteke (bez .txt): ");
	scanf(" %s", filename);
	strcat(filename, ".txt");

	while (citajDatoteku(filename, &Head) == DIDNT_OPEN)
	{
		printf("\nNepravilno ime datoteke.\nUnesi ime .txt datoteke (bez .txt): ");
		scanf(" %s", filename);
		strcat(filename, ".txt");
	}

	Print(&Head, MIN_CITY);

	while (1)
	{
		printf("\n\nUnesi broj stanovnika (0 za kraj programa): ");
		scanf("%d", &brStanovnika);
		if (brStanovnika == 0)
		{
			break;
		}

		printf("Popis gradova sa vise od %d stanovnika:\n\n", brStanovnika);
		Print(&Head, brStanovnika);
	}

	printf("\n\nKraj programa.\n");
	DeleteList(&Head);

	return 0;
}

int citajDatoteku(char filename[], Position Head)
{
	FILE* fp = NULL;

	char ime_nove_datoteke[MAX_LINE_SIZE] = { 0 };
	char tempIme[MAX_LINE_SIZE] = { 0 };

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return DIDNT_OPEN;
	}


	while (!feof(fp))
	{

		Position tempLista = NULL;

		tempLista = (Position)malloc(sizeof(Country));

		if (tempLista == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return MALLOC_ERROR;
		}

		tempLista->Next = NULL;
		tempLista->File = NULL;
		strcpy(tempLista->CName, "");


		Tree root = NULL;

		root = (Tree)malloc(sizeof(City));

		if (root == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return MALLOC_ERROR;
		}

		root->right = NULL;
		root->left = NULL;

		root->BrS = 0;
		strcpy(root->Name, "");



		tempLista->File = root;


		fscanf(fp, "%s %s", tempIme, ime_nove_datoteke);
		strcpy(tempLista->CName, tempIme);
		tempLista->File = citajDruguDatoteku(ime_nove_datoteke, root);
		InsertionSort(Head, tempLista);
	}

	fclose(fp);

	return EXIT_SUCCESS;

}

Tree citajDruguDatoteku(char filename[], Tree Root)
{
	FILE* fp = NULL;
	Tree temp = NULL;
	char pom[MAX_LINE_SIZE] = { 0 };

	fp= fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NULL;
	}

	fscanf(fp, "%s %d", pom, &(Root->BrS));
	strcpy(Root->Name, pom);

	while (!feof(fp))
	{
		temp = (Tree)malloc(sizeof(City));
		if (temp == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}
		temp->left = NULL;
		temp->right = NULL;
		strcpy(temp->Name, "");
		temp->BrS= 0;

		fscanf(fp, "%s %d", pom, &(temp->BrS));
		strcpy(temp->Name, pom);

		Root = SortTree(Root, temp);
	}

	fclose(fp);

	return(Root);
}

int InsertionSort(Position P, Position Q)
{
	while ((P->Next != NULL) && strcmp((P->Next->CName), (Q->CName)) < 0)
	{
		P = P->Next;
	}

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

Tree SortTree(Tree P, Tree Q) {																
	if (P == NULL)
	{
		return Q;
	}

	int result = cityCmp(P, Q);

	if (result > 0)
	{
		P->right = SortTree(P->right, Q);
	}

	else if (result < 0)
	{
		P->left = SortTree(P->left, Q);
	}

	else
	{
		free(Q);
	}

	return P;
}

int cityCmp(City* c1, City* c2) {
	int result = 0;
	result = c1->BrS - c2->BrS;
	if (result == 0) {
		result = strcmp(c2->Name, c1->Name);
	}

	return result;
}

int DeleteTree(Tree Root)
{
	if (Root == NULL)
	{
		return EXIT_SUCCESS;
	}

	else if (Root->left != NULL)
	{
		DeleteTree(Root->left);
	}


	if (Root->right != NULL)
	{
		DeleteTree(Root->right);
	}

	free(Root);

	return EXIT_SUCCESS;
	
}

int DeleteList(Position Head)
{
	Position temp = NULL;

	while (Head->Next != NULL)
	{
		DeleteTree(Head->Next->File);
		temp = Head->Next;
		Head->Next = temp->Next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int Print(Position Head, int br)
{
	while (Head->Next != NULL)
	{
		printf("%s:", Head->Next->CName);
		printf("\n");
		PrintInorder(Head->Next->File, br);
		Head = Head->Next;
		printf("\n\n");
	}

	return EXIT_SUCCESS;
}

int PrintInorder(Tree Root, int br)
{
	if (Root == NULL)
	{
		return EXIT_SUCCESS;
	}

	PrintInorder(Root->left, br);
	if (Root->BrS > br)
	{
		printf("\t%s:\t%d\n", Root->Name, Root->BrS);

	}
	PrintInorder(Root->right, br);

	return EXIT_SUCCESS;
}