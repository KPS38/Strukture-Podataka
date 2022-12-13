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
	char dir[LINE_LENGTH];
	Position FC;						//FC - first child
	Position NS;						//NS - next sibling
}Node;

// "md" - napravi novi direktorij
// "cd dir" - promijena direktorija 
// "cd.." - povratak na roditeljski direktorij
//"dir" - vidi sadrzaje direktorija
//"izlaz" - obrisi sve i kraj programa

int main(void) {

	Node Root = {
		.dir = "User",
		.FC = NULL,
		.NS = NULL
	};
	char cmd[LINE_LENGTH] = { 0 };
	char dir_name[LINE_LENGTH] = { 0 };
	do {
		printf("C:\>");
		scanf(" %s", cmd);
		if (strcmp(cmd, "md") == 0)
		{
			printf("Odabrali ste unos novog direktroija, unesite ime: ");
			scanf(" %s", dir_name);
		}
		else if (strcmp(cmd, "cd dir") == 0)
		{
			// do something else
		}
		else if (strcmp(cmd, "cd dir") == 0)
		{
			// do something else
		}
		else if (strcmp(cmd, "cd..") == 0)
		{
			// do something else
		}
		else if (strcmp(cmd, "dir") == 0)
		{
			// do something else
		}
		else /* default: */
		{
			printf("Nepostojeca komanda, podjsetnik postojecih:\nmd\tcd dir\tcd..\tdir\tizlaz\n");
		}
	} while (strcmp(cmd, "izlaz") == 0);

	printf("Kraj programa\n");

	return EXIT_SUCCESS;
}





