#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "test.h"

#define MAX_LENGTH 100

typedef struct student {
	LIST_OBJECT_IN_APP(node_student);

	char first_name[MAX_LENGTH];
	char last_name[MAX_LENGTH];
	unsigned int age;
} student_t;

student_t* make_student(const char* fn, const char* ln, unsigned int a) {
	student_t* stu = NULL;

	if ((stu = (student_t*)calloc(1, sizeof(struct student))) == NULL) {
		return NULL;
	}

	if (strlen(fn) > (MAX_LENGTH - 1)) {
		return NULL;
	}

	if (strlen(ln) > (MAX_LENGTH - 1)) {
		return NULL;
	}

	strcpy(stu->first_name, fn);
	strcpy(stu->last_name, ln);
	stu->age = a;

	return stu;
}


int ckernel_list_test()
{
	// Method 1
	struct list_head my_class;
	INIT_LIST_HEAD(&my_class);

	//Method 2
	//LIST_HEAD(my_class);

	student_t* stu = NULL;

	//////////////////create student
	if ((stu = make_student("ahao", "mu", 22)) == NULL) {
		fprintf(stderr, "Failed to create muahao\n");
		return -1;
	}

	list_add_tail(&stu->node_student, &my_class);

	if ((stu = make_student("lianjie", "li", 23)) == NULL) {
		fprintf(stderr, "Failed to create li tom\n");
		return -1;
	}

	list_add_tail(&stu->node_student, &my_class);

	if ((stu = make_student("xiaolong", "li", 12)) == NULL) {
		fprintf(stderr, "Failed to create lixuehua\n");
		return -1;
	}

	list_add_tail(&stu->node_student, &my_class);

	/////////////// Print all students

	printf("------print all students-----\n");

	list_for_each_entry(stu, student_t, &my_class, node_student) {
		printf("First name:%s\n", stu->first_name);
		printf("Last name:%s\n", stu->last_name);
		printf("Age:%d\n", stu->age);
	}


	//////////////// list bus

	LIST_HEAD(bus);
	printf("\nMoving all students to bus;\n");
	list_splice_init(&my_class, &bus);
	if (list_empty(&my_class)) {
		printf("No students in my_class\n");
	}

	printf("\nPrint all bus students\n");
	list_for_each_entry(stu, student_t, &bus, node_student) {
		printf("First name:%s\n", stu->first_name);
		printf("Last name:%s\n", stu->last_name);
		printf("Age:%d\n", stu->age);
	}

	student_t* temp, * tmpn = NULL;
	printf("\nMuahao do not want go\n");
	list_for_each_entry_safe(temp, tmpn, student_t, &bus, node_student) {
		if (strcmp(temp->first_name, "ahao") == 0) {
			list_del(&temp->node_student);
			free(temp);
		}
	}

	printf("\nAfter muahao leave,students are: \n");
	list_for_each_entry(stu, student_t, &bus, node_student) {
		printf("%s %s %d\n", stu->first_name, stu->last_name, stu->age);
	}

	// end begin clean  all students;
	printf("\nEnd begin clean  all students: \n");
	list_for_each_entry_safe(stu, tmpn, student_t, &bus, node_student) {
		printf("Removing students: %s %s \n", stu->first_name, stu->last_name);
		list_del(&stu->node_student);
		free(stu);
	}

	printf("\n------print all students-----\n");
	list_for_each_entry(stu, student_t, &my_class, node_student) {
		printf("First name:%s\n", stu->first_name);
		printf("Last name:%s\n", stu->last_name);
		printf("Age:%d\n", stu->age);
	}


	return 0;
}

