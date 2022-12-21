#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}node;

Tree StvoriPrazno(Tree S);
Position TraziMin(Tree S);
Position TraziMax(Tree S);
Position Trazi(int X, Tree S);
Tree Dodaj(int X, Tree S);
Tree Brisi(int X, Tree S);
int InorderIspis(Tree S);
int PreorderIspis(Tree S);
int PostorderIspis(Tree S);
int LevelorderIspsi(Tree S);

int main(void) {
	int rval = 0;
	printf("Unesi vrijednost root-a (veci od nula)>");
	scanf(" %d", &rval);
	while (rval <= 0) {
		printf("\nA brate ne gnjavi nego napravi kako valja>");
		scanf(" %d", &rval);
	}
	int op = 0;
	node Root = {
		.val = rval,
		.left = NULL,
		.right = NULL
	};

	do{
	op = 0;
	printf(
		"*\t*\t*\t*\n"
		"Odaberite zeljenu operaciju:\n"
		"1) Unos elementa\n"
		"2) Inorder ispis\n"
		"3) Preorder ispis\n"
		"4) Postorder ispis\n"
		"5) Level order ispis\n"
		"6) Briši element\n"
		"7) Traži element\n"
		"0) Izlaz\n"
		"*\t*\t*\t*\n");
	scanf_s(" %d", &op);

		switch (op) {
		case 1:
			printf("Unos elementa...\nVrijednost>");
			scanf(" %d", &rval);
			Dodaj(rval, &Root);
			break;
		case 2:
			printf("Inorder ispis...\n");
			InorderIspis(&Root);
			break;
		case 3:
			printf("Preorder ispis...\n");
			PreorderIspis(&Root);
			break;
		case 4:
			printf("Postorder ispis...\n");
			PostorderIspis(&Root);
			break;
		case 5:
			printf("Level order ispis...\n");
			LevelorderIspis(&Root);
			break;
		case 6:
			printf("Briši elemement...\nVrijednost>");
			scanf(" %d", &rval);
			Brisi(rval, &Root);
			break;
		case 7:
			printf("Traži element...\nVrijednost>");
			scanf(" %d", &rval);
			Trazi(rval, &Root);
			break;
		case 0:
			printf("Izlaz...\n");
			break;
		}
	} while (op != 0);
	return EXIT_SUCCESS;
}

Tree StvoriPrazno(Tree S) {
	if (NULL == S) {
		StvoriPrazno(S->left);
		StvoriPrazno(S->right);
		free(S);
	}
	return EXIT_SUCCESS;
}

Position TraziMin(Tree S) {
	if (NULL == S) {
		return NULL;
	}
	if (NULL == S->left) {
		return S;
	}
	return TraziMin(S->left);
}

Position TraziMax(Tree S) {
	if (NULL == S) {
		return NULL;
	}
	if (NULL == S->right) {
		return S;
	}
	return TraziMin(S->right);
}

Position Trazi(int X, Tree S) {
	if (NULL == S) {
		return NULL;
	}
	if (X < S->val) {
		Trazi(X, S->left);
	}
	else if (X > S->val) {
		Trazi(X, S->right);
	}
	else {
		return S;
	}
}

Tree Dodaj(int X, Tree S) {
	if (NULL == S) {
		S = (Tree)malloc(sizeof(Tree));
		S->val = X;
		S->left = NULL;
		S->right = NULL;
	}
	if (X < S->val) {
		S->left = Dodaj(X, S->left);
	}
	else if (X > S->val) {
		S->right = Dodaj(X, S->right);
	}
	return S;
}

Tree Brisi(int X, Tree S) {

}

int InorderIspis(Tree S) {
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	InorderIspis(S->left);
	printf(S->val);
	InorderIspis(S->right);
	return EXIT_SUCCESS;
}

int PreorderIspis(Tree S) {
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	printf(S->val);
	PreorderIspis(S->left);
	PreorderIspis(S->right);
	return EXIT_SUCCESS;
}

int PostorderIspis(Tree S) {
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	PostorderIspis(S->left);
	PostorderIspis(S->right);
	printf(S->val);
	return EXIT_SUCCESS;
}

int LevelorderIspis(Tree S) {

}