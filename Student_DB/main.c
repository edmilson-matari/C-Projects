// main - Created on Wed Jul 10 11:29:23 WAT 2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	char name[100];
	int id;
	int grade;
} Student;

int add_student(Student** student, int* count) {
	*student  = realloc(*student, (*count + 1) * sizeof(Student));
	if (!student) {
		printf("fail to realloc memory");
		return 1;
	}
	Student* new_student = &(*student)[*count];
	new_student->id = *count + 1;
	printf("Student Name: ");
	scanf(" %[^\n]s", new_student->name);
	printf("Insert Student Grade: ");
	scanf("%d", &new_student->grade);
	while (new_student->grade < 0 || new_student->grade > 100) {
		printf("Please insert a grade between 0 and 100: ");
		scanf("%d", &new_student->grade);
	}
	(*count)++;
	printf("Student succefully added\n\n");
	return 0;
}

void save_file(Student** student, int* count,  const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) {
		printf("Fail opening the file!\n");
		return;
	}
	for (int i = 0; i < *count; i++) {
		fprintf(file, "%d-%d-%s\n", 
				(*student + i)->id,
				(*student + i)->grade,
				(*student + i)->name);
	}
	fclose(file);
}

int load_file(Student** student, int* count, const char* filename) {
	FILE* file = fopen(filename, "r");
	int grade;
	if (!file) {
		printf("Fail opening file!\n");
		return 1;
	}
	char line[100];
	while (fgets(line, sizeof(line), file) != NULL) {
		*student = realloc(*student, (*count + 1) * sizeof(Student));
		Student* new_student = &(*student)[*count];

		if (sscanf(line, "%d-%d-%[^\n]s",
					&new_student->id,	
					&new_student->grade,
					new_student->name)) {
			(*count)++;
		} else
			printf("Skipping bad formatted line\n");
	}
	fclose(file);
	printf("Loaded %d data from %s\n", *count, filename);
	return 0;
}

int find_student(Student** student, int* count, int id_to_find) {
	for (int i = 0; i < *count; i++) {
		if ((*student + i)->id == id_to_find) {
			return i;
		}
	}
	return -1;
}

int delete_student(Student** student, int* count, int id_to_delete) {
	int found_index;

	found_index = find_student(student, count, id_to_delete);
	if (found_index == -1) {
		printf("ID not found %d\n", id_to_delete);
		return 1;
	}              

	for (int i = found_index; i < *count - 1; i++) {
		(*student)[i] = (*student)[i + 1];
		(*student)[i].id = i + 1;
	}

	(*count)--;
	*student = realloc(*student, *count * sizeof(Student));
	printf("Student with ID: %d succefully deleted\n\n", id_to_delete);
}

void display_students(Student** student, int* count) {
	int total = 0;
	int average;
	int i;
	printf("%-10s %-20s %-10s\n", "ID", "Name", "Grade");
	for (i = 0; i < *count; i++) {
		printf("%-10d %-20s %-10d", (*student)[i].id
				, (*student)[i].name
				, (*student)[i].grade);
		printf("\n");
		total += (*student + i)->grade;
	}
	average = total / i;
	printf("%-30s  %-10d\n", "Average", average);
	printf("\n");
}

int edit_student(Student** student, int id_to_edit, int* count) {
	int found_index;
	int choice;

	found_index = find_student(student, count, id_to_edit);
	if (found_index == -1) {
		printf("Student with ID %d not found\n", id_to_edit);
		return 1;
	}
	while (choice != 3) {
		printf("Student: %-10s Grade: %d\n",
				(*student + found_index)->name,
				(*student + found_index)->grade);
		printf("1. Edit Name\n2. Edit Grade\n3. Exit\nChoice: ");
		scanf("%d", &choice);
		if (choice == 1) {
			printf("Write the name: ");
			scanf(" %[^\n]s", (*student + found_index)->name);
		} else if (choice == 2) {
			printf("Write the grade: ");
			scanf("%d", &(*student + found_index)->grade);
		} else if (choice == 3)
			break;
	}
	printf("Student with ID: %d succefully changed\n", id_to_edit);
	return 0;
}

void sort_student_alpha(Student** student, int* count) {
	char temp[50];
	for (int i = 0; i < *count; i++) {
		for (int j = i; j < *count; j++) {
			if ((*student + i)->name[0] > (*student + j)->name[0]) {
				strcpy(temp, (*student + i)->name);
				strcpy((*student + i)->name, (*student + j)->name);
				strcpy((*student + j)->name, temp);
			}
		}
	}
}


int	main(void) {
	//code here
	Student* student = NULL;
	int count = 0;
	int choice;
	int id;
	int added = -1;
	const char filename[40] = "student_db.txt";

	load_file(&student, &count, filename);
	sort_student_alpha(&student, &count);
	while ( choice != 5) {
	sort_student_alpha(&student, &count);
		printf("1. Add a Student\n2. See Students\n3. Edit Student\n4. Delete Student\n5. Exit\nChoice: ");
		scanf("%d", &choice);
		if (choice == 1) {
			add_student(&student, &count);
			added = 1;
		} else if (choice == 2) {
			if (count == 0) {
				printf("No students in the list\n\n");
			}
			else
				display_students(&student, &count);
		} else if (choice == 3) {
			printf("ID to edit: ");
			scanf("%d", &id);
			edit_student(&student, id, &count);
			added = 1;
		}else if(choice == 4)
			if (count == 0) {
				printf("No students on the data base\n\n");
			} else {
				printf("Insert the ID to delete a student: ");
				scanf("%d", &id);
				delete_student(&student, &count, id);
				added = 1;
			} else if (choice == 5)
			break;
	}
	if (added == 1) {
		save_file(&student, &count, filename);
	}
	free(student);
	return 0;
}

