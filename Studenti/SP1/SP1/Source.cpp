#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define max_br_bodova 80

struct Student {
	char ime[20], prez[20];
	int br_bodova;
};

int countStudentsFromFile(char* filename);

int main(void) {
	char filename[MAX_FILE_NAME] = { 0 };
	int count = 0;

	Student* studenti;


	printf("Insert filename > ");
	scanf(" %s", &filename);
	strcat(filename, ".txt");

	studenti = (Student*)malloc(countStudentsFromFile(filename) * sizeof(Student));
	count = countStudentsFromFile(filename);
	if (count != FILE_DIDNT_OPEN_ERROR) {
	printf("Broj studenata u datoteci %s je %d.\r\n", filename, count);
	}
	return 0;
}

int countStudentsFromFile(char* filename) {
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(filename, "r");
	if (NULL == fp) {
		printf("Dear customer, the file %s didn't open!\r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_LINE, fp);
		if (strcmp(buffer, "\n") != 0) {
			count++;
		}
	}

	fclose(fp);
	return count;
}