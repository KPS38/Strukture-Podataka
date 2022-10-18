#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define max_br_bodova 80

typedef struct {
	char ime[20], prez[20];
	int rez;
}Student;

int countStudentsFromFile(char* filename);
void ispisStudenata(int count, char* filename , Student* studenti);

int main(void) {
	char filename[MAX_FILE_NAME] = { 0 };
	int count = 0;

	Student* studenti;


	printf("Unesite ime .txt dokumenta: ");
	scanf(" %s", &filename);
	strcat(filename, ".txt");

	count = countStudentsFromFile(filename);
	studenti = (Student*)malloc(count * sizeof(Student));
	if (count != FILE_DIDNT_OPEN_ERROR) {
	printf("Broj studenata u datoteci %s je %d.\r\n", filename, count);
	}

	ispisStudenata(count, filename, studenti);

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

	while (fscanf(fp, "%s", filename) != EOF) {
		fgets(buffer, MAX_LINE, fp);
		if (strcmp(buffer, "\n") != 0) {
			count++;
		}
	}
	fclose(fp);
	return count;
}

void ispisStudenata(int count, char* filename, Student* studenti) {
	FILE* fp = NULL;
	int i=0;

	fp = fopen(filename, "r");

	printf("Ime\t\tPrezime\t\tRezultat\t\tPostotak prolaznost\n");
	while (fscanf(fp, "%s", filename) != EOF) {
		for (i = 0; i < count; i++) {
			fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prez, &studenti[i].rez);
			printf("%s\t\t%s\t\t%d\t\t%f\n", studenti[i].ime, studenti[i].prez, studenti[i].rez, float(max_br_bodova)/float(studenti[i].rez)*100);
		}
	}
	fclose(fp);
}