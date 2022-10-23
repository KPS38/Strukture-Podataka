#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (1024)

struct _person;
typedef struct _person* Position;
typedef struct _person {
	char firstName[MAX_LINE];
	char lastName[MAX_LINE];
	int birthYear;
	Position next;
}osoba;

int main(void) {
	osoba Head = {
		Head.firstName = { 0 };
		Head.lastName = { 0 };
		Head.birthYear = 0;
		Head.next = NULL;
	}
	return EXIT_SUCCESS;
}