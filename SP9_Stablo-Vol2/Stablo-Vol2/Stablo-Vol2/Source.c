#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_SIZE 1024

#define DIDNT_OPEN -1
#define PROGRAM_ERROR (-1)									
#define MALLOC_ERROR (0)									
#define LINE_LENGTH 128		

struct tree_node;
typedef struct tree_node* Tree;
typedef struct tree_node* Position;

typedef struct tree_node
{
	int val;
	Tree left;
	Tree right;
}Node;

Tree NewNode(int X);
Tree Insert(int X, Tree S);
int BrisiSve(Tree S);
int Replace(Tree S);
int Visina(Tree S);
int TrenutniLevel(Tree S, int level);
int LevelOrderIspis(Tree S);
int Count(Tree S);
int Random(Tree S, int count);
int UnosDat(FILE *fp, Tree S);

int main(void) 
{
	Node Root = {
		.val = 2,
		.left = NULL,
		.right = NULL
	};
	Node NRoot = {
		.val = 0,
		.left = NULL,
		.right = NULL
	};
	FILE* fp = NULL;
	fp = fopen("file1.txt", "w");

	Insert(5, &Root);
	Insert(7, &Root);
	Insert(8, &Root);
	Insert(11, &Root);
	Insert(7, &Root);
	Insert(1, &Root);
	Insert(4, &Root);
	Insert(2, &Root);
	Insert(3, &Root);
	

	LevelOrderIspis(&Root);
	printf("\n");
	Replace(&Root);
	LevelOrderIspis(&Root);
	printf("\n");

	int count = Count(&Root);

	BrisiSve(Root.left);
	BrisiSve(Root.right);


	Random(&NRoot, count);

	LevelOrderIspis(&NRoot);
	printf("\n");
	UnosDat(fp, &NRoot);

	Replace(&NRoot);

	LevelOrderIspis(&NRoot);
	printf("\n");
	UnosDat(fp, &NRoot);
	fprintf(fp, "\n\n");

	BrisiSve(NRoot.left);
	BrisiSve(NRoot.right);
	fclose(fp);
	return EXIT_SUCCESS;
}

Tree NewNode(int X) {
	Tree S = (Tree)malloc(sizeof(Node));
	if (S == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return MALLOC_ERROR;
	}
	S->val = X;
	S->left = NULL;
	S->right = NULL;
	return S;
}
Tree Insert(int X, Tree S) 
{
	if (NULL == S) {
		return NewNode(X);
	}

	if (X < S->val) {
		S->right = Insert(X, S->right);
	}
	else {
		S->left = Insert(X, S->left);
	}

	return S;
}

int BrisiSve(Tree S) 
{
	if (S == NULL) {
		return EXIT_SUCCESS;
	}

	BrisiSve(S->left);
	BrisiSve(S->right);
	free(S);
}

int Replace(Tree S) 
{
	if (S == NULL) {
		return 0;
	}

	int left=Replace(S->left);
	int right=Replace(S->right);
	
	int old = S->val;

	S->val = left + right;

	return S->val + old;
}

int Visina(Tree S)
{
	if (S == NULL)
		return EXIT_SUCCESS;
	else {
		int lvisina = Visina(S->left);
		int rvisina = Visina(S->right);

		if (lvisina > rvisina)
			return (lvisina + 1);
		else
			return (rvisina + 1);
	}
}

int TrenutniLevel(Tree S, int level)
{
	if (S == NULL)
		return EXIT_SUCCESS;
	if (level == 1)
		printf("%d ", S->val);
	else if (level > 1) {
		TrenutniLevel(S->left, level - 1);
		TrenutniLevel(S->right, level - 1);
	}
	return EXIT_SUCCESS;
}

int LevelOrderIspis(Tree S) 
{
	int h = Visina(S);
	int i = 0;
	for (i = h; i > 0; i--)
		TrenutniLevel(S, i);
}

int Count(Tree S){
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	else {
		return 1 + Count(S->left) + Count(S->right);
	}
}

int Random(Tree S, int count) {
	int i = 0;
	int R = 0;

	srand(time(0));

	for (i = 0; i < count; i++) {
		R = (rand() % (90 - 10 + 1)) + 10;
		if (i == 0) {
			S->val = R;
		}
		else {
			Insert(R, S);
		}
	}

	return EXIT_SUCCESS;
}


int UnosDat(FILE *fp, Tree S)
{
	int* R = NULL;
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	UnosDat(fp, S->right);
	fprintf(fp, "%d ", S->val);
	UnosDat(fp, S->left);
	return EXIT_SUCCESS;
}
