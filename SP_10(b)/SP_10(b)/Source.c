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

struct city;
typedef struct city* Position;

typedef struct city
{
	char Name[MAX_LINE_SIZE];
	int BrS;
	Position Next;
}City;

struct country;
typedef struct country* Tree;

typedef struct country {
	char CName[MAX_LINE_SIZE];
	Tree left;
	Tree right;
	Position File;
}Country;

Tree ReadFile(char filename[], Tree Root);
int ReadFile2(char filename[], Position Head);

Tree SortTree(Tree P, Tree Q);
int InsertionSort(Position P, Position Head);
int cityCmp(City* c1, City* c2);

int DeleteTree(Tree S);
int DeleteList(Position Head);

int Print(Position Head, int br);
int PrintInorder(Tree Root, int br);

int main(void) {
	Tree root = NULL;
	root = (Tree)malloc(sizeof(Country));
	Tree root2 = NULL;
	root2 = root;

	root->right = NULL;
	root->left = NULL;

	int provjera = 0;
	int brStanovnika = 0;
	FILE* fp = NULL;
	char filename[MAX_LINE_SIZE];
	printf("Unesi ime .txt datoteke (bez .txt): ");
	scanf(" %s", filename);
	strcat(filename, ".txt");

	root = ReadFile(filename, root);
	while (root == NULL)
	{
		printf("\nNepravilno ime datoteke.\nUnesi ime .txt datoteke (bez .txt): ");
		scanf(" %s", filename);
		strcat(filename, ".txt");
		root = ReadFile(filename, root);
	}

	PrintInorder(root, MIN_CITY);

	while (1)
	{
		printf("\n\nUnesi broj stanovnika (0 za kraj programa): ");
		scanf("%d", &brStanovnika);
		if (brStanovnika == 0)
		{
			break;
		}

		printf("Popis gradova sa vise od %d stanovnika:\n\n", brStanovnika);
		PrintInorder(root, brStanovnika);
	}

	printf("\n\nKraj programa.");
	DeleteTree(root);

	return 0;
}

Tree ReadFile(char filename[], Tree Root)
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

	Position head = NULL;

	head = (Position)malloc(sizeof(City));

	if (head == NULL)
	{
		printf("Neuspjesna alokacija memorije!");
		return NULL;
	}

	head->Next = NULL;

	head->BrS = 0;
	strcpy(head->Name, "");

	fscanf(fp, "%s %s", tempIme, ime_nove_datoteke);
	strcpy(Root->CName, tempIme);
	ReadFile2(ime_nove_datoteke, head);
	Root->File = head;

	while (!feof(fp))
	{
		Tree tempRoot = NULL;

		tempRoot = (Tree)malloc(sizeof(Country));

		if (tempRoot == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}

		tempRoot->left = NULL;
		tempRoot->right = NULL;
		tempRoot->File = NULL;
		strcpy(tempRoot->CName, "");

		Position head = NULL;

		head = (Position)malloc(sizeof(City));

		if (head == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}

		head->Next= NULL;
		tempRoot->File = head;


		fscanf(fp, "%s %s", tempIme, ime_nove_datoteke);
		strcpy(tempRoot->CName, tempIme);
		ReadFile2(ime_nove_datoteke, head);
		tempRoot->File = head;
		Root = SortTree(Root, tempRoot);
	}

	fclose(fp);

	return Root;

}

int ReadFile2(char filename[], Position Head)
{
	FILE* fp = NULL;
	Position temp = NULL;
	char pom[MAX_LINE_SIZE] = { 0 };

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NULL;
	}

	fscanf(fp, "%s %d", pom, &(Head->BrS));
	strcpy(Head->Name, pom);

	while (!feof(fp))
	{
		temp = (Position)malloc(sizeof(City));
		if (temp == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}
		temp->Next = NULL;
		strcpy(temp->Name, "");
		temp->BrS = 0;

		fscanf(fp, "%s %d", pom, &(temp->BrS));
		strcpy(temp->Name, pom);

		InsertionSort(Head, temp);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int InsertionSort(Position P, Position Q)
{
	while ((P->Next != NULL) && (cityCmp(P->Next, Q) > 0))
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

	int rezultat = 0;
	rezultat = strcmp(P->CName, Q->CName);

	if (rezultat < 0)
	{
		P->right = SortTree(P->right, Q);
	}

	else if (rezultat > 0)
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

	DeleteList(Root->File);
	free(Root);

	return EXIT_SUCCESS;
}

int DeleteList(Position Head)
{
	Position temp = NULL;

	while (Head->Next != NULL)
	{
		temp = Head->Next;
		Head->Next = temp->Next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int Print(Position Head, int br)
{
	while (Head->Next != NULL && (Head->Next->BrS > br))
	{
		printf("\t%s:\t%d", Head->Next->Name, Head->Next->BrS);
		printf("\n");
		Head = Head->Next;
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
	printf("%s:", Root->CName);
	printf("\n");
	Print(Root->File, br);
	printf("\n\n");
	PrintInorder(Root->right, br);

	return EXIT_SUCCESS;
}