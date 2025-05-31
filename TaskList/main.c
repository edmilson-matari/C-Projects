// main - Created on Wed Jul 10 13:30:08 WAT 2024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int id;
	char description[100];
	char due_date[11];
	int priority;
} Task;

void add_task(Task** tasks, int* count) {
	*tasks = realloc(*tasks, (*count + 1) * sizeof(Task));
	Task* new_task = &(*tasks)[*count];
	new_task->id = *count + 1;
	printf("Entter description: ");
	scanf(" %[^\n]s", new_task->description);
	printf("Enter due date (YYYY-MM-DD): ");
	scanf("%s", &new_task->due_date);
	printf("Enter priority (1-3): ");
	scanf("%d", &new_task->priority);
	while (new_task->priority < 1 || new_task->priority > 3) {
		printf("Insert a valid priority value: ");
		scanf("%d", &new_task->priority);
	}
	(*count)++;
	printf("Task added!\n");
}

void display_list_task(Task** task, int* count) {
	int n = 0;
	printf("%-10s %-20s %-10s %-10s\n",
			"ID",
			"Task",
			"Priority",
			"Due Date");
	while (n < *count) {
		printf("%-10d %-20s %-10d %-20s\n", (*task + n)->id,
			((*task + n)->description), (*task + n)->priority, (*task + n)->due_date);
		n++;
	}
}

void write_file(Task** task, int* count) {
	FILE* fp = fopen("tasks.txt", "w");
	int n = 0;
	if (!fp) {
		perror("Fail opening the file");
		return ;
	}
	while (n < *count) {
		fprintf(fp, "%d,%s,%d,%s,\n",
				(*task + n)->id,
				(*task + n)->description,
				(*task + n)->priority,
				(*task + n)->due_date);
		n++;
	}
	printf("Saved %d task %s\n", n, "tasks.txt");
	fclose(fp);
}


int load_file(Task** task, int* count) {
	FILE* fp = fopen("tasks.txt", "r");
	if (!fp) {
		perror("fail opening the file");
		return 0;
	}
	char line[150];
	while (fgets(line, sizeof(line), fp) != NULL) {
		*task = realloc(*task, (*count + 1) * sizeof(Task));
		Task* new_task = &(*task)[*count];

		if (sscanf(line, "%d,%99[^,],%d,%10[^,]",
					&new_task->id,
					new_task->description,
					&new_task->priority,
					new_task->due_date) == 4)
		{
			(*count)++;
		}
		else {
			printf("Warning: skipping malformed line %s", line);
		}
	}
	fclose(fp);
	printf("Loaded %d tasks from ", *count);
	return *count;
}

int find_task(Task** task, int* count, int id_to_delete) {
	int b = 0;
	int e = *count - 1;

	while (b <= e) {
		int middle = b + (e - b) / 2;
		if ((*task + middle)->id == id_to_delete) {
			return middle;
		}
		if ((*task + middle)->id < id_to_delete) {
			b = middle + 1;
		} else
			e = middle - 1;
	}
	return -1;
}

int delete_task(Task** tasks, int* count, int id_to_delete) {
	int found_index;
	
	found_index = find_task(tasks, count, id_to_delete);

	if (found_index == -1) {
		printf("Task with id %d not found\n", id_to_delete);
		return 0;
	}

	for (int i = found_index; i < *count - 1; i++) {
		(*tasks)[i] = (*tasks)[i + 1];
		(*tasks)[i].id = i + 1;
	}
	(*count)--;
	*tasks = realloc(*tasks, *count * sizeof(Task));
	if (*count > 0 && *tasks == NULL) {
		printf("Error: Memory realloc failed.\n");
		exit(1);
	}

	printf("Task with ID %d deleted.\n", id_to_delete);
	return 1;
}

int main(void) {
	//code here
	Task* tasks = NULL;
	int task_count = 0;
	char choice[5];
	int id_to_delete;
	int num;
	
	load_file(&tasks, &task_count);
	while (1) {
		printf("\n1. Add Task\n2. See Tasks\n3. Delete Task\n4. Exit\nChoice: ");
		fgets(choice, sizeof(choice), stdin);
		if (sscanf(choice, "%d", &num) == 1) {
			if (num == 1) {
				add_task(&tasks, &task_count);
				write_file(&tasks, &task_count);
			}
			else if (num == 2)
				display_list_task(&tasks, &task_count);
			else if (num == 3) {
				if (task_count == 0) {
					printf("No tasks have been found");
					return 0;
				}else {
					printf("ID to delete task: ");
					scanf("%d", &id_to_delete);
					delete_task(&tasks,
						&task_count,
						id_to_delete);
					write_file(&tasks, &task_count);
				}
			}
			else if (num == 4)
				break;
		} else {
			printf("Invalid choice try again\n");
		}
	}
	
	free(tasks);
	return 0;
}

