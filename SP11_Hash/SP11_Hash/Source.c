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
#define MAX_HASH_SIZE 11

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

struct node;
struct _hashT;
typedef Position List;
typedef struct _hashT* hashTab;

typedef struct _hashT {
	int tab_size;
	List *list;
}hashT;

hashTab InitiateTable(int size);
int DeleteHashTable(hashTab H);
int calcIndex(char* name);

int citajDatoteku(char filename[], hashTab H);
Tree citajDruguDatoteku(char filename[], Tree Root);

Tree SortTree(Tree P, Tree Q);
int InsertionSort(Position P, Position Head);
int cityCmp(City* c1, City* c2);

int DeleteTree(Tree S);
int DeleteList(Position Head);

int Print(Position Head, int br);
int PrintInorder(Tree Root, int br);



int main(void) {

	hashTab H = NULL;
	H = InitiateTable(MAX_HASH_SIZE);
	int provjera = 0;
	int brStanovnika = 0;
	FILE* fp = NULL;
	char filename[MAX_LINE_SIZE];
	printf("Unesi ime .txt datoteke (bez .txt): ");
	scanf(" %s", filename);
	strcat(filename, ".txt");

	while (citajDatoteku(filename, H) == DIDNT_OPEN)
	{
		printf("\nNepravilno ime datoteke.\nUnesi ime .txt datoteke (bez .txt): ");
		scanf(" %s", filename);
		strcat(filename, ".txt");
	}

	Print(H, MIN_CITY);

	while (1)
	{
		printf("\n\nUnesi broj stanovnika (0 za kraj programa): ");
		scanf("%d", &brStanovnika);
		if (brStanovnika == 0)
		{
			break;
		}

		printf("Popis gradova sa vise od %d stanovnika:\n\n", brStanovnika);
		Print(H, brStanovnika);
	}

	printf("\n\nKraj programa.\n");
	DeleteHashTable(H);

	return 0;
}

int citajDatoteku(char filename[], hashTab H)
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
		int index = 0;
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
		index=calcIndex(tempIme);
		strcpy(tempLista->CName, tempIme);
		tempLista->File = citajDruguDatoteku(ime_nove_datoteke, root);
		InsertionSort(H->list[index], tempLista);
	}

	fclose(fp);

	return EXIT_SUCCESS;

}

Tree citajDruguDatoteku(char filename[], Tree Root)
{
	FILE* fp = NULL;
	Tree temp = NULL;
	char pom[MAX_LINE_SIZE] = { 0 };

	fp = fopen(filename, "r");
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
		temp->BrS = 0;

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

	while (Head != NULL)
	{
		DeleteTree(Head->File);
		temp = Head->Next;
		Head->Next = temp->Next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int Print(hashTab H, int br)
{
	int i = 0;
	for (i = 0; i < H->tab_size; i++) {
		while (H->list[i]->Next != NULL)
		{
			printf("%s:", H->list[i]->Next->CName);
			printf("\n");
			PrintInorder(H->list[i]->Next->File, br);
			H->list[i]->Next = H->list[i]->Next->Next;
			printf("\n\n");
		}
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

int calcIndex(char* name) {
	int len = 0;
	int i = 0;
	int sum = 0;

	if (name == NULL) {
		return EXIT_SUCCESS;
	}

	len = strlen(name);

	len = (len < 5) ? len : 5;
	for (i = 0; i < len; i++) {
		sum += name[i];
	}
	return sum % MAX_HASH_SIZE;
}

hashTab InitiateTable(int size) {
	hashTab H;
	int i = 0;

	H = (hashTab)malloc(sizeof(hashT));

	if (H == NULL) {
		printf("\nMalloc error!");
		free(H);
		return NULL;
	}

	H->tab_size = size;

	H->list = (List)malloc(sizeof(List) * H->tab_size);

	if (H->list == NULL) {
		printf("\nMalloc error!");
		free(H);
		return NULL;
	}

	for (i = 0; i < H->tab_size; i++)
	{

		H->list[i] = (List)malloc(sizeof(Country));
		if (H->list == NULL) {
			printf("\nMalloc error!");
			free(H);
			return NULL;
		}
		else
			H->list[i]->Next = NULL;
	}
	return H;
}

int DeleteHashTable(hashTab H) {
	int i = 0;
	for (i = 0; i < H->tab_size; i++)
	{
		DeleteList(H->list[i]->Next);
	}
	free(H);
	return EXIT_SUCCESS;
}